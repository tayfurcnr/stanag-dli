#pragma once

#include <map>
#include <vector>
#include <chrono>
#include <functional>
#include <iostream>
#include "DliMessage.hpp"
#include "Dispatcher.hpp"
#include "Checksum.hpp"
#include "generated/MessageAcknowledgement.hpp"

namespace dli {

/**
 * @brief Reliable Acknowledgment Status
 */
enum class AckStatus {
    Success,
    Timeout,
    Rejected,
    Failed
};

/**
 * @brief Context for a message pending an acknowledgment
 */
struct AckContext {
    uint32_t destination_id;
    uint16_t original_message_type;
    uint64_t original_time_stamp;
    std::vector<uint8_t> original_buffer;
    uint8_t retry_count{0};
    uint8_t max_retries{3};
    uint64_t deadline{0};
    uint8_t hop_count{0};
    std::function<void(AckStatus)> callback;
};

/**
 * @brief Complex Correlation Key for reliable tracking across mesh networks
 */
using AckKey = std::tuple<uint32_t, uint16_t, uint64_t>; // (Destination, Type, Timestamp)


/**
 * @brief DLI Session Orchestrator
 * Handles reliable messaging, auto-ACK generation, and session-level validation.
 */
class DliSession {
public:
    using SendFunction = std::function<bool(const uint8_t*, size_t)>;

    DliSession(Dispatcher& dispatcher, SendFunction sendFunc)
        : m_dispatcher(dispatcher), m_sendFunc(sendFunc) {}

    /**
     * @brief Sends a message reliably.
     * Injects timestamp only if missing; reuses it for retries.
     */
    template <typename TBody>
    bool send_reliable(dli::DliMessage<TBody>& msg, 
                       uint8_t max_retries = 3, 
                       uint8_t hop_count = 0,
                       std::function<void(AckStatus)> callback = nullptr) 
    {
        // 1. Timestamp Integrity: Populate if missing, preserve if present
        if (msg.body.time_stamp == 0) {
            msg.body.time_stamp = generate_unique_ts();
            msg.body.has_time_stamp = true;
        }

        // 2. Set ACK bit in header
        msg.header.message_properties |= 0x8000;

        // 3. Serialize for archival/re-transmission
        std::vector<uint8_t> buffer(DliHeader::FIXED_SIZE + 2048);
        BitCursor cursor(buffer.data(), buffer.size());
        msg.serialize(cursor);
        size_t totalLen = cursor.position();
        buffer.resize(totalLen);

        // 4. Store Context for Reliability Traceability
        uint32_t dest = msg.header.destination_id;
        uint16_t type = msg.header.message_type;
        uint64_t ts = msg.body.time_stamp;
        
        AckContext ctx;
        ctx.destination_id = dest;
        ctx.original_message_type = type;
        ctx.original_time_stamp = ts;
        ctx.original_buffer = buffer;
        ctx.max_retries = max_retries;
        ctx.deadline = current_time_ms() + calculate_timeout(hop_count);
        ctx.hop_count = hop_count;
        ctx.callback = callback;

        m_pendingAcks[std::make_tuple(dest, type, ts)] = std::move(ctx);

        // 5. Initial Transmission
        return m_sendFunc(buffer.data(), buffer.size());
    }

    /**
     * @brief Process an incoming raw buffer with strict AEP-84.1 sequencing.
     */
    void process_incoming(const uint8_t* buffer, size_t size) {
        BitCursor cursor(const_cast<uint8_t*>(buffer), size);
        
        // 1. Parse Header
        DliHeader header;
        if (!header.deserialize(cursor)) return;

        // 2. Validate Length (Buffer must be at least header + payload)
        if (size < (DliHeader::FIXED_SIZE + header.payload_length)) return;

        // 3. Validate Checksum
        uint8_t cksumType = header.get_checksum_type();
        if (cksumType > 0) {
            size_t expectedTotal = DliHeader::FIXED_SIZE + header.payload_length;
            if (cksumType == 0x01) { // 2-byte CRC
                if (size < expectedTotal + 2) return; 
                uint16_t expectedCRC = dli::Checksum::calculateCRC16(buffer, expectedTotal);
                
                BitCursor ckCursor(const_cast<uint8_t*>(buffer + expectedTotal), 2);
                uint16_t actualCRC; 
                ckCursor.read<uint16_t>(actualCRC);

                if (expectedCRC != actualCRC) {
                    std::cout << "  [DEBUG] CRC-16 Validation Failed. Expected: " << expectedCRC << ", Got: " << actualCRC << std::endl;
                    return; // Drop corrupted frame
                }
            } else if (cksumType >= 0x02) { // 4-byte CRC
                if (size < expectedTotal + 4) return;
                uint32_t expectedCRC = dli::Checksum::calculateCRC32(buffer, expectedTotal);
                
                BitCursor ckCursor(const_cast<uint8_t*>(buffer + expectedTotal), 4);
                uint32_t actualCRC; 
                ckCursor.read<uint32_t>(actualCRC);

                if (expectedCRC != actualCRC) {
                    std::cout << "  [DEBUG] CRC-32 Validation Failed. Expected: " << expectedCRC << ", Got: " << actualCRC << std::endl;
                    return; // Drop corrupted frame
                }
            }
        }

        // 4. Handle Synchronization/ACK Messages (#17000 Resolve)
        if (header.message_type == 17000) {
            handle_ack_message(header, buffer, size);
            return;
        }

        // 5. Dispatch Payload to Application Layer
        auto dispatchResult = m_dispatcher.dispatch(buffer, size);

        // 6. Auto-ACK Logic (Emit #17000 only if message is fully valid)
        if (dispatchResult.has_value() && header.requires_ack()) {
            send_auto_ack(header, dispatchResult.value());
        }
    }

    /**
     * @brief Periodic cycle to handle retry deadlines and timeouts.
     */
    void tick() {
        uint64_t now = current_time_ms();
        auto it = m_pendingAcks.begin();
        while (it != m_pendingAcks.end()) {
            if (now >= it->second.deadline) {
                if (it->second.retry_count < it->second.max_retries) {
                    it->second.retry_count++;
                    it->second.deadline = now + calculate_timeout(it->second.hop_count);
                    
                    // Advance iterator safely and copy buffer before invoking m_sendFunc 
                    // to prevent invalidation and dangling references in synchronous loopback mocks.
                    auto current = it++;
                    auto buffer_copy = current->second.original_buffer;
                    m_sendFunc(buffer_copy.data(), buffer_copy.size());
                } else {
                    auto current = it++;
                    if (current->second.callback) current->second.callback(AckStatus::Timeout);
                    m_pendingAcks.erase(current);
                }
            } else {
                ++it;
            }
        }
    }

private:
    void handle_ack_message(const dli::DliHeader& header, const uint8_t* buffer, size_t size) {
        BitCursor cursor(const_cast<uint8_t*>(buffer), size);
        dli::DliMessage<dli::generated::MessageAcknowledgement> ackMsg;
        if (ackMsg.deserialize(cursor)) {
            // Guard against uninitialized PV fields (garbage data)
            if (!ackMsg.body.has_original_message_type || !ackMsg.body.has_original_time_stamp) {
                std::cout << "  [DEBUG] Ignored Invalid ACK (Missing PV Flags)" << std::endl;
                return;
            }

            uint32_t senderId = header.source_id; // The source of the ACK is my original destination
            uint16_t origType = ackMsg.body.original_message_type;
            uint64_t origTs = ackMsg.body.original_time_stamp;

            std::cout << "  [DEBUG] Session received ACK from Node: " << senderId << " for Type: " << origType << ", TS: " << origTs << std::endl;

            auto ackKey = std::make_tuple(senderId, origType, origTs);
            auto it = m_pendingAcks.find(ackKey);
            
            if (it != m_pendingAcks.end()) {
                std::cout << "  [DEBUG] Correlation Successful!" << std::endl;
                if (it->second.callback) it->second.callback(AckStatus::Success);
                m_pendingAcks.erase(it);
            } else {
                std::cout << "  [DEBUG] Correlation Failed!" << std::endl;
            }
        } else {
            std::cout << "  [DEBUG] Failed to deserialize incoming ACK!" << std::endl;
        }
    }

    void send_auto_ack(const DliHeader& originalHeader, uint64_t originalTs) {
        dli::DliMessage<dli::generated::MessageAcknowledgement> ack;
        ack.header.message_type = 17000;
        ack.header.source_id = originalHeader.destination_id;
        ack.header.destination_id = originalHeader.source_id;
        
        ack.body.time_stamp = generate_unique_ts();
        ack.body.has_time_stamp = true;
        ack.body.original_time_stamp = originalTs;
        ack.body.has_original_time_stamp = true;
        ack.body.original_message_type = originalHeader.message_type;
        ack.body.has_original_message_type = true;
        ack.body.acknowledgement_type = 1; // "Received"
        ack.body.has_acknowledgement_type = true;

        std::vector<uint8_t> outBuffer(128);
        BitCursor outCursor(outBuffer.data(), outBuffer.size());
        ack.serialize(outCursor);
        m_sendFunc(outBuffer.data(), outCursor.position());
    }

    uint64_t calculate_timeout(uint8_t hop_count) {
        // Base AEP-84 latency (500ms) + dynamic mesh penalty
        return 500 + (hop_count * 100); 
    }

    uint64_t current_time_ms() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count();
    }

    uint64_t generate_unique_ts() {
        static uint64_t last_ts = 0;
        uint64_t now = current_time_ms();
        if (now <= last_ts) {
            now = last_ts + 1; // Monotonic increment guarantee
        }
        last_ts = now;
        return now;
    }

    Dispatcher& m_dispatcher;
    SendFunction m_sendFunc;
    std::map<AckKey, AckContext> m_pendingAcks;
};

} // namespace dli

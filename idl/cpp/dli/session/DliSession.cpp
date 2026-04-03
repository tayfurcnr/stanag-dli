#include <dli/session/DliSession.hpp>
#include <dli/core/ILogger.hpp>

namespace dli {

void DliSession::process_incoming(const uint8_t* buffer, size_t size) {
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
                Logger::debug("CRC-16 Validation Failed. Expected: " + std::to_string(expectedCRC) + ", Got: " + std::to_string(actualCRC));
                return; // Drop corrupted frame
            }
        } else if (cksumType >= 0x02) { // 4-byte CRC
            if (size < expectedTotal + 4) return;
            uint32_t expectedCRC = dli::Checksum::calculateCRC32(buffer, expectedTotal);
            
            BitCursor ckCursor(const_cast<uint8_t*>(buffer + expectedTotal), 4);
            uint32_t actualCRC; 
            ckCursor.read<uint32_t>(actualCRC);

            if (expectedCRC != actualCRC) {
                Logger::debug("CRC-32 Validation Failed. Expected: " + std::to_string(expectedCRC) + ", Got: " + std::to_string(actualCRC));
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

void DliSession::tick() {
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
                send_raw(buffer_copy.data(), buffer_copy.size());
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

void DliSession::handle_ack_message(const dli::DliHeader& header, const uint8_t* buffer, size_t size) {
    BitCursor cursor(const_cast<uint8_t*>(buffer), size);
    dli::DliMessage<dli::generated::MessageAcknowledgement> ackMsg;
    if (ackMsg.deserialize(cursor)) {
        // Guard against uninitialized PV fields (garbage data)
        if (!ackMsg.body.has_original_message_type || !ackMsg.body.has_original_message_time_stamp) {
            Logger::debug("Ignored Invalid ACK (Missing PV Flags)");
            return;
        }

        uint32_t senderId = header.source_id; // The source of the ACK is my original destination
        uint16_t origType = ackMsg.body.original_message_type;
        uint64_t origTs = ackMsg.body.original_message_time_stamp;

        Logger::debug("Session received ACK from Node: " + std::to_string(senderId) + " for Type: " + std::to_string(origType) + ", TS: " + std::to_string(origTs));

        auto ackKey = std::make_tuple(senderId, origType, origTs);
        auto it = m_pendingAcks.find(ackKey);
        
        if (it != m_pendingAcks.end()) {
            Logger::debug("Correlation Successful!");
            if (it->second.callback) it->second.callback(AckStatus::Success);
            m_pendingAcks.erase(it);
        } else {
            Logger::debug("Correlation Failed!");
        }
    } else {
        Logger::debug("Failed to deserialize incoming ACK!");
    }
}

void DliSession::send_auto_ack(const DliHeader& originalHeader, uint64_t originalTs) {
    dli::DliMessage<dli::generated::MessageAcknowledgement> ack;
    ack.header.message_type = 17000;
    ack.header.source_id = originalHeader.destination_id;
    ack.header.destination_id = originalHeader.source_id;
    
    ack.body.time_stamp = generate_unique_ts();
    ack.body.has_time_stamp = true;
    ack.body.original_message_time_stamp = originalTs;
    ack.body.has_original_message_time_stamp = true;
    ack.body.original_message_type = originalHeader.message_type;
    ack.body.has_original_message_type = true;
    ack.body.acknowledgement_type = 1; // "Received"
    ack.body.has_acknowledgement_type = true;

    std::vector<uint8_t> outBuffer(128);
    BitCursor outCursor(outBuffer.data(), outBuffer.size());
    ack.serialize(outCursor);
    send_raw(outBuffer.data(), outCursor.position());
}

uint64_t DliSession::calculate_timeout(uint8_t hop_count) {
    // Base AEP-84 latency (500ms) + dynamic mesh penalty
    return 500 + (hop_count * 100); 
}

uint64_t DliSession::current_time_ms() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
}

uint64_t DliSession::generate_unique_ts() {
    static uint64_t last_ts = 0;
    uint64_t now = current_time_ms();
    if (now <= last_ts) {
        now = last_ts + 1; // Monotonic increment guarantee
    }
    last_ts = now;
    return now;
}

} // namespace dli

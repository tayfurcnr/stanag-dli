#pragma once

#include <map>
#include <vector>
#include <chrono>
#include <functional>
#include <dli/core/ILogger.hpp>
#include <dli/core/BitCursor.hpp>
#include <dli/core/Checksum.hpp>
#include <dli/protocol/DliHeader.hpp>
#include <dli/protocol/DliMessage.hpp>
#include <dli/protocol/Dispatcher.hpp>
#include <dli/generated/messages/MessageAcknowledgement.hpp>

#include <dli/transport/ITransport.hpp>
#include <dli/generated/messages/MessageAcknowledgement.hpp>

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
 * Handles multi-transport management, reliable messaging, and auto-ACK generation.
 */
class DliSession {
public:
    explicit DliSession(Dispatcher& dispatcher)
        : m_dispatcher(dispatcher) {}

    /**
     * @brief Registers a transport adapter to the session.
     */
    void add_transport(ITransport* transport) {
        if (transport) m_transports.push_back(transport);
    }

    /**
     * @brief Broadcasts a raw buffer to all active transports.
     */
    bool send_raw(const uint8_t* buffer, size_t size) {
        bool any_success = false;
        for (auto* t : m_transports) {
            if (t->send(buffer, size)) any_success = true;
        }
        return any_success;
    }

    /**
     * @brief Sends a message reliably across all active transports.
     */
    template <typename TBody>
    bool send_reliable(dli::DliMessage<TBody>& msg, 
                       uint8_t max_retries = 3, 
                       uint8_t hop_count = 0,
                       std::function<void(AckStatus)> callback = nullptr) 
    {
        if (msg.body.time_stamp == 0) {
            msg.body.time_stamp = generate_unique_ts();
            msg.body.has_time_stamp = true;
        }

        msg.header.message_properties |= 0x8000;

        std::vector<uint8_t> buffer(DliHeader::FIXED_SIZE + 2048);
        BitCursor cursor(buffer.data(), buffer.size());
        msg.serialize(cursor);
        size_t totalLen = cursor.position();
        buffer.resize(totalLen);

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

        return send_raw(buffer.data(), buffer.size());
    }

    /**
     * @brief Process an incoming raw buffer.
     */
    void process_incoming(const uint8_t* buffer, size_t size);

    /**
     * @brief Periodic cycle to handle retry deadlines and timeouts.
     */
    void tick();

private:
    void handle_ack_message(const dli::DliHeader& header, const uint8_t* buffer, size_t size);
    void send_auto_ack(const DliHeader& originalHeader, uint64_t originalTs);
    uint64_t calculate_timeout(uint8_t hop_count);
    uint64_t current_time_ms();
    uint64_t generate_unique_ts();

    Dispatcher& m_dispatcher;
    std::vector<ITransport*> m_transports;
    std::map<AckKey, AckContext> m_pendingAcks;
};

} // namespace dli

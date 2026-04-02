#pragma once

#include <dli/core/BitCursor.hpp>
#include <functional>
#include <map>
#include <memory>
#include <vector>

#include <dli/protocol/DliHeader.hpp>
#include <dli/protocol/Profile.hpp>
#include <dli/core/ILogger.hpp>
#include <iostream>

namespace dli {

/**
 * @brief Dispatcher for routing incoming DLI messages to registered handlers.
 */
class Dispatcher {
public:
    using MessageHandler = std::function<uint64_t(const DliHeader& header, BitCursor& payload)>;

    /**
     * @brief Registers a handler for a specific message type.
     */
    void registerHandler(uint16_t type, MessageHandler handler) {
        m_handlers[type] = handler;
    }

    /**
     * @brief Sets the active interoperability profile for filtering.
     */
    void setProfile(const Profile& profile) {
        m_activeProfile = profile;
        Logger::info("Dispatcher profile set to: " + profile.name() + " (LOI " + std::to_string(profile.loi()) + ")");
    }

    /**
     * @brief Dispatches a raw buffer according to AEP-84 Volume II Wrapper.
     */
    std::optional<uint64_t> dispatch(const uint8_t* buffer, size_t size) {
        if (size < DliHeader::FIXED_SIZE) return std::nullopt;

        BitCursor cursor(const_cast<uint8_t*>(buffer), size);
        
        DliHeader header;
        if (!header.deserialize(cursor)) {
            return std::nullopt;
        }

        // Validate payload bounds
        size_t expectedTotal = DliHeader::FIXED_SIZE + header.payload_length;
        if (size < expectedTotal) {
            return std::nullopt;
        }

        // Create a sub-cursor for the payload (Body)
        BitCursor payloadCursor(const_cast<uint8_t*>(buffer + DliHeader::FIXED_SIZE), header.payload_length);

        // 1. Profile Validation (AEP-84 Compliance)
        if (m_activeProfile.has_value() && !m_activeProfile->is_permitted(header.message_type)) {
            Logger::warn("Message #" + std::to_string(header.message_type) + " is REJECTED by active profile: " + m_activeProfile->name());
            return std::nullopt;
        }

        // 2. Route to Handler
        if (m_handlers.count(header.message_type)) {
            uint64_t ts = m_handlers[header.message_type](header, payloadCursor);
            return ts;
        }

        return std::nullopt; // Unhandled message
    }

private:
    std::map<uint16_t, MessageHandler> m_handlers;
    std::optional<Profile> m_activeProfile;
};


} // namespace dli

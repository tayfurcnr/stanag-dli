#include <dli/protocol/Dispatcher.hpp>
#include <dli/core/ILogger.hpp>
#include <iostream>

namespace dli {

void Dispatcher::registerHandler(uint16_t type, MessageHandler handler) {
    m_handlers[type] = handler;
}

void Dispatcher::setProfile(const Profile& profile) {
    m_activeProfile = profile;
    Logger::info("Dispatcher profile set to: " + profile.name() + " (LOI " + std::to_string(profile.loi()) + ")");
}

std::optional<uint64_t> Dispatcher::dispatch(const uint8_t* buffer, size_t size) {
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
    auto it = m_handlers.find(header.message_type);
    if (it != m_handlers.end()) {
        uint64_t ts = it->second(header, payloadCursor);
        return ts;
    }

    return std::nullopt; // Unhandled message
}

} // namespace dli

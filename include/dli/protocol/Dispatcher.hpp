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
    void registerHandler(uint16_t type, MessageHandler handler);

    /**
     * @brief Sets the active interoperability profile for filtering.
     */
    void setProfile(const Profile& profile);

    /**
     * @brief Dispatches a raw buffer according to AEP-84 Volume II Wrapper.
     */
    std::optional<uint64_t> dispatch(const uint8_t* buffer, size_t size);

private:
    std::map<uint16_t, MessageHandler> m_handlers;
    std::optional<Profile> m_activeProfile;
};

} // namespace dli

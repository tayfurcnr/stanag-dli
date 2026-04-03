#ifndef DLI_I_TRANSPORT_HPP
#define DLI_I_TRANSPORT_HPP

#include <cstdint>
#include <cstddef>
#include <functional>

namespace dli {

/**
 * @brief Abstract interface for DLI Transport Layers.
 * 
 * Defines how raw DLI buffers are sent and received across physical media.
 */
class ITransport {
public:
    using DataCallback = std::function<void(const uint8_t* data, size_t length)>;

    virtual ~ITransport() = default;

    /**
     * @brief Start the transport (e.g., open socket/serial port).
     */
    virtual bool start() = 0;

    /**
     * @brief Stop the transport.
     */
    virtual void stop() = 0;

    /**
     * @brief Sends a DLI message buffer.
     * Implementation may include internal grouping/packing (AEP-84 Policy).
     */
    virtual bool send(const uint8_t* data, size_t length) = 0;

    /**
     * @brief Polls for incoming data and triggers the callback for each DLI message found.
     */
    virtual void poll(DataCallback callback) = 0;

    /**
     * @brief Flushes any buffered/packed messages immediately.
     */
    virtual void flush() = 0;
};

} // namespace dli

#endif // DLI_I_TRANSPORT_HPP

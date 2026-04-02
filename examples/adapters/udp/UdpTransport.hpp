#ifndef DLI_UDP_TRANSPORT_HPP
#define DLI_UDP_TRANSPORT_HPP

#include <dli/transport/ITransport.hpp>
#include <dli/transport/TransportCapabilities.hpp>
#include <dli/transport/IPackingPolicy.hpp>
#include <dli/protocol/DliHeader.hpp>

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <atomic>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

namespace dli {

/**
 * @brief POSIX-based UDP Multicast Transport.
 * 
 * Implements a non-blocking multicast adapter with throughput-optimized packing
 * and Message #32300-aware monitoring statistics.
 */
class UdpTransport : public ITransport {
public:
    using DataCallback = std::function<void(const uint8_t*, size_t)>;

    struct Config {
        std::string multicast_group;
        uint16_t port;
        std::string local_interface = "0.0.0.0"; // Default to all interfaces
        size_t mtu = 548;            // Implementation policy default
        TransportCapabilities caps;
    };

    explicit UdpTransport(const Config& config, std::unique_ptr<IPackingPolicy> packing_policy = nullptr);
    ~UdpTransport();

    /**
     * @brief Initializes the socket and joins the multicast group.
     */
    bool start();

    /**
     * @brief Closes the socket and leaves the group.
     */
    void stop();

    /**
     * @brief Queues a DLI frame for transmission.
     * 
     * If packing is enabled, the message may be buffered until MTU is reached.
     */
    bool send(const uint8_t* data, size_t length);

    /**
     * @brief Forces transmission of the current packed buffer.
     */
    void flush();

    /**
     * @brief Polls the socket for incoming DLI frames.
     * 
     * @param callback Invoked for each successfully received (and optionally packed) DLI frame.
     */
    void poll(DataCallback callback);

    // Monitoring
    uint64_t get_rx_count() const { return m_rx_count.load(); }
    uint64_t get_tx_count() const { return m_tx_count.load(); }

private:
    Config m_config;
    int m_sockfd = -1;
    std::unique_ptr<IPackingPolicy> m_packing_policy;

    std::vector<uint8_t> m_tx_buffer;
    std::atomic<uint64_t> m_rx_count{0};
    std::atomic<uint64_t> m_tx_count{0};

    bool set_nonblocking(int fd);
};

} // namespace dli

#endif // DLI_UDP_TRANSPORT_HPP

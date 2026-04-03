#ifndef DLI_MULTICAST_TRANSPORT_HPP
#define DLI_MULTICAST_TRANSPORT_HPP

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
 * @brief Standard AEP-84 Vol II Multicast Transport Profile.
 * 
 * Implements a non-blocking multicast adapter using the standard universal
 * multicast group (225.200.1.0) as default for DLI discovery and streaming.
 */
struct MulticastConfig {
    std::string multicast_group = "225.200.1.0"; // AEP-84 Example Universal Group
    uint16_t port = 51017;                      // AEP-84 Example Port
    std::string local_interface = "0.0.0.0"; 
    size_t mtu = 548;            
    TransportCapabilities caps;
};

/**
 * @brief Standard AEP-84 Vol II Multicast Transport Profile.
 * 
 * Implements a non-blocking multicast adapter using the standard universal
 * multicast group (225.200.1.0) as default for DLI discovery and streaming.
 */
class MulticastTransport : public ITransport {
public:
    using DataCallback = std::function<void(const uint8_t*, size_t)>;

    explicit MulticastTransport(const MulticastConfig& config = MulticastConfig(), std::unique_ptr<IPackingPolicy> packing_policy = nullptr);
    ~MulticastTransport();

    bool start() override;
    void stop() override;
    bool send(const uint8_t* data, size_t length) override;
    void flush() override;
    void poll(DataCallback callback) override;

    uint64_t get_rx_count() const { return m_rx_count.load(); }
    uint64_t get_tx_count() const { return m_tx_count.load(); }

private:
    MulticastConfig m_config;
    int m_sockfd = -1;
    std::unique_ptr<IPackingPolicy> m_packing_policy;

    std::vector<uint8_t> m_tx_buffer;
    std::atomic<uint64_t> m_rx_count{0};
    std::atomic<uint64_t> m_tx_count{0};

    bool set_nonblocking(int fd);
};

} // namespace dli

#endif // DLI_MULTICAST_TRANSPORT_HPP

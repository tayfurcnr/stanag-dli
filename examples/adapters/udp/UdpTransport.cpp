#include "UdpTransport.hpp"
#include <dli/core/BitCursor.hpp>
#include <dli/core/ILogger.hpp>
#include <cstring>

namespace dli {

UdpTransport::UdpTransport(const Config& config, std::unique_ptr<IPackingPolicy> packing_policy)
    : m_config(config), m_packing_policy(std::move(packing_policy)) {
    if (!m_packing_policy) {
        m_packing_policy = std::make_unique<MtuBatchingPolicy>();
    }
    m_tx_buffer.reserve(m_config.mtu);
}

UdpTransport::~UdpTransport() {
    stop();
}

bool UdpTransport::start() {
    m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_sockfd < 0) {
        Logger::error("Failed to create UDP socket");
        return false;
    }

    int reuse = 1;
    setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    struct sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_config.port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(m_sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        Logger::error("Failed to bind UDP socket to port " + std::to_string(m_config.port));
        stop();
        return false;
    }

    // Join Multicast Group
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(m_config.multicast_group.c_str());
    mreq.imr_interface.s_addr = inet_addr(m_config.local_interface.c_str());
    if (setsockopt(m_sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
        Logger::error("Failed to join multicast group: " + m_config.multicast_group);
        stop();
        return false;
    }

    set_nonblocking(m_sockfd);
    return true;
}

void UdpTransport::stop() {
    if (m_sockfd >= 0) {
        struct ip_mreq mreq;
        mreq.imr_multiaddr.s_addr = inet_addr(m_config.multicast_group.c_str());
        mreq.imr_interface.s_addr = inet_addr(m_config.local_interface.c_str());
        setsockopt(m_sockfd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq));
        close(m_sockfd);
        m_sockfd = -1;
    }
}

bool UdpTransport::send(const uint8_t* data, size_t length) {
    if (!m_config.caps.supports_packing) {
        // Immediate send
        struct sockaddr_in dest;
        std::memset(&dest, 0, sizeof(dest));
        dest.sin_family = AF_INET;
        dest.sin_port = htons(m_config.port);
        dest.sin_addr.s_addr = inet_addr(m_config.multicast_group.c_str());
        
        ssize_t sent = sendto(m_sockfd, data, length, 0, (struct sockaddr*)&dest, sizeof(dest));
        if (sent > 0) m_tx_count++;
        return sent > 0;
    }

    // Packing logic
    if (m_packing_policy->should_flush(m_tx_buffer.size(), length, m_config.mtu)) {
        flush();
    }

    m_tx_buffer.insert(m_tx_buffer.end(), data, data + length);
    return true;
}

void UdpTransport::flush() {
    if (m_tx_buffer.empty()) return;

    struct sockaddr_in dest;
    std::memset(&dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(m_config.port);
    dest.sin_addr.s_addr = inet_addr(m_config.multicast_group.c_str());

    ssize_t sent = sendto(m_sockfd, m_tx_buffer.data(), m_tx_buffer.size(), 0, (struct sockaddr*)&dest, sizeof(dest));
    if (sent > 0) m_tx_count++;
    
    m_tx_buffer.clear();
    m_packing_policy->on_flush();
}

void UdpTransport::poll(DataCallback callback) {
    if (m_sockfd < 0) return;

    uint8_t buffer[65535]; // Max possible UDP datagram
    while (true) {
        ssize_t received = recvfrom(m_sockfd, buffer, sizeof(buffer), 0, nullptr, nullptr);
        if (received <= 0) break;

        // Extract DLI message(s) from the datagram
        size_t offset = 0;
        size_t bytes_left = static_cast<size_t>(received);

        while (bytes_left >= DliHeader::FIXED_SIZE) {
            // Read header into a temporary BitCursor or direct mapping
            // Note: We need to know the payload length to find the next message
            // and the checksum size if applicable.
            
            // For now, we assume standard wrapper parsing:
            // Since we don't have a full wrapper parser here yet, 
            // we'll use a conservative peek at the payload length field.
            
            // Header: Reserved(2), Length(2), ...
            uint16_t payload_len = (buffer[offset + 2] << 8) | buffer[offset + 3];
            
            // TODO: If checksum bits in header are set, account for 2 or 4 bytes footer.
            // For the purpose of this implementation POC, we check message properties.
            uint16_t properties = (buffer[offset + 14] << 8) | buffer[offset + 15];
            uint8_t checksum_type = (properties >> 6) & 0x03;
            size_t checksum_size = 0;
            if (checksum_type == 0x01) checksum_size = 2;
            else if (checksum_type == 0x03) checksum_size = 4;

            size_t total_msg_size = DliHeader::FIXED_SIZE + payload_len + checksum_size;

            if (total_msg_size > bytes_left) {
                // Malformed or truncated datagram
                break;
            }

            callback(&buffer[offset], total_msg_size);
            m_rx_count++;

            offset += total_msg_size;
            bytes_left -= total_msg_size;
        }
    }
}

bool UdpTransport::set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) return false;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK) >= 0;
}

} // namespace dli

#include <UdpTransport.hpp>
#include <dli/protocol/DliHeader.hpp>
#include <dli/core/BitCursor.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace dli;

/**
 * @brief Simple utility to bridge simulated DLI traffic to the network.
 */
int main() {
    std::cout << "[DLI Bridge] Initializing UDP Multicast Transport..." << std::endl;

    UdpTransport::Config config;
    config.multicast_group = "239.1.2.3";
    config.port = 30001;
    config.mtu = 548; // AEP-84 policy
    config.caps.supports_packing = true;

    UdpTransport transport(config);
    if (!transport.start()) {
        std::cerr << "[DLI Bridge] Failed to start transport!" << std::endl;
        return 1;
    }

    std::cout << "[DLI Bridge] Multicast Group: " << config.multicast_group << ":" << config.port << std::endl;
    std::cout << "[DLI Bridge] MTU: " << config.mtu << " bytes | Packing: ENABLED" << std::endl;

    // Simulate sending some DLI messages
    uint32_t msg_count = 0;
    auto start_time = std::chrono::steady_clock::now();

    while (msg_count < 10) {
        DliHeader header;
        header.message_type = 4000; // Inertial States
        header.source_id = 100;
        header.destination_id = 0; // Broadcast
        header.payload_length = 8;  // Dummy payload

        std::vector<uint8_t> buffer(DliHeader::FIXED_SIZE + 8);
        BitCursor cursor(buffer.data(), buffer.size());
        header.serialize(cursor);
        
        // Dummy payload bytes
        for(int i=0; i<8; ++i) buffer[DliHeader::FIXED_SIZE + i] = static_cast<uint8_t>(msg_count + i);

        std::cout << "[DLI Bridge] Sending Message #" << (msg_count + 1) << " (Type 4000)..." << std::endl;
        transport.send(buffer.data(), buffer.size());

        msg_count++;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        // Every 5 messages, we might want to see if it packed them
        if (msg_count % 5 == 0) {
            std::cout << "[DLI Bridge] Stats - TX Datagrams: " << transport.get_tx_count() 
                      << " | RX Messages: " << transport.get_rx_count() << std::endl;
        }
    }

    std::cout << "[DLI Bridge] Finalizing transmission (flushing buffer)..." << std::endl;
    transport.flush();

    std::cout << "[DLI Bridge] Final Stats - TX Datagrams: " << transport.get_tx_count() << std::endl;
    std::cout << "[DLI Bridge] Bridge shutting down. 🫡" << std::endl;

    transport.stop();
    return 0;
}

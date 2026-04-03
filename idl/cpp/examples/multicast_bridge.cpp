#include <dli/transport/MulticastTransport.hpp>
#include <dli/protocol/DliHeader.hpp>
#include <dli/core/BitCursor.hpp>
#include <dli/generated/messages/InertialStates.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace dli;
using namespace dli::generated;

int main() {
    std::cout << "[DLI Bridge] Initializing AEP-84 Multicast Transport..." << std::endl;

    MulticastConfig config;
    config.multicast_group = "239.1.2.3";
    config.port = 30001;
    config.mtu = 548;
    config.caps.supports_packing = true;

    MulticastTransport transport(config);
    if (!transport.start()) {
        std::cerr << "[DLI Bridge] Failed to start transport!" << std::endl;
        return 1;
    }

    std::cout << "[DLI Bridge] Multicast Group: " << config.multicast_group << ":" << config.port << std::endl;

    uint32_t msg_count = 0;
    while (msg_count < 20) {
        // 1. Create a real InertialStates message
        InertialStates msg;
        msg.has_time_stamp = true;
        msg.time_stamp = std::chrono::system_clock::now().time_since_epoch().count() / 1000000;
        
        msg.has_latitude = true;
        msg.latitude = 40.123456 + (msg_count * 0.0001); // Bursa/TURKEY area
        
        msg.has_longitude = true;
        msg.longitude = 29.123456 + (msg_count * 0.0001);
        
        msg.has_altitude = true;
        msg.altitude = 1500.5 + msg_count;

        msg.has_heading = true;
        msg.heading = 1.57; // 90 degrees

        // 2. Serialize Payload
        std::vector<uint8_t> payload_buf(128);
        BitCursor pay_cursor(payload_buf.data(), payload_buf.size());
        msg.serialize(pay_cursor);
        uint32_t pay_len = pay_cursor.byteOffset();

        // 3. Prepare DLI Packet (Header + Payload)
        DliHeader header;
        header.message_type = 4000;
        header.source_id = 100;
        header.destination_id = 0;
        header.payload_length = pay_len;

        std::vector<uint8_t> packet_buf(DliHeader::FIXED_SIZE + pay_len);
        BitCursor pack_cursor(packet_buf.data(), packet_buf.size());
        header.serialize(pack_cursor);
        
        // Copy payload manually to bit-boundary (DLI payload starts at byte 20)
        std::copy(payload_buf.begin(), payload_buf.begin() + pay_len, packet_buf.begin() + DliHeader::FIXED_SIZE);

        std::cout << "[DLI Bridge] Sending InertialStates #" << (msg_count + 1) 
                  << " | Lat: " << msg.latitude << " | Lon: " << msg.longitude << std::endl;
        
        transport.send(packet_buf.data(), packet_buf.size());

        msg_count++;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    transport.flush();
    std::cout << "[DLI Bridge] Done. 🫡" << std::endl;
    transport.stop();
    return 0;
}

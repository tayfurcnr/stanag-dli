#include <gtest/gtest.h>
#include <UdpTransport.hpp>
#include <dli/protocol/DliMessage.hpp>
#include <dli/generated/messages/InertialStates.hpp>
#include <thread>
#include <chrono>

using namespace dli;

TEST(UdpTransportTest, MulticastLoopback) {
    UdpTransport::Config config;
    config.multicast_group = "239.0.0.1";
    config.port = 12345;
    config.local_interface = "0.0.0.0";
    config.mtu = 548;
    config.caps.supports_packing = false; // Test single message first

    UdpTransport transport(config);
    ASSERT_TRUE(transport.start());

    // Prepare a DLI message
    DliHeader header;
    header.message_type = 4000;
    header.source_id = 1;
    header.destination_id = 2;
    header.payload_length = 0; // No payload for smoke test

    std::vector<uint8_t> buffer(DliHeader::FIXED_SIZE);
    BitCursor cursor(buffer.data(), buffer.size());
    header.serialize(cursor);

    // Send
    transport.send(buffer.data(), buffer.size());

    // Receive with a small delay for OS to route multicast
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    bool received = false;
    transport.poll([&](const uint8_t* data, size_t len) {
        ASSERT_EQ(len, DliHeader::FIXED_SIZE);
        DliHeader rx_header;
        BitCursor rx_cursor(const_cast<uint8_t*>(data), len);
        rx_header.deserialize(rx_cursor);
        EXPECT_EQ(rx_header.message_type, 4000);
        received = true;
    });

    EXPECT_TRUE(received);
    EXPECT_EQ(transport.get_rx_count(), 1);
    
    transport.stop();
}

TEST(UdpTransportTest, PackingVerification) {
    UdpTransport::Config config;
    config.multicast_group = "239.0.0.1";
    config.port = 12346;
    config.mtu = 548;
    config.caps.supports_packing = true;

    UdpTransport transport(config);
    ASSERT_TRUE(transport.start());

    std::vector<uint8_t> msg1(DliHeader::FIXED_SIZE, 0xAA);
    std::vector<uint8_t> msg2(DliHeader::FIXED_SIZE, 0xBB);
    
    // Manually set payload length in headers (offset 2-3) to FIXED_SIZE-FIXED_SIZE = 0
    msg1[2] = 0; msg1[3] = 0;
    msg2[2] = 0; msg2[3] = 0;

    // Send two messages. They should be packed into one datagram.
    transport.send(msg1.data(), msg1.size());
    transport.send(msg2.data(), msg2.size());
    
    // Total buffer is 40 bytes. MTU is 548. `should_flush` is false.
    // We must manually flush.
    transport.flush();

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    int count = 0;
    transport.poll([&](const uint8_t* data, size_t len) {
        count++;
    });

    EXPECT_EQ(count, 2);
    EXPECT_EQ(transport.get_rx_count(), 2);
    EXPECT_EQ(transport.get_tx_count(), 1); // One datagram, two messages
    
    transport.stop();
}

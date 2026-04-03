#include <iostream>
#include <cassert>
#include <dli/generated/messages/InertialStates.hpp>
#include <dli/protocol/DliMessage.hpp>
#include <dli/protocol/Dispatcher.hpp>

using namespace dli;
using namespace dli::generated;

int main() {
    std::cout << "[TEST] Starting DLI Protocol Round-trip Test..." << std::endl;

    // 1. Prepare a Message with Payload (#4000 Inertial States)
    DliMessage<InertialStates> original;
    original.header.source_id = 12345;
    original.header.destination_id = 54321;
    original.header.message_type = 4000;
    original.header.message_properties = 0x8020; // ACK requested, IDD Version 32 (Ed 4)
    
    // Set fields and their presence flags
    original.body.time_stamp = 1000;
    original.body.has_time_stamp = true;
    
    original.body.latitude = 0.523598; // 30 degrees
    original.body.has_latitude = true;
    
    original.body.longitude = 0.785398; // 45 degrees
    original.body.has_longitude = true;
    
    original.body.altitude = 150.0;
    original.body.has_altitude = true;
    
    original.body.u_speed = 50; // cm/s if scaled, but uint32 here
    original.body.has_u_speed = true;

    // 2. Serialize
    uint8_t buffer[1024];
    BitCursor writeCursor(buffer, 1024);
    original.serialize(writeCursor);

    size_t totalBytes = writeCursor.position();
    std::cout << "[INFO] Serialized Size: " << totalBytes << " bytes (" 
              << DliHeader::FIXED_SIZE << " header + " 
              << original.header.payload_length << " payload, excluding checksum)" << std::endl;

    assert(totalBytes == DliHeader::FIXED_SIZE + original.header.payload_length);

    // 3. Dispatch & Verify
    Dispatcher dispatcher;
    bool messageReceived = false;

    dispatcher.registerHandler(4000, [&](const DliHeader& header, BitCursor& payload) -> uint64_t {
        std::cout << "[RECV] Dispatcher triggered for Message #4000" << std::endl;
        assert(header.source_id == 12345);
        assert(header.destination_id == 54321);
        assert(header.message_type == 4000);

        InertialStates receivedBody;
        receivedBody.deserialize(payload); // Returns void
        
        std::cout << "[RECV] Body Deserialized" << std::endl;
        assert(receivedBody.has_time_stamp);
        assert(receivedBody.time_stamp == 1000);
        assert(receivedBody.has_latitude);
        messageReceived = true;
        return receivedBody.time_stamp;
    });

    auto res = dispatcher.dispatch(buffer, totalBytes);
    bool success = res.has_value();
    
    if (success && messageReceived) {
        std::cout << "[SUCCESS] DLI Protocol Round-trip verified!" << std::endl;
        return 0;
    } else {
        std::cerr << "[FAILURE] Protocol Round-trip failed!" << std::endl;
        return 1;
    }
}

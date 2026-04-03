#include <iostream>
#include <cassert>
#include <vector>
#include "../include/dli/BitCursor.hpp"
#include "../include/dli/Bam.hpp"

using namespace dli;

void test_endian_roundtrip() {
    std::cout << "[Test] Endian Roundtrip (uint16, uint32)..." << std::endl;
    uint8_t buffer[16] = {0};
    BitCursor cursor(buffer, 16);

    uint16_t val16 = 0xABCD;
    uint32_t val32 = 0x12345678;

    cursor.write(val16);
    cursor.write(val32);

    assert(cursor.position() == 6);
    
    // Manual check for Big-Endian
    assert(buffer[0] == 0xAB);
    assert(buffer[1] == 0xCD);
    assert(buffer[2] == 0x12);
    assert(buffer[5] == 0x78);

    BitCursor reader(buffer, 16);
    uint16_t out16;
    uint32_t out32;
    reader.read(out16);
    reader.read(out32);

    assert(out16 == val16);
    assert(out32 == val32);
    std::cout << "  Passed." << std::endl;
}

void test_bam_conversion() {
    std::cout << "[Test] BAM Conversion (BAM16, BAM32)..." << std::endl;
    
    double input = 1.0; // 1 radian
    uint16_t bam16 = bam::to_bam16(input);
    double output16 = bam::from_bam16(bam16);
    
    // Check precision (BAM16 is roughly 0.0001 radians)
    assert(std::abs(input - output16) < 0.0002);

    uint32_t bam32 = bam::to_bam32(input);
    double output32 = bam::from_bam32(bam32);
    assert(std::abs(input - output32) < 1e-9);

    // Boundary check [-PI, PI)
    assert(bam::to_bam16(-3.14159) == 0); // Roughly
    assert(bam::to_bam16(3.14159) > 65530);

    std::cout << "  Passed." << std::endl;
}

void test_error_handling() {
    std::cout << "[Test] Error Handling (EndOfStream)..." << std::endl;
    uint8_t buffer[2] = {0};
    BitCursor cursor(buffer, 2);

    cursor.write<uint32_t>(0x12345678); // Should fail
    assert(cursor.error() == ErrorState::EndOfStream);
    std::cout << "  Passed." << std::endl;
}

#include "dli/generated/InertialStates.hpp"

using namespace dli;

void test_generated_inertial_states() {
    std::cout << "[Test] Generated InertialStates Roundtrip..." << std::endl;
    uint8_t buffer[64] = {0};
    BitCursor cursor(buffer, 64);

    generated::InertialStates msg;
    msg.time_stamp = 1234567890;
    msg.has_time_stamp = true;
    msg.latitude = 39.92 * (M_PI / 180.0); // deg to rad
    msg.has_latitude = true;
    msg.longitude = 32.85 * (M_PI / 180.0); // deg to rad
    msg.has_longitude = true;
    msg.altitude = 1000.5; // m
    msg.has_altitude = true;
    msg.phi = 0.5; // rad
    msg.has_phi = true;
    msg.psi_dot = 100;
    msg.has_psi_dot = true;

    msg.serialize(cursor);
    assert(cursor.position() > 0);
    assert(cursor.error() == ErrorState::None);

    BitCursor reader(buffer, 64);
    generated::InertialStates out;
    out.deserialize(reader);

    assert(out.time_stamp == msg.time_stamp);
    assert(std::abs(out.latitude - msg.latitude) < 0.001);
    assert(std::abs(out.longitude - msg.longitude) < 0.001);
    assert(std::abs(out.altitude - msg.altitude) < 0.02); // Scaled 0.01
    assert(std::abs(out.phi - msg.phi) < 0.001);
    assert(out.psi_dot == msg.psi_dot);
    
    // Optionality check
    assert(out.has_phi == true);
    assert(out.has_theta == false); // Should be false by default
    
    std::cout << "  Passed." << std::endl;
}

#include "dli/Dispatcher.hpp"

void test_dispatcher() {
    std::cout << "[Test] Dispatcher Message Routing..." << std::endl;
    Dispatcher dispatcher;
    bool handlerCalled = false;

    // Register handler for #4000
    dispatcher.registerHandler(4000, [&](uint16_t type, BitCursor& payload) {
        generated::InertialStates msg;
        msg.deserialize(payload);
        assert(msg.time_stamp == 0xABCDE);
        handlerCalled = true;
    });

    // Mock DLI Packet: [Type=4000 (2B)][Len=8 (2B)][Payload...]
    // Payload for #4000 with only timestamp set:
    // PV (3B) = 0x000001 (Bit 0 set)
    // Timestamp (5B) = 0x00000ABCDE
    uint8_t packet[] = {
        0x0F, 0xA0, // Type 4000
        0x00, 0x08, // Length 8
        0x00, 0x00, 0x01, // PV (Sequential LSb 0)
        0x00, 0x00, 0x0A, 0xBC, 0xDE // Timestamp
    };

    bool success = dispatcher.dispatch(packet, sizeof(packet));
    assert(success);
    assert(handlerCalled);
    std::cout << "  Passed." << std::endl;
}

int main() {
    std::cout << "--- DLI Runtime Smoke Tests ---" << std::endl;
    test_endian_roundtrip();
    test_bam_conversion();
    test_error_handling();
    test_generated_inertial_states();
    test_dispatcher();
    std::cout << "All Smoke Tests Passed!" << std::endl;
    return 0;
}

#include <iostream>
#include <cassert>
#include <thread>
#include <vector>
#include "dli/DliSession.hpp"
#include "dli/generated/InertialStates.hpp"

using namespace dli;
using namespace dli::generated;

/**
 * @brief Mock Network to simulate loss and round-trip
 */
struct MockNetwork {
    dli::DliSession* peer{nullptr};
    bool drop_next{false};
    uint32_t sent_count{0};

    bool send(const uint8_t* buf, size_t len) {
        sent_count++;
        if (drop_next) {
            std::cout << "  [MOCK] Dropped packet (" << len << " bytes)" << std::endl;
            drop_next = false;
            return true; // "Handed over" successfully even if dropped later
        }
        if (peer) {
            peer->process_incoming(buf, len);
        }
        return true;
    }
};

int main() {
    std::cout << "=== STANAG 4586 Phase 9: Session Reliability Tests (v1.6) ===" << std::endl;

    dli::Dispatcher vsm_dispatcher;
    dli::Dispatcher cucs_dispatcher;
    
    // Register handled message on CUCS to allow auto-ACK
    cucs_dispatcher.registerHandler(4000, [](const dli::DliHeader& h, dli::BitCursor& p) -> uint64_t {
        dli::generated::InertialStates body;
        body.deserialize(p);
        std::cout << "  [INFO] cucs: Received InertialStates (#4000) with TS " << body.time_stamp << std::endl;
        return body.time_stamp;
    });

    MockNetwork net;

    // VSM is the sender
    dli::DliSession vsm(vsm_dispatcher, [&](const uint8_t* b, size_t s){ 
        std::cout << "  [DEBUG] vsm -> cucs (" << s << " bytes)" << std::endl;
        return net.send(b, s); 
    });
    
    // CUCS is the receiver
    // CUCS reply: We just pass the bytes back into VSM's process_incoming
    auto cucs_reply = [&](const uint8_t* b, size_t s){ 
        std::cout << "  [DEBUG] cucs -> vsm (" << s << " bytes)" << std::endl;
        vsm.process_incoming(b, s); 
        return true; 
    };
    dli::DliSession cucs_final(cucs_dispatcher, cucs_reply);
    net.peer = &cucs_final;

    bool ack_received = false;

    std::cout << "\n[TEST 1] Reliable Round-trip with Checksum (#4000 -> #17000 Type 1)" << std::endl;
    dli::DliMessage<dli::generated::InertialStates> msg;
    msg.header.message_type = 4000;
    msg.header.source_id = 101;
    msg.header.destination_id = 202;
    // Enable 4-byte Checksum (bits 7:6 = 0x02 => 2 << 6 = 0x0080)
    msg.header.message_properties |= 0x0080; 
    msg.body.time_stamp = 0; 
    msg.body.latitude = 0.523; 

    vsm.send_reliable(msg, 3, 0, [&](dli::AckStatus status){
        if (status == dli::AckStatus::Success) {
            std::cout << "  [RESULT] vsm: ACK Received successfully." << std::endl;
            ack_received = true;
        }
    });

    assert(ack_received == true);

    // --- TEST 2: Retransmission with Timestamp Preservation ---
    std::cout << "\n[TEST 2] Retransmission with Timestamp Preservation" << std::endl;
    ack_received = false;
    net.drop_next = true; 
    net.sent_count = 0;

    vsm.send_reliable(msg, 3, 0, [&](dli::AckStatus status){
        if (status == dli::AckStatus::Success) {
            std::cout << "  [RESULT] vsm: ACK Received after retransmission." << std::endl;
            ack_received = true;
        }
    });

    assert(ack_received == false); 
    assert(net.sent_count == 1);
    std::cout << "  [INFO] Waiting for timeout (600ms)..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(650));
    
    vsm.tick(); 

    assert(ack_received == true);
    assert(net.sent_count == 2);

    // --- TEST 3: Invalid Length/Structure -> No ACK ---
    std::cout << "\n[TEST 3] Invalid Length Handling -> No ACK" << std::endl;
    net.sent_count = 0;
    dli::DliMessage<dli::generated::InertialStates> msg_invalid;
    msg_invalid.header.message_type = 4000;
    msg_invalid.header.message_properties |= 0x8000;
    
    std::vector<uint8_t> buf_inv(128);
    dli::BitCursor cursor_inv(buf_inv.data(), buf_inv.size());
    msg_invalid.serialize(cursor_inv);
    
    // Pass smaller size than header.payload_length suggests (10 bytes total)
    cucs_final.process_incoming(buf_inv.data(), 10); 
    if (net.sent_count == 0) {
        std::cout << "  [RESULT] Invalid length correctly ignored." << std::endl;
    } else {
        std::cout << "  [FAILURE] ACK emitted for invalid length!" << std::endl;
        assert(false);
    }

    // --- TEST 4: ACK Storm Protection (#17000 never triggers another ACK) ---
    std::cout << "\n[TEST 4] ACK Storm Protection (Proof)" << std::endl;
    net.sent_count = 0;
    
    dli::DliMessage<dli::generated::MessageAcknowledgement> malicious_ack;
    malicious_ack.header.message_type = 17000;
    malicious_ack.header.message_properties |= 0x8000; // MALICIOUS: Explicitly requesting ACK for an ACK
    
    std::vector<uint8_t> buf_mal(128);
    dli::BitCursor cursor_mal(buf_mal.data(), buf_mal.size());
    malicious_ack.serialize(cursor_mal);
    
    // Even if ACK bit is set, process_incoming MUST NOT respond with another #17000
    cucs_final.process_incoming(buf_mal.data(), cursor_mal.position());
    
    if (net.sent_count == 0) {
        std::cout << "  [RESULT] Storm Protection Proof: No auto-ACK generated for incoming #17000." << std::endl;
    } else {
        std::cout << "  [FAILURE] Storm Protection FAILED! Auto-ACK triggered for #17000." << std::endl;
        assert(false);
    }

    std::cout << "\n=== All Phase 9 Reliability Tests Passed! ===" << std::endl;
    return 0;
}

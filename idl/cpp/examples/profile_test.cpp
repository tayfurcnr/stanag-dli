#include <dli/protocol/Dispatcher.hpp>
#include <dli/protocol/Profile.hpp>
#include <dli/generated/profiles/Profiles.hpp>
#include <dli/core/ILogger.hpp>
#include <iostream>
#include <cassert>

using namespace dli;

int main() {
    Logger::info("=== AEP-84 Profile Conformance Test Starting ===");

    Dispatcher dispatcher;

    // 1. Setup Generated LOI 4 Profile (Control & Monitor)
    auto loi4 = dli::generated::Profiles::LOI4_UA_Control();
    
    dispatcher.setProfile(loi4);

    // 2. Prepare mock buffers
    uint8_t buffer4000[20] = {0}; // Min header size
    buffer4000[12] = (4000 >> 8) & 0xFF; // Message Type High
    buffer4000[13] = 4000 & 0xFF;        // Message Type Low

    uint8_t buffer2016[20] = {0};
    buffer2016[12] = (2016 >> 8) & 0xFF;
    buffer2016[13] = 2016 & 0xFF;

    // 3. Register a dummy handler
    bool handlerTriggered = false;
    dispatcher.registerHandler(4000, [&](const DliHeader&, BitCursor&) {
        handlerTriggered = true;
        return 0;
    });

    dispatcher.registerHandler(2016, [&](const DliHeader&, BitCursor&) {
        Logger::error("CRITICAL FAILURE: Handler for unauthorized message #2016 was triggered!");
        exit(1);
        return 0;
    });

    // 4. Dispatch Telemetry (Should be Allowed)
    Logger::info("Dispatching Authorized Message #4000...");
    auto res1 = dispatcher.dispatch(buffer4000, 20);
    assert(res1.has_value());
    assert(handlerTriggered == true);
    Logger::info("Result: SUCCESS (Message Allowed)");

    Logger::info("Dispatching Unauthorized Message #2016...");
    auto res2 = dispatcher.dispatch(buffer2016, 20);
    assert(!res2.has_value());
    Logger::info("Result: SUCCESS (Message Rejected by DLI Policy)");

    // 6. Test Custom Tactical Profile
    Logger::info("--- Switching to Custom Tactical Profile ---");
    auto custom = dli::generated::Profiles::Custom_Tactical();
    dispatcher.setProfile(custom);

    // Heartbeat (#16002) should be allowed (manual include)
    uint8_t buffer16002[20] = {0};
    buffer16002[12] = (16002 >> 8) & 0xFF;
    buffer16002[13] = 16002 & 0xFF;
    
    dispatcher.registerHandler(16002, [](const DliHeader&, BitCursor&) { return 0; });
    
    Logger::info("Dispatching Heartbeat #16002 (Manual Include)...");
    assert(dispatcher.dispatch(buffer16002, 20).has_value());
    Logger::info("Result: SUCCESS");

    // VehicleID (#3) should be rejected (manual exclude despite being in SystemID group)
    uint8_t buffer3[20] = {0};
    buffer3[12] = (3 >> 8) & 0xFF;
    buffer3[13] = 3 & 0xFF;
    
    Logger::info("Dispatching VehicleID #3 (Manual Exclude)...");
    assert(!dispatcher.dispatch(buffer3, 20).has_value());
    Logger::info("Result: SUCCESS (Rejected as expected)");

    Logger::info("=== AEP-84 Profile Conformance Test PASSED! ===");
    return 0;
}

#include <dli/protocol/Dispatcher.hpp>
#include <dli/protocol/Profile.hpp>
#include <dli/core/ILogger.hpp>
#include <iostream>
#include <cassert>

using namespace dli;

int main() {
    Logger::info("=== AEP-84 Profile Conformance Test Starting ===");

    Dispatcher dispatcher;

    // 1. Setup LOI 2 (Monitor Only) Profile
    Profile loi2("LOI2_Monitor", 2);
    loi2.allow(4000); // Allow Inertial States (Telemetry)
    
    // Note: ID 02016 (Vehicle Operating Mode Command) is NOT allowed in LOI 2.
    
    dispatcher.setProfile(loi2);

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

    // 5. Dispatch Command (Should be Rejected)
    Logger::info("Dispatching Unauthorized Message #2016...");
    auto res2 = dispatcher.dispatch(buffer2016, 20);
    assert(!res2.has_value());
    Logger::info("Result: SUCCESS (Message Rejected by DLI Policy)");

    Logger::info("=== AEP-84 Profile Conformance Test PASSED! ===");
    return 0;
}

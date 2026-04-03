#pragma once

#include <dli/protocol/Profile.hpp>
#include <vector>

namespace dli {
namespace generated {

/**
 * @brief Auto-generated Profiles based on AEP-84 definitions.
 */
class Profiles {
public:
    static Profile Custom_Tactical() {
        Profile p("Custom_Tactical_Profile", 3);
        p.allow(1); // CUCSAuthorisationRequest (SystemID)
        p.allow(2); // VSMAuthorisationResponse (SystemID)
        p.allow(3); // VehicleID (SystemID)
        p.allow(4); // PositiveHandoverAuthorisationRequest (SystemID)
        p.allow(5); // PositiveHandoverAuthorisationGranted (SystemID)
        p.allow(4000); // InertialStates (FlightVehiclePayloadRelevantStatus)
        p.allow(4001); // FromToNextWaypointStates (FlightVehiclePayloadRelevantStatus)
        p.allow(16002); // Manual include
        p.deny(3); // Manual exclude
        return p;
    }

    static Profile LOI2_Monitor() {
        Profile p("LOI2_Monitor_Profile", 2);
        p.allow(1); // CUCSAuthorisationRequest (SystemID)
        p.allow(2); // VSMAuthorisationResponse (SystemID)
        p.allow(3); // VehicleID (SystemID)
        p.allow(4); // PositiveHandoverAuthorisationRequest (SystemID)
        p.allow(5); // PositiveHandoverAuthorisationGranted (SystemID)
        return p;
    }

    static Profile LOI4_UA_Control() {
        Profile p("LOI4_UA_Control_Profile", 4);
        p.allow(1); // CUCSAuthorisationRequest (SystemID)
        p.allow(2); // VSMAuthorisationResponse (SystemID)
        p.allow(3); // VehicleID (SystemID)
        p.allow(4); // PositiveHandoverAuthorisationRequest (SystemID)
        p.allow(5); // PositiveHandoverAuthorisationGranted (SystemID)
        p.allow(4000); // InertialStates (FlightVehiclePayloadRelevantStatus)
        p.allow(4001); // FromToNextWaypointStates (FlightVehiclePayloadRelevantStatus)
        return p;
    }

};

} // namespace generated
} // namespace dli
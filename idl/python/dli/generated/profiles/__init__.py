from dli.protocol import Profile


class Profiles:
    @staticmethod
    def Custom_Tactical():
        p = Profile('Custom_Tactical_Profile', 3)
        p.allow(1)  # CUCSAuthorisationRequest (SystemID)
        p.allow(2)  # VSMAuthorisationResponse (SystemID)
        p.allow(3)  # VehicleID (SystemID)
        p.allow(4)  # PositiveHandoverAuthorisationRequest (SystemID)
        p.allow(5)  # PositiveHandoverAuthorisationGranted (SystemID)
        p.allow(4000)  # InertialStates (FlightVehiclePayloadRelevantStatus)
        p.allow(4001)  # FromToNextWaypointStates (FlightVehiclePayloadRelevantStatus)
        p.allow(16002)  # Manual include
        p.deny(3)  # Manual exclude
        return p

    @staticmethod
    def LOI2_Monitor():
        p = Profile('LOI2_Monitor_Profile', 2)
        p.allow(1)  # CUCSAuthorisationRequest (SystemID)
        p.allow(2)  # VSMAuthorisationResponse (SystemID)
        p.allow(3)  # VehicleID (SystemID)
        p.allow(4)  # PositiveHandoverAuthorisationRequest (SystemID)
        p.allow(5)  # PositiveHandoverAuthorisationGranted (SystemID)
        p.allow(3002)  # VehicleOperatingStates (FlightVehicleStatus)
        p.allow(3007)  # EngineOperatingStates (FlightVehicleStatus)
        return p

    @staticmethod
    def LOI4_UA_Control():
        p = Profile('LOI4_UA_Control_Profile', 4)
        p.allow(1)  # CUCSAuthorisationRequest (SystemID)
        p.allow(2)  # VSMAuthorisationResponse (SystemID)
        p.allow(3)  # VehicleID (SystemID)
        p.allow(4)  # PositiveHandoverAuthorisationRequest (SystemID)
        p.allow(5)  # PositiveHandoverAuthorisationGranted (SystemID)
        p.allow(3002)  # VehicleOperatingStates (FlightVehicleStatus)
        p.allow(3007)  # EngineOperatingStates (FlightVehicleStatus)
        p.allow(4000)  # InertialStates (FlightVehiclePayloadRelevantStatus)
        p.allow(4001)  # FromToNextWaypointStates (FlightVehiclePayloadRelevantStatus)
        return p


__all__ = ["Profiles"]
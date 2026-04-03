name: Custom_Tactical_Profile
loi: 3
include_groups:
  - SystemID
  - FlightVehiclePayloadRelevantStatus
include_messages:
  - 16002 # Heartbeat (Manual Include)
exclude_messages:
  - 3     # VehicleID (Manual Exclude)

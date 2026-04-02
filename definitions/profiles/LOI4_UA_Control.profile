# LOI 4 Profile - UA Control
# Chapter 3: Requires full control & monitor capabilities

name: LOI4_UA_Control_Profile
loi: 4
mode: control_and_monitor
strict: true

include_groups:
  - SystemID
  - FlightVehicleStatus
  - FlightVehiclePayloadRelevantStatus
  - FlightVehicleCommand
  - SubsystemStatus

exclude_groups:
  - WeaponsCommand
  - PayloadCommand # Assuming specific platform profile

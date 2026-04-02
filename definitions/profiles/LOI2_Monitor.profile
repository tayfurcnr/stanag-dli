# LOI 2 Profile - Monitor Only
# Chapter 3: Payload dependencies apply
# Note: This profile is a project-tailored LOI2 profile, not a minimum normative LOI2 set.

name: LOI2_Monitor_Profile
loi: 2
mode: monitor_only
strict: true

include_groups:
  - SystemID
  - FlightVehicleStatus
  - SubsystemStatus

# Note: PayloadStatus may be conditional based on platform
optional_groups:
  - DataLinkStatus
  - FlightVehiclePayloadRelevantStatus

exclude_groups:
  - FlightVehicleCommand
  - PayloadCommand
  - WeaponsCommand

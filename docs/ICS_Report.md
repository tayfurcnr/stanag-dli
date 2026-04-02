# DLI Interface Control Sheet (ICS) - v1.0 (Draft Aligned to STANAG 4586)

> [!IMPORTANT]
> This document is a framework-generated ICS draft aligned to STANAG 4586. All PV bits are sequential LSB 0.

## 1. Message Catalog

| ID | Name | Group | Fields | Source | Direction | Latency | Payload Length (Max) |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | CUCSAuthorisationRequest | SystemID | 18 | CUCS | CUCS -> UA/VSM | 1000ms | 39 B |
| 2 | VSMAuthorisationResponse | SystemID | 19 | VSM | VSM -> CUCS | 1000ms | 41 B |
| 3 | VehicleID | SystemID | 9 | VSM / UA | VSM/UA -> CUCS | 1000ms | 88 B |
| 4 | PositiveHandoverAuthorisationRequest | SystemID | 16 | CUCS | CUCS -> UA/VSM | 1000ms | 40 B |
| 5 | PositiveHandoverAuthorisationGranted | SystemID | 15 | VSM / UA | VSM/UA -> CUCS | 1000ms | 36 B |
| 2007 | UnmannedAircraftLights | VehicleControl | 2 | CUCS | CUCS -> UA/VSM | 1000ms | 7 B |
| 2010 | UAStickCommand | VehicleControl | 13 | CUCS | CUCS -> UA/VSM | 50ms | 19 B |
| 2016 | VehicleOperatingModeCommand | VehicleControl | 23 | CUCS | CUCS -> UA/VSM | 100ms | 46 B |
| 2017 | LoiterConfiguration | VehicleControl | 11 | CUCS | CUCS -> UA/VSM | 100ms | 21 B |
| 3001 | VehicleOperatingModeReport | VehicleStatus | 2 | VSM / UA | VSM/UA -> CUCS | 100ms | 7 B |
| 3002 | VehicleOperatingStates | VehicleStatus | 18 | VSM / UA | VSM/UA -> CUCS | 100ms | 35 B |
| 3004 | LoiterConfigurationReport | VehicleStatus | 10 | VSM / UA | VSM/UA -> CUCS | 100ms | 20 B |
| 3006 | VehicleLightsState | VehicleStatus | 2 | VSM / UA | VSM/UA -> CUCS | 1000ms | 7 B |
| 3011 | UAStickStatus | VehicleStatus | 13 | VSM / UA | VSM/UA -> CUCS | 50ms | 19 B |
| 4000 | InertialStates | FlightVehiclePayloadRelevantStatus | 18 | UA / VSM | UA/VSM -> CUCS | 500ms | 46 B |
| 4001 | FromToNextWaypointStates | FlightVehiclePayloadRelevantStatus | 21 | UA / VSM | UA/VSM -> CUCS | 500ms | 63 B |
| 13002 | UAPositionWaypoint | Mission | 17 | CUCS / VSM | Bi-directional | 1000ms | 34 B |
| 16002 | Heartbeat | DataLinkStatus | 1 | VSM / UA / CUCS | Bi-directional | 1000ms | 6 B |
| 17000 | MessageAcknowledgement | Miscellaneous | 4 | UA / VSM / CUCS | Bi-directional | 500ms | 14 B |

## 2. Detailed Bit Layouts

### Message #1: CUCSAuthorisationRequest
**Group:** SystemID | **Source:** CUCS | **Direction:** CUCS -> UA/VSM | **Latency:** 1000ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint24 | 3 B | Bitmapped | - | M |
| 3 | 0 | time_stamp | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 8 | 1 | vsm_id | uint32 | 4 B | uint32 | - | O |
| 12 | 2 | data_link_id | uint32 | 4 B | uint32 | - | O |
| 16 | 3 | vehicle_type | uint16 | 2 B | uint16 | enum | O |
| 18 | 4 | vehicle_subtype | uint16 | 2 B | uint16 | - | O |
| 20 | 5 | requested_handover_loi | uint8 | 1 B | uint8 | Bitmapped | O |
| 21 | 6 | requested_handover_access | uint8 | 1 B | uint8 | enum | O |
| 22 | 7 | requested_flight_mode | uint8 | 1 B | uint8 | enum | O |
| 23 | 8 | controlled_stn_1_16 | uint16 | 2 B | uint16 | Bitmapped | O |
| 25 | 9 | component_number | uint16 | 2 B | uint16 | Bitmapped | O |
| 27 | 10 | sub_component_number | uint16 | 2 B | uint16 | Bitmapped | O |
| 29 | 11 | payload_type | uint8 | 1 B | uint8 | enum | O |
| 30 | 12 | asset_mode | uint8 | 1 B | uint8 | enum | O |
| 31 | 13 | wait_for_transition_coord | uint8 | 1 B | uint8 | enum | O |
| 32 | 14 | cucs_type | uint16 | 2 B | uint16 | enum | O |
| 34 | 15 | cucs_subtype | uint16 | 2 B | uint16 | - | O |
| 36 | 16 | presence_vector_support | uint8 | 1 B | uint8 | enum | O |
| 37 | 17 | controlled_stn_17_32 | uint16 | 2 B | uint16 | Bitmapped | O |

### Message #2: VSMAuthorisationResponse
**Group:** SystemID | **Source:** VSM | **Direction:** VSM -> CUCS | **Latency:** 1000ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint24 | 3 B | Bitmapped | - | M |
| 3 | 0 | time_stamp | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 8 | 1 | vsm_id | uint32 | 4 B | uint32 | - | O |
| 12 | 2 | data_link_id | uint32 | 4 B | uint32 | - | O |
| 16 | 3 | access_authorized | uint8 | 1 B | uint8 | enum | O |
| 17 | 4 | access_granted | uint8 | 1 B | uint8 | enum | O |
| 18 | 5 | loi_authorized | uint8 | 1 B | uint8 | Bitmapped | O |
| 19 | 6 | loi_granted | uint8 | 1 B | uint8 | Bitmapped | O |
| 20 | 7 | flight_modes_granted | uint32 | 4 B | uint32 | Bitmapped | O |
| 24 | 8 | controlled_stn_1_16 | uint16 | 2 B | uint16 | Bitmapped | O |
| 26 | 9 | component_number | uint16 | 2 B | uint16 | Bitmapped | O |
| 28 | 10 | sub_component_number | uint16 | 2 B | uint16 | Bitmapped | O |
| 30 | 11 | payload_type | uint8 | 1 B | uint8 | enum | O |
| 31 | 12 | access_requested | uint8 | 1 B | uint8 | Bitmapped | O |
| 32 | 13 | vehicle_type | uint16 | 2 B | uint16 | enum | O |
| 34 | 14 | vehicle_subtype | uint16 | 2 B | uint16 | - | O |
| 36 | 15 | cucs_type | uint8 | 1 B | uint8 | enum | O |
| 37 | 16 | cucs_subtype | uint8 | 1 B | uint8 | - | O |
| 38 | 17 | presence_vector_support | uint8 | 1 B | uint8 | enum | O |
| 39 | 18 | controlled_stn_17_32 | uint16 | 2 B | uint16 | Bitmapped | O |

### Message #3: VehicleID
**Group:** SystemID | **Source:** VSM / UA | **Direction:** VSM/UA -> CUCS | **Latency:** 1000ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint16 | 2 B | Bitmapped | - | M |
| 2 | 0 | time_stamp | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 7 | 1 | vsm_id | uint32 | 4 B | uint32 | - | O |
| 11 | 2 | vehicle_id_update | uint32 | 4 B | uint32 | - | O |
| 15 | 3 | vehicle_type | uint16 | 2 B | uint16 | enum | O |
| 17 | 4 | vehicle_subtype | uint16 | 2 B | uint16 | - | O |
| 19 | 5 | owning_id | uint8 | 1 B | uint8 | enum | O |
| 20 | 6 | tail_number | Char16 | 16 B | Char16 | - | O |
| 36 | 7 | mission_id | Char20 | 20 B | Char20 | - | O |
| 56 | 8 | atc_call_sign | Char32 | 32 B | Char32 | - | O |

### Message #4: PositiveHandoverAuthorisationRequest
**Group:** SystemID | **Source:** CUCS | **Direction:** CUCS -> UA/VSM | **Latency:** 1000ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint16 | 2 B | Bitmapped | - | M |
| 2 | 0 | time_stamp | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 7 | 1 | vsm_id | uint32 | 4 B | uint32 | - | O |
| 11 | 2 | data_link_id | uint32 | 4 B | uint32 | - | O |
| 15 | 3 | vehicle_type | uint16 | 2 B | uint16 | enum | O |
| 17 | 4 | vehicle_subtype | uint16 | 2 B | uint16 | - | O |
| 19 | 5 | requested_handover_loi | uint8 | 1 B | uint8 | Bitmapped | O |
| 20 | 6 | flight_mode_offset | uint8 | 1 B | uint8 | - | O |
| 21 | 7 | requested_flight_mode | uint32 | 4 B | uint32 | Bitmapped | O |
| 25 | 8 | controlled_stn_1_16 | uint16 | 2 B | uint16 | Bitmapped | O |
| 27 | 9 | component_number | uint16 | 2 B | uint16 | Bitmapped | O |
| 29 | 10 | sub_component_number | uint16 | 2 B | uint16 | Bitmapped | O |
| 31 | 11 | requesting_cucs_type | uint8 | 1 B | uint8 | enum | O |
| 32 | 12 | requesting_cucs_subtype | uint8 | 1 B | uint8 | - | O |
| 33 | 13 | requesting_cucs_id | uint32 | 4 B | uint32 | - | O |
| 37 | 14 | presence_vector_support | uint8 | 1 B | uint8 | enum | O |
| 38 | 15 | controlled_stn_17_32 | uint16 | 2 B | uint16 | Bitmapped | O |

### Message #5: PositiveHandoverAuthorisationGranted
**Group:** SystemID | **Source:** VSM / UA | **Direction:** VSM/UA -> CUCS | **Latency:** 1000ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint16 | 2 B | Bitmapped | - | M |
| 2 | 0 | time_stamp | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 7 | 1 | vsm_id | uint32 | 4 B | uint32 | - | O |
| 11 | 2 | data_link_id | uint32 | 4 B | uint32 | - | O |
| 15 | 3 | loi_authorized | uint8 | 1 B | uint8 | Bitmapped | O |
| 16 | 4 | flight_mode_offset | uint8 | 1 B | uint8 | - | O |
| 17 | 5 | flight_modes_authorized | uint32 | 4 B | uint32 | Bitmapped | O |
| 21 | 6 | controlled_stn_1_16 | uint16 | 2 B | uint16 | Bitmapped | O |
| 23 | 7 | component_number | uint16 | 2 B | uint16 | Bitmapped | O |
| 25 | 8 | sub_component_number | uint16 | 2 B | uint16 | Bitmapped | O |
| 27 | 9 | vehicle_type | uint16 | 2 B | uint16 | enum | O |
| 29 | 10 | vehicle_subtype | uint16 | 2 B | uint16 | - | O |
| 31 | 11 | cucs_type | uint8 | 1 B | uint8 | enum | O |
| 32 | 12 | cucs_subtype | uint8 | 1 B | uint8 | - | O |
| 33 | 13 | presence_vector_support | uint8 | 1 B | uint8 | enum | O |
| 34 | 14 | controlled_stn_17_32 | uint16 | 2 B | uint16 | Bitmapped | O |

### Message #2007: UnmannedAircraftLights
**Group:** VehicleControl | **Source:** CUCS | **Direction:** CUCS -> UA/VSM | **Latency:** 1000ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint8 | 1 B | Bitmapped | - | M |
| 1 | 0 | time_stamp | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 6 | 1 | ua_lights | uint8 | 1 B | uint8 | Bitmapped | O |

### Message #2010: UAStickCommand
**Group:** VehicleControl | **Source:** CUCS | **Direction:** CUCS -> UA/VSM | **Latency:** 50ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint16 | 2 B | Bitmapped | - | M |
| 2 | 0 | time_stamp | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 7 | 1 | lateral_stick | int8 | 1 B | int8 | - | O |
| 8 | 2 | longitudinal_stick | int8 | 1 B | int8 | - | O |
| 9 | 3 | rotational_stick | int8 | 1 B | int8 | - | O |
| 10 | 4 | throttle_stick_eng1 | uint8 | 1 B | uint8 | - | O |
| 11 | 5 | pitch_stick_eng1 | int8 | 1 B | int8 | - | O |
| 12 | 6 | throttle_stick_eng2 | uint8 | 1 B | uint8 | - | O |
| 13 | 7 | pitch_stick_eng2 | int8 | 1 B | int8 | - | O |
| 14 | 8 | throttle_stick_eng3 | uint8 | 1 B | uint8 | - | O |
| 15 | 9 | pitch_stick_eng3 | int8 | 1 B | int8 | - | O |
| 16 | 10 | throttle_stick_eng4 | uint8 | 1 B | uint8 | - | O |
| 17 | 11 | pitch_stick_eng4 | int8 | 1 B | int8 | - | O |
| 18 | 12 | taxi_stick | int8 | 1 B | int8 | - | O |

### Message #2016: VehicleOperatingModeCommand
**Group:** VehicleControl | **Source:** CUCS | **Direction:** CUCS -> UA/VSM | **Latency:** 100ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint24 | 3 B | Bitmapped | - | M |
| 3 | 0 | time_stamp | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 8 | 1 | flight_path_control_mode | uint8 | 1 B | uint8 | enum | O |
| 9 | 2 | altitude_command_type | uint8 | 1 B | uint8 | enum | O |
| 10 | 3 | commanded_altitude | int24 | 1 B | int24 | m | O |
| 11 | 4 | commanded_vertical_speed | int16 | 2 B | int16 | m/s | O |
| 13 | 5 | heading_command_type | uint8 | 1 B | uint8 | enum | O |
| 14 | 6 | heading_reference | uint8 | 1 B | uint8 | enum | O |
| 15 | 7 | commanded_heading | BAM16 | 2 B | BAM16 | rad | O |
| 17 | 8 | commanded_course | BAM16 | 2 B | BAM16 | rad | O |
| 19 | 9 | commanded_turn_rate | int16 | 2 B | int16 | rad/s | O |
| 21 | 10 | commanded_roll_rate | int16 | 2 B | int16 | rad/s | O |
| 23 | 11 | commanded_roll | BAM16 | 2 B | BAM16 | rad | O |
| 25 | 12 | commanded_speed | uint16 | 2 B | uint16 | m/s | O |
| 27 | 13 | speed_type | uint8 | 1 B | uint8 | enum | O |
| 28 | 14 | commanded_waypoint_number | uint16 | 2 B | uint16 | - | O |
| 30 | 15 | altimeter_setting | uint16 | 2 B | uint16 | Pa | O |
| 32 | 16 | altitude_type | uint8 | 1 B | uint8 | enum | O |
| 33 | 17 | loiter_latitude | BAM32 | 4 B | BAM32 | rad | O |
| 37 | 18 | loiter_longitude | BAM32 | 4 B | BAM32 | rad | O |
| 41 | 19 | loiter_altitude_change | uint8 | 1 B | uint8 | enum | O |
| 42 | 20 | thrust_direction | BAM16 | 2 B | BAM16 | rad | O |
| 44 | 21 | thrust | uint8 | 1 B | uint8 | % | O |
| 45 | 22 | activity_id | uint24 | 1 B | uint24 | - | O |

### Message #2017: LoiterConfiguration
**Group:** VehicleControl | **Source:** CUCS | **Direction:** CUCS -> UA/VSM | **Latency:** 100ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint16 | 2 B | Bitmapped | - | M |
| 2 | 0 | time_stamp | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 7 | 1 | loiter_type | uint8 | 1 B | uint8 | enum | O |
| 8 | 2 | loiter_radius | uint16 | 2 B | uint16 | m | O |
| 10 | 3 | loiter_length | uint16 | 2 B | uint16 | m | O |
| 12 | 4 | loiter_length_units | uint8 | 1 B | uint8 | enum | O |
| 13 | 5 | loiter_bearing | BAM16 | 2 B | BAM16 | rad | O |
| 15 | 6 | loiter_direction | uint8 | 1 B | uint8 | enum | O |
| 16 | 7 | flying_behaviour | uint8 | 1 B | uint8 | enum | O |
| 17 | 8 | loiter_duration | uint16 | 2 B | uint16 | - | O |
| 19 | 9 | loiter_duration_units | uint8 | 1 B | uint8 | enum | O |
| 20 | 10 | activity_id | uint24 | 1 B | uint24 | - | O |

### Message #3001: VehicleOperatingModeReport
**Group:** VehicleStatus | **Source:** VSM / UA | **Direction:** VSM/UA -> CUCS | **Latency:** 100ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint8 | 1 B | Bitmapped | - | M |
| 1 | 0 | time_stamp | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 6 | 1 | flight_path_control_mode | uint8 | 1 B | uint8 | enum | O |

### Message #3002: VehicleOperatingStates
**Group:** VehicleStatus | **Source:** VSM / UA | **Direction:** VSM/UA -> CUCS | **Latency:** 100ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint24 | 3 B | Bitmapped | - | M |
| 3 | 0 | time_stamp | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 8 | 1 | commanded_altitude | int24 | 1 B | int24 | m | O |
| 9 | 2 | altitude_type | uint8 | 1 B | uint8 | enum | O |
| 10 | 3 | commanded_heading | BAM16 | 2 B | BAM16 | rad | O |
| 12 | 4 | commanded_course | BAM16 | 2 B | BAM16 | rad | O |
| 14 | 5 | commanded_turn_rate | int16 | 2 B | int16 | rad/s | O |
| 16 | 6 | commanded_roll_rate | int16 | 2 B | int16 | rad/s | O |
| 18 | 7 | commanded_speed | uint16 | 2 B | uint16 | m/s | O |
| 20 | 8 | speed_type | uint8 | 1 B | uint8 | enum | O |
| 21 | 9 | power_level | int8 | 1 B | int8 | % | O |
| 22 | 10 | bingo_energy | uint16 | 2 B | uint16 | % | O |
| 24 | 11 | current_energy_level | uint16 | 2 B | uint16 | % | O |
| 26 | 12 | current_energy_usage | uint16 | 2 B | uint16 | %/s | O |
| 28 | 13 | commanded_roll | BAM16 | 2 B | BAM16 | rad | O |
| 30 | 14 | altitude_command_type | uint8 | 1 B | uint8 | enum | O |
| 31 | 15 | heading_command_type | uint8 | 1 B | uint8 | enum | O |
| 32 | 16 | ua_state | uint8 | 1 B | uint8 | enum | O |
| 33 | 17 | thrust_direction | BAM16 | 2 B | BAM16 | rad | O |

### Message #3004: LoiterConfigurationReport
**Group:** VehicleStatus | **Source:** VSM / UA | **Direction:** VSM/UA -> CUCS | **Latency:** 100ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint16 | 2 B | Bitmapped | - | M |
| 2 | 0 | time_stamp | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 7 | 1 | loiter_type | uint8 | 1 B | uint8 | enum | O |
| 8 | 2 | loiter_radius | uint16 | 2 B | uint16 | m | O |
| 10 | 3 | loiter_length | uint16 | 2 B | uint16 | m | O |
| 12 | 4 | loiter_length_units | uint8 | 1 B | uint8 | enum | O |
| 13 | 5 | loiter_bearing | BAM16 | 2 B | BAM16 | rad | O |
| 15 | 6 | loiter_direction | uint8 | 1 B | uint8 | enum | O |
| 16 | 7 | loiter_altitude | int24 | 1 B | int24 | m | O |
| 17 | 8 | altitude_type | uint8 | 1 B | uint8 | enum | O |
| 18 | 9 | loiter_speed | uint16 | 2 B | uint16 | m/s | O |

### Message #3006: VehicleLightsState
**Group:** VehicleStatus | **Source:** VSM / UA | **Direction:** VSM/UA -> CUCS | **Latency:** 1000ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint8 | 1 B | Bitmapped | - | M |
| 1 | 0 | time_stamp | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 6 | 1 | lights_state | uint8 | 1 B | uint8 | Bitmapped | O |

### Message #3011: UAStickStatus
**Group:** VehicleStatus | **Source:** VSM / UA | **Direction:** VSM/UA -> CUCS | **Latency:** 50ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint16 | 2 B | Bitmapped | - | M |
| 2 | 0 | time_stamp | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 7 | 1 | lateral_stick | int8 | 1 B | int8 | - | O |
| 8 | 2 | longitudinal_stick | int8 | 1 B | int8 | - | O |
| 9 | 3 | rotational_stick | int8 | 1 B | int8 | - | O |
| 10 | 4 | throttle_stick_eng1 | uint8 | 1 B | uint8 | - | O |
| 11 | 5 | pitch_stick_eng1 | int8 | 1 B | int8 | - | O |
| 12 | 6 | throttle_stick_eng2 | uint8 | 1 B | uint8 | - | O |
| 13 | 7 | pitch_stick_eng2 | int8 | 1 B | int8 | - | O |
| 14 | 8 | throttle_stick_eng3 | uint8 | 1 B | uint8 | - | O |
| 15 | 9 | pitch_stick_eng3 | int8 | 1 B | int8 | - | O |
| 16 | 10 | throttle_stick_eng4 | uint8 | 1 B | uint8 | - | O |
| 17 | 11 | pitch_stick_eng4 | int8 | 1 B | int8 | - | O |
| 18 | 12 | taxi_stick | int8 | 1 B | int8 | - | O |

### Message #4000: InertialStates
**Group:** FlightVehiclePayloadRelevantStatus | **Source:** UA / VSM | **Direction:** UA/VSM -> CUCS | **Latency:** 500ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint24 | 3 B | Bitmapped | - | M |
| 3 | 0 | time_stamp | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 8 | 1 | latitude | BAM32 | 4 B | BAM32 | - | O |
| 12 | 2 | longitude | BAM32 | 4 B | BAM32 | - | O |
| 16 | 3 | altitude | Altitude | 3 B | int24 (Scaled 0.02m) | m | O |
| 19 | 4 | altitude_type | uint8 | 1 B | uint8 | enum | O |
| 20 | 5 | u_speed | int16 | 2 B | int16 | m/s | O |
| 22 | 6 | v_speed | int16 | 2 B | int16 | m/s | O |
| 24 | 7 | w_speed | int16 | 2 B | int16 | m/s | O |
| 26 | 8 | u_accel | int16 | 2 B | int16 | m/s^2 | O |
| 28 | 9 | v_accel | int16 | 2 B | int16 | m/s^2 | O |
| 30 | 10 | w_accel | int16 | 2 B | int16 | m/s^2 | O |
| 32 | 11 | roll | BAM16 | 2 B | BAM16 | rad | O |
| 34 | 12 | pitch | BAM16 | 2 B | BAM16 | rad | O |
| 36 | 13 | heading | BAM16 | 2 B | BAM16 | rad | O |
| 38 | 14 | roll_rate | int16 | 2 B | int16 | rad/s | O |
| 40 | 15 | pitch_rate | int16 | 2 B | int16 | rad/s | O |
| 42 | 16 | turn_rate | int16 | 2 B | int16 | rad/s | O |
| 44 | 17 | magnetic_variation | BAM16 | 2 B | BAM16 | rad | O |

### Message #4001: FromToNextWaypointStates
**Group:** FlightVehiclePayloadRelevantStatus | **Source:** UA / VSM | **Direction:** UA/VSM -> CUCS | **Latency:** 500ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint24 | 3 B | Bitmapped | - | M |
| 3 | 0 | time_stamp | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 8 | 1 | altitude_type | uint8 | 1 B | uint8 | enum | O |
| 9 | 2 | speed_type | uint8 | 1 B | uint8 | enum | O |
| 10 | 3 | from_waypoint_latitude | BAM32 | 4 B | BAM32 | rad | O |
| 14 | 4 | from_waypoint_longitude | BAM32 | 4 B | BAM32 | rad | O |
| 18 | 5 | from_waypoint_altitude | int24 | 1 B | int24 | m | O |
| 19 | 6 | from_waypoint_time | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 24 | 7 | from_waypoint_number | uint16 | 2 B | uint16 | - | O |
| 26 | 8 | to_waypoint_latitude | BAM32 | 4 B | BAM32 | rad | O |
| 30 | 9 | to_waypoint_longitude | BAM32 | 4 B | BAM32 | rad | O |
| 34 | 10 | to_waypoint_altitude | int24 | 1 B | int24 | m | O |
| 35 | 11 | to_waypoint_speed | uint16 | 2 B | uint16 | m/s | O |
| 37 | 12 | to_waypoint_time | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 42 | 13 | to_waypoint_number | uint16 | 2 B | uint16 | - | O |
| 44 | 14 | next_waypoint_latitude | BAM32 | 4 B | BAM32 | rad | O |
| 48 | 15 | next_waypoint_longitude | BAM32 | 4 B | BAM32 | rad | O |
| 52 | 16 | next_waypoint_altitude | int24 | 1 B | int24 | m | O |
| 53 | 17 | next_waypoint_speed | uint16 | 2 B | uint16 | m/s | O |
| 55 | 18 | next_waypoint_time | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 60 | 19 | next_waypoint_number | uint16 | 2 B | uint16 | - | O |
| 62 | 20 | loiter_valid_for_to_wp | uint8 | 1 B | uint8 | enum | O |

### Message #13002: UAPositionWaypoint
**Group:** Mission | **Source:** CUCS / VSM | **Direction:** Bi-directional | **Latency:** 1000ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint24 | 3 B | Bitmapped | - | M |
| 3 | 0 | time_stamp | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 8 | 1 | waypoint_number | uint16 | 2 B | uint16 | - | O |
| 10 | 2 | waypoint_latitude | BAM32 | 4 B | BAM32 | rad | O |
| 14 | 3 | waypoint_longitude | BAM32 | 4 B | BAM32 | rad | O |
| 18 | 4 | location_type | uint8 | 1 B | uint8 | enum | O |
| 19 | 5 | waypoint_altitude | int24 | 1 B | int24 | m | O |
| 20 | 6 | altitude_type | uint8 | 1 B | uint8 | enum | O |
| 21 | 7 | altitude_change | uint8 | 1 B | uint8 | enum | O |
| 22 | 8 | waypoint_speed | uint16 | 2 B | uint16 | m/s | O |
| 24 | 9 | speed_type | uint8 | 1 B | uint8 | enum | O |
| 25 | 10 | next_waypoint | uint16 | 2 B | uint16 | - | O |
| 27 | 11 | turn_type | uint8 | 1 B | uint8 | enum | O |
| 28 | 12 | optional_messages | uint8 | 1 B | uint8 | Bitmapped | O |
| 29 | 13 | waypoint_type | uint8 | 1 B | uint8 | enum | O |
| 30 | 14 | limit_type | uint8 | 1 B | uint8 | enum | O |
| 31 | 15 | loop_limit | uint16 | 2 B | uint16 | - | O |
| 33 | 16 | activity_id | uint24 | 1 B | uint24 | - | O |

### Message #16002: Heartbeat
**Group:** DataLinkStatus | **Source:** VSM / UA / CUCS | **Direction:** Bi-directional | **Latency:** 1000ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint8 | 1 B | Bitmapped | - | M |
| 1 | 0 | time_stamp | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |

### Message #17000: MessageAcknowledgement
**Group:** Miscellaneous | **Source:** UA / VSM / CUCS | **Direction:** Bi-directional | **Latency:** 500ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint8 | 1 B | Bitmapped | - | M |
| 1 | 0 | time_stamp | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 6 | 1 | original_time_stamp | Timestamp | 5 B | uint40 (Scaled 1ms) | ms | O |
| 11 | 2 | original_message_type | uint16 | 2 B | uint16 | - | O |
| 13 | 3 | acknowledgement_type | uint8 | 1 B | uint8 | enum | O |

## 3. Capability Profile Mapping

### Profile: LOI2_Monitor_Profile (LOI 2)
**Mode:** monitor_only
**Included Groups:** SystemID, FlightVehicleStatus, SubsystemStatus
**Optional Groups:** DataLinkStatus, FlightVehiclePayloadRelevantStatus
**Supported Messages:**
- #1 CUCSAuthorisationRequest (Full Support)
- #2 VSMAuthorisationResponse (Full Support)
- #3 VehicleID (Full Support)
- #4 PositiveHandoverAuthorisationRequest (Full Support)
- #5 PositiveHandoverAuthorisationGranted (Full Support)
- #4000 InertialStates (Optional / profile-dependent)
- #4001 FromToNextWaypointStates (Optional / profile-dependent)
- #16002 Heartbeat (Optional / profile-dependent)

### Profile: LOI4_UA_Control_Profile (LOI 4)
**Mode:** control_and_monitor
**Included Groups:** SystemID, FlightVehicleStatus, FlightVehiclePayloadRelevantStatus, FlightVehicleCommand, SubsystemStatus
**Supported Messages:**
- #1 CUCSAuthorisationRequest (Full Support)
- #2 VSMAuthorisationResponse (Full Support)
- #3 VehicleID (Full Support)
- #4 PositiveHandoverAuthorisationRequest (Full Support)
- #5 PositiveHandoverAuthorisationGranted (Full Support)
- #4000 InertialStates (Full Support)
- #4001 FromToNextWaypointStates (Full Support)


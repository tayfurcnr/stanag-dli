# DLI Interface Control Sheet (ICS) - v1.0 (Draft Aligned to STANAG 4586)

> [!IMPORTANT]
> This document is a framework-generated ICS draft aligned to STANAG 4586. Presence vector sizes, field widths, and encodings are derived from the SDLI definitions.

## 1. Message Catalog

| ID | Name | Group | Fields | Source | Direction | Latency | Payload Length (Max) |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | CUCSAuthorisationRequest | SystemID | 18 | CUCS | CUCS -> UA/VSM | 1000ms | 38 B |
| 2 | VSMAuthorisationResponse | SystemID | 19 | VSM | VSM -> CUCS | 1000ms | 39 B |
| 3 | VehicleID | SystemID | 10 | VSM / UA | VSM/UA -> CUCS | 1000ms | 90 B |
| 4 | PositiveHandoverAuthorisationRequest | SystemID | 16 | CUCS | CUCS -> UA/VSM | 1000ms | 41 B |
| 5 | PositiveHandoverAuthorisationGranted | SystemID | 16 | VSM / UA | VSM/UA -> CUCS | 1000ms | 42 B |
| 2000 | VehicleConfigurationCommand | VehicleControl | 3 | CUCS | CUCS -> UA/VSM | 1000ms | 9 B |
| 2007 | UnmannedAircraftLights | VehicleControl | 3 | CUCS | CUCS -> UA/VSM | 1000ms | 11 B |
| 2008 | EngineCommand | PropulsionControl | 8 | CUCS | CUCS -> UA/VSM | 100ms | 15 B |
| 2010 | UAStickCommand | VehicleControl | 13 | CUCS | CUCS -> UA/VSM | 50ms | 19 B |
| 2016 | VehicleOperatingModeCommand | VehicleControl | 23 | CUCS | CUCS -> UA/VSM | 100ms | 50 B |
| 2017 | LoiterConfiguration | VehicleControl | 11 | CUCS | CUCS -> UA/VSM | 100ms | 23 B |
| 3001 | VehicleOperatingModeReport | VehicleStatus | 2 | VSM / UA | VSM/UA -> CUCS | 100ms | 7 B |
| 3002 | VehicleOperatingStates | FlightVehicleStatus | 24 | VSM | VSM -> CUCS | 500ms | 50 B |
| 3004 | LoiterConfigurationReport | VehicleStatus | 14 | VSM / UA | VSM/UA -> CUCS | 100ms | 27 B |
| 3006 | VehicleLightsState | VehicleStatus | 2 | VSM / UA | VSM/UA -> CUCS | 1000ms | 8 B |
| 3007 | EngineOperatingStates | FlightVehicleStatus | 37 | VSM | VSM -> CUCS | 500ms | 59 B |
| 3011 | UAStickStatus | VehicleStatus | 13 | VSM / UA | VSM/UA -> CUCS | 50ms | 19 B |
| 4000 | InertialStates | FlightVehiclePayloadRelevantStatus | 18 | UA / VSM | UA/VSM -> CUCS | 500ms | 46 B |
| 4001 | FromToNextWaypointStates | FlightVehiclePayloadRelevantStatus | 21 | UA / VSM | UA/VSM -> CUCS | 500ms | 69 B |
| 13002 | UAPositionWaypoint | Mission | 18 | CUCS / VSM | Bi-directional | 1000ms | 43 B |
| 16002 | Heartbeat | DataLinkStatus | 1 | VSM / UA / CUCS | Bi-directional | 1000ms | 6 B |
| 17000 | MessageAcknowledgement | Miscellaneous | 4 | UA / VSM / CUCS | Bi-directional | 500ms | 14 B |

## 2. Detailed Bit Layouts

### Message #1: CUCSAuthorisationRequest
**Group:** SystemID | **Source:** CUCS | **Direction:** CUCS -> UA/VSM | **Latency:** 1000ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint24 | 3 B | Bitmapped | - | M |
| 3 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 8 | 1 | VSM ID | uint32 | 4 B | uint32 | - | O |
| 12 | 2 | Data Link ID | uint32 | 4 B | uint32 | - | O |
| 16 | 3 | Vehicle Type | uint16 | 2 B | uint16 | enum | O |
| 18 | 4 | Vehicle Subtype | uint16 | 2 B | uint16 | - | O |
| 20 | 5 | Requested/Handover LOI | uint8 | 1 B | uint8 | Bitmapped | O |
| 21 | 6 | Requested/Handover Access | uint8 | 1 B | uint8 | enum | O |
| 22 | 7 | Requested Flight Mode | uint8 | 1 B | uint8 | enum | O |
| 23 | 8 | Controlled Station 1-16 | uint16 | 2 B | uint16 | Bitmapped | O |
| 25 | 9 | Component Number | uint16 | 2 B | uint16 | Bitmapped | O |
| 27 | 10 | Sub-Component Number | uint16 | 2 B | uint16 | Bitmapped | O |
| 29 | 11 | Payload Type | uint8 | 1 B | uint8 | enum | O |
| 30 | 12 | Asset Mode | uint8 | 1 B | uint8 | enum | O |
| 31 | 13 | Wait for Vehicle Data Link Transition Coordination Message | uint8 | 1 B | uint8 | enum | O |
| 32 | 14 | CUCS Type | uint8 | 1 B | uint8 | enum | O |
| 33 | 15 | CUCS Subtype | uint16 | 2 B | uint16 | - | O |
| 35 | 16 | Presence Vector Support | uint8 | 1 B | uint8 | enum | O |
| 36 | 17 | Controlled Station 17-32 | uint16 | 2 B | uint16 | Bitmapped | O |

### Message #2: VSMAuthorisationResponse
**Group:** SystemID | **Source:** VSM | **Direction:** VSM -> CUCS | **Latency:** 1000ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint24 | 3 B | Bitmapped | - | M |
| 3 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 8 | 1 | VSM ID | uint32 | 4 B | uint32 | - | O |
| 12 | 2 | Data Link ID | uint32 | 4 B | uint32 | - | O |
| 16 | 3 | Access Authorized | uint8 | 1 B | uint8 | enum | O |
| 17 | 4 | Access Granted | uint8 | 1 B | uint8 | enum | O |
| 18 | 5 | LOI Authorized | uint8 | 1 B | uint8 | Bitmapped | O |
| 19 | 6 | LOI Granted | uint8 | 1 B | uint8 | Bitmapped | O |
| 20 | 7 | Flight Modes Granted | uint8 | 1 B | uint8 | enum | O |
| 21 | 8 | Controlled Station 1-16 | uint16 | 2 B | uint16 | Bitmapped | O |
| 23 | 9 | Component Number | uint16 | 2 B | uint16 | Bitmapped | O |
| 25 | 10 | Sub-Component Number | uint16 | 2 B | uint16 | Bitmapped | O |
| 27 | 11 | Payload Type | uint8 | 1 B | uint8 | enum | O |
| 28 | 12 | Access Requested | uint8 | 1 B | uint8 | Bitmapped | O |
| 29 | 13 | Vehicle Type | uint16 | 2 B | uint16 | enum | O |
| 31 | 14 | Vehicle Subtype | uint16 | 2 B | uint16 | - | O |
| 33 | 15 | CUCS Type | uint8 | 1 B | uint8 | enum | O |
| 34 | 16 | CUCS Subtype | uint16 | 2 B | uint16 | - | O |
| 36 | 17 | Presence Vector Support | uint8 | 1 B | uint8 | enum | O |
| 37 | 18 | Controlled Station 17-32 | uint16 | 2 B | uint16 | Bitmapped | O |

### Message #3: VehicleID
**Group:** SystemID | **Source:** VSM / UA | **Direction:** VSM/UA -> CUCS | **Latency:** 1000ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint16 | 2 B | Bitmapped | - | M |
| 2 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 7 | 1 | VSM ID | uint32 | 4 B | uint32 | - | O |
| 11 | 2 | Vehicle ID Update | uint32 | 4 B | uint32 | - | O |
| 15 | 3 | Vehicle Type | uint16 | 2 B | uint16 | enum | O |
| 17 | 4 | Vehicle Subtype | uint16 | 2 B | uint16 | - | O |
| 19 | 5 | Owning ID | uint8 | 1 B | uint8 | enum | O |
| 20 | 6 | Tail Number | Char16 | 16 B | buffer[16] | - | O |
| 36 | 7 | Mission ID | Char20 | 20 B | buffer[20] | - | O |
| 56 | 8 | ATC Call Sign | Char32 | 32 B | buffer[32] | - | O |
| 88 | 9 | Configuration Checksum | uint16 | 2 B | uint16 | - | O |

### Message #4: PositiveHandoverAuthorisationRequest
**Group:** SystemID | **Source:** CUCS | **Direction:** CUCS -> UA/VSM | **Latency:** 1000ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint16 | 2 B | Bitmapped | - | M |
| 2 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 7 | 1 | VSM ID | uint32 | 4 B | uint32 | - | O |
| 11 | 2 | Data Link ID | uint32 | 4 B | uint32 | - | O |
| 15 | 3 | Vehicle Type | uint16 | 2 B | uint16 | enum | O |
| 17 | 4 | Vehicle Subtype | uint16 | 2 B | uint16 | - | O |
| 19 | 5 | Requested/Handover LOI | uint8 | 1 B | uint8 | Bitmapped | O |
| 20 | 6 | Flight Mode Offset | uint8 | 1 B | uint8 | - | O |
| 21 | 7 | Requested Flight Mode | uint32 | 4 B | uint32 | Bitmapped | O |
| 25 | 8 | Controlled Station 1-16 | uint16 | 2 B | uint16 | Bitmapped | O |
| 27 | 9 | Component Number | uint16 | 2 B | uint16 | Bitmapped | O |
| 29 | 10 | Sub-Component Number | uint16 | 2 B | uint16 | Bitmapped | O |
| 31 | 11 | Requesting CUCS Type | uint8 | 1 B | uint8 | enum | O |
| 32 | 12 | Requesting CUCS Subtype | uint16 | 2 B | uint16 | - | O |
| 34 | 13 | Requesting CUCS ID | uint32 | 4 B | uint32 | - | O |
| 38 | 14 | Presence Vector Support | uint8 | 1 B | uint8 | enum | O |
| 39 | 15 | Controlled Station 17-32 | uint16 | 2 B | uint16 | Bitmapped | O |

### Message #5: PositiveHandoverAuthorisationGranted
**Group:** SystemID | **Source:** VSM / UA | **Direction:** VSM/UA -> CUCS | **Latency:** 1000ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint24 | 3 B | Bitmapped | - | M |
| 3 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 8 | 1 | VSM ID | uint32 | 4 B | uint32 | - | O |
| 12 | 2 | Data Link ID | uint32 | 4 B | uint32 | - | O |
| 16 | 3 | LOI Authorized | uint8 | 1 B | uint8 | Bitmapped | O |
| 17 | 4 | Flight Mode Offset | uint8 | 1 B | uint8 | - | O |
| 18 | 5 | Flight Modes Authorized | uint32 | 4 B | uint32 | Bitmapped | O |
| 22 | 6 | Controlled Station 1 16 Authorized | uint16 | 2 B | uint16 | Bitmapped | O |
| 24 | 7 | Component Number Authorized | uint16 | 2 B | uint16 | Bitmapped | O |
| 26 | 8 | Sub-Component Number Authorized | uint16 | 2 B | uint16 | Bitmapped | O |
| 28 | 9 | Vehicle Type | uint16 | 2 B | uint16 | enum | O |
| 30 | 10 | Vehicle Subtype | uint16 | 2 B | uint16 | - | O |
| 32 | 11 | Requesting CUCS Type | uint8 | 1 B | uint8 | enum | O |
| 33 | 12 | Requesting CUCS Subtype | uint16 | 2 B | uint16 | - | O |
| 35 | 13 | Requesting CUCS ID | uint32 | 4 B | uint32 | - | O |
| 39 | 14 | Presence Vector Support | uint8 | 1 B | uint8 | enum | O |
| 40 | 15 | Controlled Station 17-32 Authorized | uint16 | 2 B | uint16 | Bitmapped | O |

### Message #2000: VehicleConfigurationCommand
**Group:** VehicleControl | **Source:** CUCS | **Direction:** CUCS -> UA/VSM | **Latency:** 1000ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint8 | 1 B | Bitmapped | - | M |
| 1 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 6 | 1 | Energy Storage Unit | uint8 | 1 B | uint8 | - | O |
| 7 | 2 | Initial Propulsion Energy | uint16 | 2 B | uint16 (Field scale=0.002) | % | O |

### Message #2007: UnmannedAircraftLights
**Group:** VehicleControl | **Source:** CUCS | **Direction:** CUCS -> UA/VSM | **Latency:** 1000ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint8 | 1 B | Bitmapped | - | M |
| 1 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 6 | 1 | Set Lights | uint16 | 2 B | uint16 | Bitmapped | O |
| 8 | 2 | Activity ID | uint24 | 3 B | uint24 | - | O |

### Message #2008: EngineCommand
**Group:** PropulsionControl | **Source:** CUCS | **Direction:** CUCS -> UA/VSM | **Latency:** 100ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint8 | 1 B | Bitmapped | - | M |
| 1 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 6 | 1 | Engine Number | uint8 | 1 B | uint8 | - | O |
| 7 | 2 | Engine Command | uint8 | 1 B | uint8 | enum | O |
| 8 | 3 | Reverse Thrust Power | uint8 | 1 B | uint8 | enum | O |
| 9 | 4 | Reverse Thrust | uint8 | 1 B | uint8 | enum | O |
| 10 | 5 | Ignition Switch Power | uint8 | 1 B | uint8 | enum | O |
| 11 | 6 | Ignition Switch Activation | uint8 | 1 B | uint8 | enum | O |
| 12 | 7 | Activity ID | uint24 | 3 B | uint24 | - | O |

### Message #2010: UAStickCommand
**Group:** VehicleControl | **Source:** CUCS | **Direction:** CUCS -> UA/VSM | **Latency:** 50ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint16 | 2 B | Bitmapped | - | M |
| 2 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 7 | 1 | Lateral Stick | int8 | 1 B | int8 | - | O |
| 8 | 2 | Longitudinal Stick | int8 | 1 B | int8 | - | O |
| 9 | 3 | Rotational Stick (Rudder) | int8 | 1 B | int8 | - | O |
| 10 | 4 | Throttle Stick - Engine 1 | uint8 | 1 B | uint8 | - | O |
| 11 | 5 | Pitch Stick - Engine 1 | int8 | 1 B | int8 | - | O |
| 12 | 6 | Throttle Stick - Engine 2 | uint8 | 1 B | uint8 | - | O |
| 13 | 7 | Pitch Stick - Engine 2 | int8 | 1 B | int8 | - | O |
| 14 | 8 | Throttle Stick - Engine 3 | uint8 | 1 B | uint8 | - | O |
| 15 | 9 | Pitch Stick - Engine 3 | int8 | 1 B | int8 | - | O |
| 16 | 10 | Throttle Stick - Engine 4 | uint8 | 1 B | uint8 | - | O |
| 17 | 11 | Pitch Stick - Engine 4 | int8 | 1 B | int8 | - | O |
| 18 | 12 | Taxi Stick | int8 | 1 B | int8 | - | O |

### Message #2016: VehicleOperatingModeCommand
**Group:** VehicleControl | **Source:** CUCS | **Direction:** CUCS -> UA/VSM | **Latency:** 100ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint24 | 3 B | Bitmapped | - | M |
| 3 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 8 | 1 | Select Flight Path Control Mode | uint8 | 1 B | uint8 | enum | O |
| 9 | 2 | Altitude Command Type | uint8 | 1 B | uint8 | enum | O |
| 10 | 3 | Commanded Altitude | int24 | 3 B | int24 (Field scale=0.02) | m | O |
| 13 | 4 | Commanded Vertical Speed | int16 | 2 B | int16 (Field scale=0.05) | m/s | O |
| 15 | 5 | Heading Command Type | uint8 | 1 B | uint8 | enum | O |
| 16 | 6 | Heading Reference | uint8 | 1 B | uint8 | enum | O |
| 17 | 7 | Commanded Heading | BAM16 | 2 B | BAM16 (uint16) | rad | O |
| 19 | 8 | Commanded Course | BAM16 | 2 B | BAM16 (uint16) | rad | O |
| 21 | 9 | Commanded Turn Rate | int16 | 2 B | int16 (Field scale=0.005) | rad/s | O |
| 23 | 10 | Commanded Roll Rate | int16 | 2 B | int16 (Field scale=0.005) | rad/s | O |
| 25 | 11 | Commanded Roll | BAM16 | 2 B | BAM16 (uint16) | rad | O |
| 27 | 12 | Commanded Speed | uint16 | 2 B | uint16 (Field scale=0.5) | m/s | O |
| 29 | 13 | Speed Type | uint8 | 1 B | uint8 | enum | O |
| 30 | 14 | Commanded Waypoint Number | uint16 | 2 B | uint16 | - | O |
| 32 | 15 | Altimeter Setting | uint16 | 2 B | uint16 (Field scale=10.0) | Pa | O |
| 34 | 16 | Altitude Type | uint8 | 1 B | uint8 | enum | O |
| 35 | 17 | Loiter Position Latitude | BAM32 | 4 B | BAM32 (uint32) | rad | O |
| 39 | 18 | Loiter Position Longitude | BAM32 | 4 B | BAM32 (uint32) | rad | O |
| 43 | 19 | Loiter Altitude Change Behaviour | uint8 | 1 B | uint8 | enum | O |
| 44 | 20 | Thrust Direction | BAM16 | 2 B | BAM16 (uint16) | rad | O |
| 46 | 21 | Thrust | uint8 | 1 B | uint8 | % | O |
| 47 | 22 | Activity ID | uint24 | 3 B | uint24 | - | O |

### Message #2017: LoiterConfiguration
**Group:** VehicleControl | **Source:** CUCS | **Direction:** CUCS -> UA/VSM | **Latency:** 100ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint16 | 2 B | Bitmapped | - | M |
| 2 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 7 | 1 | Loiter Type | uint8 | 1 B | uint8 | enum | O |
| 8 | 2 | Loiter Radius | uint16 | 2 B | uint16 (Field scale=1.5) | m | O |
| 10 | 3 | Loiter Length | uint16 | 2 B | uint16 (Field scale=1.5) | m | O |
| 12 | 4 | Loiter Length Units | uint8 | 1 B | uint8 | enum | O |
| 13 | 5 | Loiter Bearing | BAM16 | 2 B | BAM16 (uint16) | rad | O |
| 15 | 6 | Loiter Direction | uint8 | 1 B | uint8 | enum | O |
| 16 | 7 | Flying Behaviour | uint8 | 1 B | uint8 | enum | O |
| 17 | 8 | Loiter Duration | uint16 | 2 B | uint16 | - | O |
| 19 | 9 | Loiter Duration Units | uint8 | 1 B | uint8 | enum | O |
| 20 | 10 | Activity ID | uint24 | 3 B | uint24 | - | O |

### Message #3001: VehicleOperatingModeReport
**Group:** VehicleStatus | **Source:** VSM / UA | **Direction:** VSM/UA -> CUCS | **Latency:** 100ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint8 | 1 B | Bitmapped | - | M |
| 1 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 6 | 1 | Select Flight Path Control Mode | uint8 | 1 B | uint8 | enum | O |

### Message #3002: VehicleOperatingStates
**Group:** FlightVehicleStatus | **Source:** VSM | **Direction:** VSM -> CUCS | **Latency:** 500ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint24 | 3 B | Bitmapped | - | M |
| 3 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 8 | 1 | Commanded Altitude | int24 | 3 B | int24 (Field scale=0.02) | m | O |
| 11 | 2 | Altitude Type | uint8 | 1 B | uint8 | enum | O |
| 12 | 3 | Commanded Heading | BAM16 | 2 B | BAM16 (uint16) | rad | O |
| 14 | 4 | Commanded Course | BAM16 | 2 B | BAM16 (uint16) | rad | O |
| 16 | 5 | Commanded Turn Rate | int16 | 2 B | int16 (Field scale=0.005) | rad/s | O |
| 18 | 6 | Commanded Roll Rate | int16 | 2 B | int16 (Field scale=0.005) | rad/s | O |
| 20 | 7 | Commanded Speed | uint16 | 2 B | uint16 (Field scale=0.5) | m/s | O |
| 22 | 8 | Speed Type | uint8 | 1 B | uint8 | enum | O |
| 23 | 9 | Power Level | int8 | 1 B | int8 | % | O |
| 24 | 10 | Bingo Energy | uint16 | 2 B | uint16 (Field scale=0.0016) | % | O |
| 26 | 11 | Current Propulsion Energy Level | uint16 | 2 B | uint16 (Field scale=0.0016) | % | O |
| 28 | 12 | Current Propulsion Energy Usage Rate | uint16 | 2 B | uint16 (Field scale=0.0002) | %/s | O |
| 30 | 13 | Commanded Roll | BAM16 | 2 B | BAM16 (uint16) | rad | O |
| 32 | 14 | Altitude Command Type | uint8 | 1 B | uint8 | enum | O |
| 33 | 15 | Heading Command Type | uint8 | 1 B | uint8 | enum | O |
| 34 | 16 | UA State | uint8 | 1 B | uint8 | enum | O |
| 35 | 17 | Thrust Direction | BAM16 | 2 B | BAM16 (uint16) | rad | O |
| 37 | 18 | Thrust | uint8 | 1 B | uint8 | % | O |
| 38 | 19 | Loiter & Waypoint Validity | uint8 | 1 B | uint8 | bitmapped | O |
| 39 | 20 | Commanded Loiter Position Latitude | BAM32 | 4 B | BAM32 (uint32) | rad | O |
| 43 | 21 | Commanded Loiter Position Longitude | BAM32 | 4 B | BAM32 (uint32) | rad | O |
| 47 | 22 | Altitude Change Behaviour | uint8 | 1 B | uint8 | enum | O |
| 48 | 23 | Commanded Waypoint Number | uint16 | 2 B | uint16 | - | O |

### Message #3004: LoiterConfigurationReport
**Group:** VehicleStatus | **Source:** VSM / UA | **Direction:** VSM/UA -> CUCS | **Latency:** 100ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint16 | 2 B | Bitmapped | - | M |
| 2 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 7 | 1 | Loiter Type | uint8 | 1 B | uint8 | enum | O |
| 8 | 2 | Loiter Radius | uint16 | 2 B | uint16 (Field scale=1.5) | m | O |
| 10 | 3 | Loiter Length | uint16 | 2 B | uint16 (Field scale=1.5) | m | O |
| 12 | 4 | Loiter Length Units | uint8 | 1 B | uint8 | enum | O |
| 13 | 5 | Loiter Bearing | BAM16 | 2 B | BAM16 (uint16) | rad | O |
| 15 | 6 | Loiter Direction | uint8 | 1 B | uint8 | enum | O |
| 16 | 7 | Loiter Altitude | int24 | 3 B | int24 (Field scale=0.02) | m | O |
| 19 | 8 | Altitude Type | uint8 | 1 B | uint8 | enum | O |
| 20 | 9 | Loiter Speed | uint16 | 2 B | uint16 (Field scale=0.5) | m/s | O |
| 22 | 10 | Speed Type | uint8 | 1 B | uint8 | enum | O |
| 23 | 11 | Flying Behaviour | uint8 | 1 B | uint8 | enum | O |
| 24 | 12 | Loiter Duration | uint16 | 2 B | uint16 | - | O |
| 26 | 13 | Loiter Duration Units | uint8 | 1 B | uint8 | enum | O |

### Message #3006: VehicleLightsState
**Group:** VehicleStatus | **Source:** VSM / UA | **Direction:** VSM/UA -> CUCS | **Latency:** 1000ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint8 | 1 B | Bitmapped | - | M |
| 1 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 6 | 1 | Navigation Lights State | uint16 | 2 B | uint16 | Bitmapped | O |

### Message #3007: EngineOperatingStates
**Group:** FlightVehicleStatus | **Source:** VSM | **Direction:** VSM -> CUCS | **Latency:** 500ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint40 | 5 B | Bitmapped | - | M |
| 5 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 10 | 1 | Engine Number | uint16 | 2 B | uint16 | - | O |
| 12 | 2 | Engine Status | uint8 | 1 B | uint8 | enum | O |
| 13 | 3 | Reported Engine Command | uint8 | 1 B | uint8 | enum | O |
| 14 | 4 | Reverse Thrust Power Status | uint8 | 1 B | uint8 | enum | O |
| 15 | 5 | Reported Reverse Thrust | uint8 | 1 B | uint8 | enum | O |
| 16 | 6 | Ignition Switch Power Status | uint8 | 1 B | uint8 | enum | O |
| 17 | 7 | Ignition Switch Activation | uint8 | 1 B | uint8 | enum | O |
| 18 | 8 | Engine Power Setting | uint16 | 2 B | uint16 (Field scale=0.0017) | % | O |
| 20 | 9 | Engine Speed 1 Type | uint8 | 1 B | uint8 | enum | O |
| 21 | 10 | Engine Speed 1 | uint16 | 2 B | uint16 (Field scale=0.5) | rad/s | O |
| 23 | 11 | Engine Speed 2 Type | uint8 | 1 B | uint8 | enum | O |
| 24 | 12 | Engine Speed 2 | uint16 | 2 B | uint16 (Field scale=0.5) | rad/s | O |
| 26 | 13 | Engine Speed 3 Type | uint8 | 1 B | uint8 | enum | O |
| 27 | 14 | Engine Speed 3 | uint16 | 2 B | uint16 (Field scale=0.5) | rad/s | O |
| 29 | 15 | Propeller Pitch Angle | int8 | 1 B | int8 (Field scale=0.02) | rad | O |
| 30 | 16 | Output Power (Shaft Torque) Status | uint8 | 1 B | uint8 | enum | O |
| 31 | 17 | Engine Temperature 1 Type | uint8 | 1 B | uint8 | enum | O |
| 32 | 18 | Engine Temperature 1 | uint16 | 2 B | uint16 (Field scale=0.5) | K | O |
| 34 | 19 | Engine Temperature 2 Type | uint8 | 1 B | uint8 | enum | O |
| 35 | 20 | Engine Temperature 2 | uint16 | 2 B | uint16 (Field scale=0.5) | K | O |
| 37 | 21 | Engine Temperature 3 Type | uint8 | 1 B | uint8 | enum | O |
| 38 | 22 | Engine Temperature 3 | uint16 | 2 B | uint16 (Field scale=0.5) | K | O |
| 40 | 23 | Engine Temperature 4 Type | uint8 | 1 B | uint8 | enum | O |
| 41 | 24 | Engine Temperature 4 | uint16 | 2 B | uint16 (Field scale=0.5) | K | O |
| 43 | 25 | Engine Pressure 1 Type | uint8 | 1 B | uint8 | enum | O |
| 44 | 26 | Engine Pressure 1 | uint16 | 2 B | uint16 (Field scale=10.0) | Pa | O |
| 46 | 27 | Engine Pressure 1 Status | uint8 | 1 B | uint8 | enum | O |
| 47 | 28 | Engine Pressure 2 Type | uint8 | 1 B | uint8 | enum | O |
| 48 | 29 | Engine Pressure 2 | uint16 | 2 B | uint16 (Field scale=10.0) | Pa | O |
| 50 | 30 | Engine Pressure 2 Status | uint8 | 1 B | uint8 | enum | O |
| 51 | 31 | Fire Detection Sensor Status | uint8 | 1 B | uint8 | enum | O |
| 52 | 32 | Engine Energy Flow | uint24 | 3 B | uint24 (Field scale=0.0017) | %/s | O |
| 55 | 33 | Engine Body Temperature Status | uint8 | 1 B | uint8 | enum | O |
| 56 | 34 | Exhaust Gas Temperature Status | uint8 | 1 B | uint8 | enum | O |
| 57 | 35 | Coolant Temperature Status | uint8 | 1 B | uint8 | enum | O |
| 58 | 36 | Lubricant Temperature Status | uint8 | 1 B | uint8 | enum | O |

### Message #3011: UAStickStatus
**Group:** VehicleStatus | **Source:** VSM / UA | **Direction:** VSM/UA -> CUCS | **Latency:** 50ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint16 | 2 B | Bitmapped | - | M |
| 2 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 7 | 1 | Lateral Stick | int8 | 1 B | int8 | - | O |
| 8 | 2 | Longitudinal Stick | int8 | 1 B | int8 | - | O |
| 9 | 3 | Rotational Stick (Rudder) | int8 | 1 B | int8 | - | O |
| 10 | 4 | Throttle Stick - Engine 1 | uint8 | 1 B | uint8 | - | O |
| 11 | 5 | Pitch Stick - Engine 1 | int8 | 1 B | int8 | - | O |
| 12 | 6 | Throttle Stick - Engine 2 | uint8 | 1 B | uint8 | - | O |
| 13 | 7 | Pitch Stick - Engine 2 | int8 | 1 B | int8 | - | O |
| 14 | 8 | Throttle Stick - Engine 3 | uint8 | 1 B | uint8 | - | O |
| 15 | 9 | Pitch Stick - Engine 3 | int8 | 1 B | int8 | - | O |
| 16 | 10 | Throttle Stick - Engine 4 | uint8 | 1 B | uint8 | - | O |
| 17 | 11 | Pitch Stick - Engine 4 | int8 | 1 B | int8 | - | O |
| 18 | 12 | Taxi Stick | int8 | 1 B | int8 | - | O |

### Message #4000: InertialStates
**Group:** FlightVehiclePayloadRelevantStatus | **Source:** UA / VSM | **Direction:** UA/VSM -> CUCS | **Latency:** 500ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint24 | 3 B | Bitmapped | - | M |
| 3 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 8 | 1 | Latitude | BAM32 | 4 B | BAM32 (uint32) | rad | O |
| 12 | 2 | Longitude | BAM32 | 4 B | BAM32 (uint32) | rad | O |
| 16 | 3 | Altitude | int24 | 3 B | int24 (Field scale=0.02) | m | O |
| 19 | 4 | Altitude Type | uint8 | 1 B | uint8 | enum | O |
| 20 | 5 | U_Speed | int16 | 2 B | int16 (Field scale=0.05) | m/s | O |
| 22 | 6 | V_Speed | int16 | 2 B | int16 (Field scale=0.05) | m/s | O |
| 24 | 7 | W_Speed | int16 | 2 B | int16 (Field scale=0.05) | m/s | O |
| 26 | 8 | U_Accel | int16 | 2 B | int16 (Field scale=0.005) | m/s^2 | O |
| 28 | 9 | V_Accel | int16 | 2 B | int16 (Field scale=0.005) | m/s^2 | O |
| 30 | 10 | W_Accel | int16 | 2 B | int16 (Field scale=0.005) | m/s^2 | O |
| 32 | 11 | Roll | BAM16 | 2 B | BAM16 (uint16) | rad | O |
| 34 | 12 | Pitch | BAM16 | 2 B | BAM16 (uint16) | rad | O |
| 36 | 13 | Heading | BAM16 | 2 B | BAM16 (uint16) | rad | O |
| 38 | 14 | Roll Rate | int16 | 2 B | int16 (Field scale=0.005) | rad/s | O |
| 40 | 15 | Pitch Rate | int16 | 2 B | int16 (Field scale=0.005) | rad/s | O |
| 42 | 16 | Turn Rate | int16 | 2 B | int16 (Field scale=0.005) | rad/s | O |
| 44 | 17 | Magnetic Variation | BAM16 | 2 B | BAM16 (uint16) | rad | O |

### Message #4001: FromToNextWaypointStates
**Group:** FlightVehiclePayloadRelevantStatus | **Source:** UA / VSM | **Direction:** UA/VSM -> CUCS | **Latency:** 500ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint24 | 3 B | Bitmapped | - | M |
| 3 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 8 | 1 | Altitude Type | uint8 | 1 B | uint8 | enum | O |
| 9 | 2 | Speed Type | uint8 | 1 B | uint8 | enum | O |
| 10 | 3 | From Waypoint – Latitude | BAM32 | 4 B | BAM32 (uint32) | rad | O |
| 14 | 4 | From Waypoint – Longitude | BAM32 | 4 B | BAM32 (uint32) | rad | O |
| 18 | 5 | From Waypoint Altitude | int24 | 3 B | int24 (Field scale=0.02) | m | O |
| 21 | 6 | From Waypoint Time | Timestamp | 5 B | uint40 | ms | O |
| 26 | 7 | From Waypoint Number | uint16 | 2 B | uint16 | - | O |
| 28 | 8 | To Waypoint – Latitude | BAM32 | 4 B | BAM32 (uint32) | rad | O |
| 32 | 9 | To Waypoint – Longitude | BAM32 | 4 B | BAM32 (uint32) | rad | O |
| 36 | 10 | To Waypoint Altitude | int24 | 3 B | int24 (Field scale=0.02) | m | O |
| 39 | 11 | To Waypoint Speed | uint16 | 2 B | uint16 (Field scale=0.5) | m/s | O |
| 41 | 12 | To Waypoint Time | Timestamp | 5 B | uint40 | ms | O |
| 46 | 13 | To Waypoint Number | uint16 | 2 B | uint16 | - | O |
| 48 | 14 | Next Waypoint – Latitude | BAM32 | 4 B | BAM32 (uint32) | rad | O |
| 52 | 15 | Next Waypoint – Longitude | BAM32 | 4 B | BAM32 (uint32) | rad | O |
| 56 | 16 | Next Waypoint Altitude | int24 | 3 B | int24 (Field scale=0.02) | m | O |
| 59 | 17 | Next Waypoint Speed | uint16 | 2 B | uint16 (Field scale=0.5) | m/s | O |
| 61 | 18 | Next Waypoint Time | Timestamp | 5 B | uint40 | ms | O |
| 66 | 19 | Next Waypoint Number | uint16 | 2 B | uint16 | - | O |
| 68 | 20 | Loiter Configuration Report Validity for “To Waypoint” | uint8 | 1 B | uint8 | enum | O |

### Message #13002: UAPositionWaypoint
**Group:** Mission | **Source:** CUCS / VSM | **Direction:** Bi-directional | **Latency:** 1000ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint24 | 3 B | Bitmapped | - | M |
| 3 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 8 | 1 | Waypoint Number | uint16 | 2 B | uint16 | - | O |
| 10 | 2 | Waypoint to Latitude or Relative Y | BAM32 | 4 B | BAM32 (uint32) | rad | O |
| 14 | 3 | Waypoint to Longitude or Relative X | BAM32 | 4 B | BAM32 (uint32) | rad | O |
| 18 | 4 | Location Type | uint8 | 1 B | uint8 | enum | O |
| 19 | 5 | Waypoint to Altitude | int24 | 3 B | int24 (Field scale=0.02) | m | O |
| 22 | 6 | Waypoint Altitude Type | uint8 | 1 B | uint8 | enum | O |
| 23 | 7 | Altitude Change Behaviour | uint8 | 1 B | uint8 | enum | O |
| 24 | 8 | Waypoint to Speed | uint16 | 2 B | uint16 (Field scale=0.5) | m/s | O |
| 26 | 9 | Waypoint Speed Type | uint8 | 1 B | uint8 | enum | O |
| 27 | 10 | Next Waypoint | uint16 | 2 B | uint16 | - | O |
| 29 | 11 | Turn Type | uint8 | 1 B | uint8 | enum | O |
| 30 | 12 | Optional Messages for Waypoint | uint8 | 1 B | uint8 | Bitmapped | O |
| 31 | 13 | Waypoint Type | uint8 | 1 B | uint8 | enum | O |
| 32 | 14 | Limit Type | uint8 | 1 B | uint8 | enum | O |
| 33 | 15 | Loop Limit | uint16 | 2 B | uint16 | - | O |
| 35 | 16 | Arrival Time | Timestamp | 5 B | uint40 | ms | O |
| 40 | 17 | Activity ID | uint24 | 3 B | uint24 | - | O |

### Message #16002: Heartbeat
**Group:** DataLinkStatus | **Source:** VSM / UA / CUCS | **Direction:** Bi-directional | **Latency:** 1000ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint8 | 1 B | Bitmapped | - | M |
| 1 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |

### Message #17000: MessageAcknowledgement
**Group:** Miscellaneous | **Source:** UA / VSM / CUCS | **Direction:** Bi-directional | **Latency:** 500ms

| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | - | **Presence Vector** | uint8 | 1 B | Bitmapped | - | M |
| 1 | 0 | Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 6 | 1 | Original Message Time Stamp | Timestamp | 5 B | uint40 | ms | O |
| 11 | 2 | Original Message Type | uint16 | 2 B | uint16 | - | O |
| 13 | 3 | Acknowledgement Type | uint8 | 1 B | uint8 | enum | O |

## 3. Capability Profile Mapping

### Profile: Custom_Tactical_Profile (LOI 3)
**Mode:** -
**Included Groups:** SystemID, FlightVehiclePayloadRelevantStatus
**Supported Messages:**
- #1 CUCSAuthorisationRequest (Full Support)
- #2 VSMAuthorisationResponse (Full Support)
- #3 VehicleID (Full Support)
- #4 PositiveHandoverAuthorisationRequest (Full Support)
- #5 PositiveHandoverAuthorisationGranted (Full Support)
- #4000 InertialStates (Full Support)
- #4001 FromToNextWaypointStates (Full Support)

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
- #3002 VehicleOperatingStates (Full Support)
- #3007 EngineOperatingStates (Full Support)
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
- #3002 VehicleOperatingStates (Full Support)
- #3007 EngineOperatingStates (Full Support)
- #4000 InertialStates (Full Support)
- #4001 FromToNextWaypointStates (Full Support)


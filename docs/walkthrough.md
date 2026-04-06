# DLI Framework v1.0 - STANAG 4586 Compliance & Refinement Walkthrough

This document summarizes the technical verification of the DLI framework, aligned to STANAG 4586 / AEP-84 Volume II.

### 1. Bit-Accurate Message Representation (Wire-Level Fidelity)
Message schemas have been updated following AEP-84 Volume II tables (`Table 4-34` and `Table 4-73`):
- **Message #1 (CUCS Authorisation Request):** 18 data fields + PV; fully compliant with AEP-84 field definitions.
- **Message #4000 (Inertial States):** 18 data fields + PV; fully compliant with AEP-84 field definitions.
- **Presence Vector:** Contiguous bit allocation verified with LSb = 0 ordering across all messages.

### 2. Technical Metadata (Audit-Friendly)
DLI documentation and source code now incorporate critical protocol constants:
- **Latency Control:** 1000ms for Message #1, 500ms for Message #4000 (aligned with AEP-84 Summary Tables).
- **Source/Direction:** Message flow directions (CUCS -> VSM or UA -> CUCS) are strictly defined.
- **Payload Length:** Net message body lengths (excluding header) are pre-calculated for each message.

### 3. High-Fidelity ICS Report
The `docs/ICS_Report.md` document serves as a standard-compliant technical reference:
- **Offset & Encoding:** Byte offsets and specific encoding types (`BAM32`, `uint40`, etc.) for every field.
- **Profile Mapping:** Detailed "Full Support" vs. "Optional" status for LOI 2 and LOI 4 profiles.
- **DLI Nomenclature:** Standard-compliant terminology (e.g., `Payload Length` instead of `Wire Length`).

### 4. Runtime Verification
Smoke tests using the generated SDK assets under `idl/cpp/dli/generated/` and `idl/python/dli/generated/` validate the runtime surface:
- **Sequential PV Processing:** Bit-level I/O over 3-byte Presence Vectors.
- **Endianness Safety:** All data is guaranteed Big-Endian in wire format.
- **Capability-Aware Dispatcher:** Correct message routing based on active role handlers.

### 5. DLI Protocol Layer (Wrapper & Header)
The framework covers the entire "Wire Message" (Fixed Wrapper + Payload + Checksum):
- **Bit-Accurate Header:** 20-byte fixed AEP-84 Volume II wrapper (Reserved, Payload Length, IDs, Type, Properties). Optional checksum (0/2/4B) is handled outside the fixed wrapper based on Message Properties.
- **Protocol Wrapper:** `DliMessage<T>` template manages the integration of Header, Body, and Checksum.
- **Header-Aware Dispatcher:** Parses the header first to route to the correct payload parser based on `message_type`.

## Phase 14: Wireshark DLI Dissector Success
The STANAG 4586 DLI SDK now includes a fully automated Wireshark Lua Dissector. This tool translates raw binary packets into human-readable engineering values.

### Key Achievements:
- **Bit-Level Accurate**: Fully supports the 20-byte DLI Header and all 19+ defined messages.
- **Engineering Unit Decoding**: Automatically converts BAM32 (Radians) and Scaled (Altitude/Speed) values for real-time human verification.
- **Presence Vector Aware**: Correctly identifies and skips optional fields based on the message PV.

### Visual Verification:
The dissector artifact is generated at `idl/lua/dli.lua` and can be loaded into Wireshark for live packet inspection.
> [!TIP]
> Use `wireshark -X lua_script:idl/lua/dli.lua` to start analyzing STANAG 4586 traffic.

## Conclusion
The DLI SDK provides the following verified capabilities:
1. **Modular C++17 Architecture** (Core, Protocol, Transport, Session).
2. **AEP-84 Compliance** (LoI Profile Filtering & MTU Packing).
3. **Transport Agnosticism** (UDP Multicast & Generic ITransport).
4. **Automated Ecosystem** (C++/Python message generation, C++/Python profile generation, Lua dissector generation, ICS generation).

Current verification focuses on repo-local generation, unit/smoke coverage, and host-only transport checks when explicitly requested.

### Phase 9: Pure Protocol Session Reliability
- **Architecture Context:** Upgraded the framework to a strictly decoupled protocol engine. The `DliSession` logic can run independently of socket ownership and attach to an injected transport surface.
- **Reliability Logic:** Completed the asynchronous callback-based reliable retransmission flow with a stable iterator tick architecture to inherently prevent reentrancy invalidation in synchronous Mock networks.
- **ACK Timestamps:** Overcame the AEP-84 dynamic Presence Vector size variance by plumbing exactly parsed `uint64_t` original_time_stamps straight from the typed `Dispatcher` logic, ensuring 100% accurate correlation.
- **Validation Results:**
  - `Reliable Round-trip (#4000 -> #17000 Type 1)` completes with intact callbacks and TS correlation.
  - `Retransmission with Timestamp Preservation` validates that `send_reliable` never overwrites an intentionally supplied original protocol timestamp.
  - `Invalid Length Handling -> No ACK` successfully ignores corrupted payloads.
  - `ACK Storm Protection` guarantees that injected `#17000` loops are entirely halted at the validation border.

### Phase 10: Data Integrity (Checksums)
- **Architecture Context:** Implemented final layer of STANAG compliance: Data Link Integrity checks via cyclic redundancy.
- **Implementation:** Added `Checksum.hpp` featuring strictly AEP-84 mandated algorithms: CRC-16-CCITT (`0x1021`) and CRC-32 (`0xEDB88320`).
- **Dynamic Logic:** The `DliMessage<T>::serialize` automatically expands the raw packet footprint array by 2 or 4 bytes and calculates/appends the active checksum based purely on the `Message Properties` DLI header setup. The `DliSession::process_incoming` orchestrator dynamically cross-validates this payload checksum before firing the application dispatcher.

```text
=== STANAG 4586 Phase 9: Session Reliability Tests (with CRC-32 enabled) ===
...
  [RESULT] vsm: ACK Received successfully.
...
  [RESULT] vsm: ACK Received after retransmission.
...
  [RESULT] Invalid length correctly ignored.
...
  [RESULT] Storm Protection Proof: No auto-ACK generated for incoming #17000.
=== All Phase 9 Reliability Tests Passed! ===
### Phase 11: UDP Multicast Transport (Tactical Networking)
- **Architecture Context:** Implemented a robust, non-blocking POSIX multicast adapter with a clear distinction between **Protocol Conformance** and **SDK Implementation Policies**.
- **Elite Performance (Packing):** Developed `IPackingPolicy` to enable throughput-optimized batching. Successfully verified packing **10 DLI messages into a single 548-byte MTU datagram** (TX Count: 1).
- **Monitoring & Compliance:** `rx_count` is maintained in accordance with Message #32300 reporting semantics. The `TransportCapabilities` struct allows runtime selection of `ValidationMode` (STRICT/LENIENT) and `timestamp_collision_avoidance`.

```text
=== Phase 11: UDP Multicast Bridge Test Results ===
[DLI Bridge] Multicast Group: 239.1.2.3:30001
[DLI Bridge] MTU: 548 bytes | Packing: ENABLED
[DLI Bridge] Sending Message #1...#10 (Type 4000)
[DLI Bridge] Final Stats - TX Datagrams: 1  <-- Verified (10 messages in 1 datagram)
[DLI Bridge] Bridge shutting down. 🫡 
=== Phase 11 Transport Implementation Passed! ===

## Phase 15: Profile Engine & Multi-Language Scalability
- **Architecture Context:** Established a professional, hierarchical `idl/` root directory.
- **Profiles Implementation:** Automated profile selection via generated `Profiles` surfaces for both C++ and Python. Supports `include_groups`, `include_messages`, and `exclude_messages` for surgical precision in LoI compliance.
- **Hierarchy:** 
  - `idl/cpp/dli/generated/messages/`
  - `idl/cpp/dli/generated/profiles/`
  - `idl/python/dli/generated/profiles/`
  - `idl/lua/`
- **Verification:** `profile_test` and `multicast_bridge` are verified with the new hierarchical include paths.
  - Successfully validated `Custom_Tactical_Profile` with manual overrides (Heartbeat allowed, VehicleID excluded).

---
**Final Status:** The DLI Framework is a multi-language SDK workspace with shared SDLI definitions, generated artifacts, runtime layers, and verification tooling for C++ and Python.

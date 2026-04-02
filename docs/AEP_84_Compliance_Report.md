# STANAG 4586 AEP-84 Volume II Compliance Report

**Status:** Wire-Format Compliant (v1.6 Core DLI Framework)
**Date:** April 2026
**Scope:** Message Encoding, Protocol Integrity, Transport Behavior, and Implementation Strategy

This document distinguishes between **Protocol-Mandated Conformance** (AEP-84 clauses) and **Developer Implementation Policies** adopted to ensure a production-ready SDK.

---

## 1. Protocol-Mandated Conformance (Standard)

The SDK strictly adheres to the following normative AEP-84 Volume II requirements:

### 1.1. Message Wrapper & Header Architecture
- **Wrapper Structure**: The application-layer message wrapper follows the AEP-84 defined structure (Reserved Start -> ... -> Optional Checksum).
- **Reference [DLI 3081]**: All header entries are 16-bit unsigned integers unless otherwise specified.
- **Reference [DLI 3475]**: The "Message Properties" bit-field (Bit 15 for ACK, Bits 14:8 for Version) is mapped with bit-accuracy.

### 1.2. Protocol Integrity & Validation
- **Reference [DLI 3106]**: Receiving units perform range checking (payload length validation) and discard corrupted datagrams in accordance with implementation-defined validation policies.
- **Data Coverage**: Checksum calculations are applied over the complete message, from the first byte of the header to the last byte of the data, consistent with AEP-84 wrapper integrity requirements.
- **Supported Algorithms**: Supported checksum types (e.g., CRC-16-CCITT, CRC-32 ITU-T V.42) are implemented in accordance with standard polynomial definitions.

### 1.3. Networking & Monitoring
- **Architecture**: The DLI engine remains fully transport-independent, consistent with AEP-84 architectural principles. This implementation does not alter or extend any AEP-84 defined message structure.
- **Support for Message #32300**: Supports the "Data Link UDP Count" monitoring structure (rx_count is maintained in accordance with reporting semantics).
- **Support for Message #32301**: Supports the "Universal Multicast Address Announcement" functionality.

---

## 2. Developer Implementation Policy (Decisions)

The following were developer-led choices designed to make the SDK robust in real-world tactical environments. These are **layered on top** of the standard:

### 2.1. Reliability & Orchestration
- **Decision (Session Layer)**: Implemented an asynchronous `DliSession` state-machine to automate the Message #17000 acknowledgement messages retry logic.
- **Decision (ACK Correlation)**: Utilized a custom `(Type, Timestamp, Destination ID)` tuple aligned with DLI message identification semantics for O(1) correlation in multi-node mesh networks.

### 2.2. Network Interoperability
- **Decision (Conservative MTU)**: Adopted a 548-byte payload limit as a policy to minimize IP fragmentation and improve interoperability across heterogeneous IPv4 networks.
- **Decision (Smart Packing)**: Implemented back-to-back message concatenation to maximize throughput without altering individual message semantics or field encoding.

### 2.3. Platform Logic
- **Decision (Collision Avoidance)**: Applied logical "epsilon" increments to timestamps for intra-millisecond messages, preserving real-time ordering and ensuring reliable ACK correlation.
- **Decision (Strict Validation)**: Enforced a "fail-fast" policy for malformed frames to prevent propagation of corruption into safety-critical subsystems.

---

### FINAL VERDICT

The SDK is wire-format compliant with AEP-84 Volume II and maintains strict adherence to all protocol-mandated structures. Additional implementation policies are introduced at the transport and session layers to ensure robustness, interoperability, and operational reliability in real-world deployments. Our developer-led policies provide the necessary "connective tissue" to turn the standard into a stable, operational system.

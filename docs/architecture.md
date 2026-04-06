# DLI SDK Architecture Overview

This document describes the high-level architecture of the STANAG 4586 DLI SDK. The framework is built with a strictly decoupled, layered approach to ensure maximum performance, portability, and AEP-84 compliance.

> [!NOTE]
> The C++ SDK lives under `idl/cpp/dli/`, with headers and implementations organized by layer (`core/`, `protocol/`, `session/`, `transport/`). Generated artifacts live under `idl/cpp/dli/generated/`.

## 1. Layered Architecture

The SDK is organized into four logical layers, from low-level bit manipulation to high-level networking:

### 1.1 Core Layer (`dli/core/`)
The foundation of the SDK. It handles bit-level I/O, endianness, and unit conversions.
- **`BitCursor`**: Orchestrates byte-aligned bit-level reading/writing.
- **`Bam` / `Scaled`**: Handles AEP-84 specific encoding/decoding (Binary Angle Measurement and Scaled types).
- **`Endian`**: Ensures all wire traffic is strictly Big-Endian.

### 1.2 Protocol Layer (`dli/protocol/`)
Defines the AEP-84 Volume II "Wrapper" and filtering logic.
- **`DliHeader`**: Represents the 20-byte fixed wrapper (Source/Dest IDs, Message Type, Properties).
- **`Profile`**: Implements Interoperability Level (LoI) access control. It maintains a whitelist of permitted message IDs.
- **`Dispatcher`**: The central router. It parses headers, validates them against the active `Profile`, and routes payloads to registered application handlers.

### 1.3 Session Layer (`dli/session/`)
Manages stateful communication and reliability (Message #17000 ACKs).
- **`DliSession`**: A dispatcher-driven protocol engine that handles retransmissions, ACK correlation, transport polling, and session-level error reporting (e.g., CRC failures) independently of socket ownership.

### 1.4 Transport Layer (`dli/transport/`)
The physical delivery mechanism.
- **`ITransport`**: An abstract interface for lifecycle and message flow (`start`, `stop`, `send`, `poll`, `flush`).
- **`MulticastTransport`**: A reference POSIX implementation supporting Multicast, Non-blocking I/O, and MTU-aware Packing (batching multiple DLI messages into one UDP datagram).

### 1.5 Generated Assets (`idl/`)
Centralized repository for all code and assets produced by the generator suite.
- **`cpp/`**: Hierarchical C++ SDK sources, tests, examples, and generated headers (`messages/`, `profiles/`).
- **`python/`**: Python runtime, generated messages, generated profiles, and tests.
- **`lua/`**: Wireshark dissector scripts.

---

## 2. Automated Generator Pipeline (`generator/`)

The SDK follows a "Single Source of Truth" philosophy using `.sdli` (YAML-based) definitions.
1. **`dli_gen.py`**: Reads definitions and outputs type-safe C++ message classes in `idl/cpp/dli/generated/messages/`.
2. **`ics_gen.py`**: Generates human-readable compliance reports (`docs/ICS_Report.md`).
3. **`dissector_gen.py`**: Generates a Lua plugin for Wireshark (`idl/lua/dli.lua`).
4. **`profile_gen.py`**: Generates C++ and Python profile classes in `idl/cpp/dli/generated/profiles/` and `idl/python/dli/generated/profiles/`.

---

## 3. Data Flow

1. **Outgoing**: `Application` -> `Generated Class` (Serialize) -> `DliSession` (Reliability/ACK) -> `MulticastTransport` (Packing/Multicast) -> `Wire`.
2. **Incoming**: `Wire` -> `MulticastTransport` -> `DliSession` (De-packing/CRC/ACK) -> `Dispatcher` (Profile Filter) -> `Application Handler`.
3. **Runtime Loop**: `DliSession` owns the orchestration boundary in both C++ and Python: transports are attached to the session, polled through the session, and flushed/stopped through the same surface.

---

## 4. Compliance (AEP-84 Volume II)

- **Wrapper Fidelity**: Strict 20-byte header implementation.
- **Endianness**: Big-Endian wire format guaranteed.
- **Presence Vector**: Sequential LSB-0 bitmasking as per standard tables.
- **Profile Filtering**: Hard-enforced LoI message whitelisting.
- **Runtime Symmetry**: C++ and Python both expose header/message/profile/dispatcher/session building blocks, with generated message and profile assets sourced from the same SDLI definitions.

---
*Architected for high-integrity, real-time UAV/GCS ecosystems.* 🫡

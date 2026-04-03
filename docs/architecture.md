# DLI SDK Architecture Overview

This document describes the high-level architecture of the STANAG 4586 DLI SDK. The framework is built with a strictly decoupled, layered approach to ensure maximum performance, portability, and AEP-84 compliance.

> [!NOTE]
> The SDK uses a traditional C++ structure where **Interfaces (.hpp)** and **Implementations (.cpp)** are separated in `include/` and `src/` respectively, allowing for static library compilation and improved build times.

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
- **`DliSession`**: A pure protocol engine that handles retransmissions, ACK correlation, and session-level error reporting (e.g., CRC failures) independently of any networking stack.

### 1.4 Transport Layer (`dli/transport/`)
The physical delivery mechanism.
- **`ITransport`**: An abstract interface for sending/receiving DLI packets.
- **`UdpTransport`**: A reference POSIX implementation supporting Multicast, Non-blocking I/O, and MTU-aware Packing (batching multiple DLI messages into one UDP datagram).

### 1.5 Generated Assets (`idl/`)
Centralized repository for all code and assets produced by the generator suite.
- **`cpp/`**: Hierarchical C++ headers (`messages/`, `profiles/`). 
- **`lua/`**: Wireshark dissector scripts.

---

## 2. Automated Generator Pipeline (`generator/`)

The SDK follows a "Single Source of Truth" philosophy using `.sdli` (YAML-based) definitions.
1. **`dli_gen.py`**: Reads definitions and outputs type-safe C++ message classes in `idl/cpp/dli/generated/messages/`.
2. **`ics_gen.py`**: Generates human-readable compliance reports (`docs/ICS_Report.md`).
3. **`dissector_gen.py`**: Generates a Lua plugin for Wireshark (`idl/lua/dli.lua`).
4. **`profile_gen.py`**: Generates C++ profile classes in `idl/cpp/dli/generated/profiles/`.

---

## 3. Data Flow

1. **Outgoing**: `Application` -> `Generated Class` (Serialize) -> `DliSession` (Reliability/ACK) -> `UdpTransport` (Packing/Multicast) -> `Wire`.
2. **Incoming**: `Wire` -> `UdpTransport` -> `DliSession` (De-packing/CRC/ACK) -> `Dispatcher` (Profile Filter) -> `Application Handler`.

---

## 4. Compliance (AEP-84 Volume II)

- **Wrapper Fidelity**: Strict 20-byte header implementation.
- **Endianness**: Big-Endian wire format guaranteed.
- **Presence Vector**: Sequential LSB-0 bitmasking as per standard tables.
- **Profile Filtering**: Hard-enforced LoI message whitelisting.

---
*Architected for high-integrity, real-time UAV/GCS ecosystems.* 🫡

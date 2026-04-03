# STANAG 4586 DLI SDK - Professional C++ Protocol Engine

An enterprise-grade, high-performance C++17 SDK for STANAG 4586 DLI (Data Link Interface) compliance. Fully AEP-84 Volume II compliant.

## Features
- **Modular Architecture**: Separate Core, Protocol, and Session layers.
- **AEP-84 Compliance**: Built-in Interoperability Level (LoI) profile filtering.
- **Transport Agnostic**: Decoupled from physical networking via `ITransport` interface.
- **Performance**: Zero-copy packet processing and automatic MTU packing.
- **Ecosystem**: 
  - Automated C++ Header Generation from SDLI definitions.
  - Automated Wireshark Lua Dissector Generation.

## Getting Started

### Prerequisites
- CMake >= 3.10
- C++17 Compiler (GCC/Clang)
- GTest (for unit tests)
- Wireshark (for protocol analysis)

### Build Instructions
```bash
mkdir -p build && cd build
cmake ..
make -j$(nproc)
```

### Running Tests
```bash
cd build
ctest --output-on-failure
```

### Generating Assets
If you modify protocol definitions in `definitions/messages/*.sdli`:
```bash
# Generate C++ headers
python3 generator/dli_gen.py

# Generate Wireshark Dissector
python3 generator/dissector_gen.py

# Generate Interface Control Sheet (ICS) Report
python3 generator/ics_gen.py

# Generate C++ Interoperability Profiles (LoI)
python3 generator/profile_gen.py
```

## Documentation & Auditing
- **Architecture**: Overall system design and layering is in `docs/architecture.md`.
- **ICS Report**: Bit-level detailed breakdown for auditing in `docs/ICS_Report.md`.
- **Walkthrough**: Development history and test logs in `docs/walkthrough.md`.

## Interoperability Profiles (LoI)
The SDK strictly enforces message filtering based on AEP-84 LoI profiles. 
- **Modify Profiles**: Edit the `.profile` files in `definitions/profiles/`. You can use `include_groups`, `include_messages`, and `exclude_messages` for fine-grained control.
- **Apply in C++**:
```cpp
#include <dli/generated/profiles/Profiles.hpp>
// ...
dispatcher.setProfile(dli::generated::Profiles::LOI4_UA_Control());
// Or a custom one:
dispatcher.setProfile(dli::generated::Profiles::Custom_Tactical());
```

## Wireshark Analysis
To analyze STANAG 4586 DLI traffic on the network:
```bash
sudo wireshark -X lua_script:generated/lua/dli.lua
```
Then filter by `dli` and expand the **STANAG 4586 DLI Packet** tree.

## Project Structure
- `include/dli`: Core SDK headers (Core, Protocol, Session, Transport).
- `src/`: Core implementation logic (non-template classes like Dispatcher and DliSession).
- `idl/`: Centralized machine-generated assets (Interface Description Language).
  - `cpp/`: C++ headers (Messages and Profiles).
  - `lua/`: Wireshark dissector.
- `definitions/`: SDLI protocol and Profile definitions (YAML).
- `generator/`: Automated tooling suite.
- `examples/`: Reference implementations.

---
*Maintained for high-integrity defense deployments.* 🫡

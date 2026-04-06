# STANAG 4586 DLI SDK - Professional Multi-Language Framework (v2.0)

An enterprise-grade, high-performance SDK for STANAG 4586 DLI (Data Link Interface) compliance. Fully AEP-84 Volume II compliant with Twin-Architecture symmetry between C++ and Python.

## Features
- **AEP-84 Compliance**: Strict adherence to Volume II message structures and exact field nomenclature.
- **Twin-Architecture**: 1:1 logical and structural symmetry between C++ and Python SDKs.
- **Protocol Logic**: Automatic ACK generation, reliable messaging (retries), and session management.
- **Ecosystem Tooling**: 
  - Automated C++/Python/Lua generation from SDLI definitions.
  - Automated Interface Control Sheet (ICS) generation.
  - Automated Interoperability Level (LoI) profile enforcement.
- **Transport Agnostic**: Decoupled IO layer via `ITransport` interfaces.
- **Symmetric Runtime Surface**: C++ and Python both expose dispatcher-driven sessions, generated profiles, and transport lifecycle methods (`start/stop/poll/flush/send`).

## Project Structure (Clean Root)

```text
STANAG/
├── definitions/        <-- Single Source of Truth (SSOT)
├── generator/          <-- Multi-language IDL Generators
├── idl/
│   ├── cpp/            <-- C++ SDK Root
│   │   ├── dli/        (core, protocol, session, transport, generated)
│   │   ├── tests/      (GTest suite)
│   │   └── examples/   (Reference implementations)
│   ├── python/         <-- Python SDK Root
│   │   ├── dli/        (core, protocol, session, transport, utils, generated)
│   │   └── tests/      (Validation scripts)
│   └── lua/            <-- Wireshark Dissector
├── CMakeLists.txt      <-- Framework Build Orchestrator
└── README.md
```

## Getting Started

### C++ Build
```bash
mkdir -p build && cd build
cmake ..
make -j$(nproc)
```

Minimal consumer example with `find_package(dli)`:
```cmake
find_package(dli REQUIRED CONFIG)
add_executable(app main.cpp)
target_link_libraries(app PRIVATE dli::dli)
```

### Python Setup
For editable local development:
```bash
python3 -m pip install -e .
```

Wheel smoke build:
```bash
python3 -m pip wheel . --no-deps --no-build-isolation -w dist
```

Minimal Python runtime shape:
```python
from dli.protocol import Dispatcher
from dli.session import DliSession
from dli.transport import MulticastTransport

dispatcher = Dispatcher()
session = DliSession(dispatcher)
session.add_transport(MulticastTransport(autostart=False))
session.start_transports()
session.spin_once()
```

### Running Tests
For C++, it is recommended to run `ctest` directly within the `build` directory for accurate result reporting:
```bash
cd build
ctest --output-on-failure
```
> [!NOTE]
> `TransportTest` opens real UDP multicast sockets. It may fail inside restricted sandbox/container environments even when the code is correct, while passing on the host machine.

For Python, run the pytest suite:
```bash
python3 -m pytest -q
```

### Generating Assets
If you modify protocol definitions in `definitions/messages/*.sdli`:
```bash
python3 generator/dli_gen.py        # C++
python3 generator/dli_gen_python.py # Python
python3 generator/dissector_gen.py  # Wireshark
python3 generator/ics_gen.py        # Docs (ICS Report)
python3 generator/profile_gen.py    # C++ Profiles
```

### Unified Verification
Use the standardized verification workflow for sandbox-safe checks:
```bash
python3 tools/full_verify.py
```

To include host-only multicast transport checks:
```bash
python3 tools/full_verify.py --host
```

Equivalent convenience targets are also available:
```bash
make verify
make verify-host
```

## Documentation
- **ICS Report**: `docs/ICS_Report.md` (Audit-friendly bit-level details).
- **Architecture**: `docs/architecture.md`.
- **Walkthrough**: `docs/walkthrough.md` (Development history).

## Wireshark Analysis
```bash
wireshark -X lua_script:idl/lua/dli.lua
```

---
*Maintained for high-integrity defense deployments.* 🫡

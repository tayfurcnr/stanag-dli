# STANAG 4586 AEP-84 Volume II Compliance Report

**Status:** Core generator and wire-format path reviewed against AEP-84 Volume II
**Date:** April 2026
**Scope:** SDLI message definitions, generated C++/Python message code, ICS generation, and dissector metadata

This report summarizes what was directly verified against the local AEP-84 Volume II source documents in `docs/`, what was corrected in the repository, and what remains out of scope.

---

## 1. Verified Against AEP-84

The following areas were checked directly against the local standard sources:

- `docs/ANA STANDART VOL II-AEP-84 VOLII EDA V1 E.pdf`
- `docs/ANA STANDART VOL II-AEP-84 VOLII EDA V1 E.txt`

### 1.1 Reviewed Message Set

The currently implemented message subset in `definitions/messages/` was reviewed against the matching AEP-84 tables:

- `#1` CUCS Authorisation Request
- `#2` VSM Authorisation Response
- `#3` Vehicle ID
- `#4` Positive Handover Authorisation Request
- `#5` Positive Handover Authorisation Granted
- `#2000` Vehicle Configuration Command
- `#2007` Unmanned Aircraft Lights
- `#2008` Engine Command
- `#2010` UA Stick Command
- `#2016` Vehicle Operating Mode Command
- `#2017` Loiter Configuration
- `#3001` Vehicle Operating Mode Report
- `#3002` Vehicle Operating States
- `#3004` Loiter Configuration Report
- `#3006` Vehicle Lights State
- `#3007` Engine Operating States
- `#3011` UA Stick Status
- `#4000` Inertial States
- `#4001` From-To-Next Waypoint States
- `#13002` UA Position Waypoint
- `#16002` Heartbeat
- `#17000` Message Acknowledgement

### 1.2 Confirmed Standard Alignment

The following properties were checked in the reviewed subset:

- Presence vector width and field count
- Field order
- Field names as represented in SDLI definitions
- Integer width and signedness
- Field-level scaling factors where applicable
- Key BAM and timestamp field usage

### 1.3 Standard Mismatch Found And Corrected

One confirmed mismatch was found and corrected:

- `Message #1 / CUCS Type`
  - Standard: `Unsigned 1`
  - Previous repository definition: `uint16`
  - Corrected repository definition: `uint8`

This correction was propagated through generated C++ and Python message code and revalidated.

---

## 2. Generator Compliance Improvements

In addition to the direct SDLI correction above, the generator path was tightened so generated code now better preserves AEP-84 encoding intent.

### 2.1 C++ Generator

`generator/dli_gen.py` now preserves declared field widths instead of widening fields by default. This includes:

- `uint16 -> uint16_t`
- `int16 -> int16_t`
- `uint24 -> 3-byte serialization`
- `uint40 -> 5-byte serialization`

Presence vector storage may use a wider host integer internally, but serialization still writes the exact byte width declared by the message definition.

### 2.2 Python Generator

`generator/dli_gen_python.py` and `idl/python/dli/core/bit_cursor.py` now distinguish signed and unsigned 24-bit values correctly.

This removed a previous risk where `uint24` values could be handled through signed `int24` logic.

### 2.3 ICS Generator

`generator/ics_gen.py` now derives widths and encodings from the actual SDLI/type definitions instead of hardcoded assumptions.

This means the generated ICS report reflects:

- actual field byte length
- actual declared scalar type
- actual field-level scaling

### 2.4 Lua Dissector Generator

`generator/dissector_gen.py` now preserves distinctions such as:

- `uint24` vs `int24`
- `uint40`
- field signedness
- explicit multi-byte reads for 3-byte and 5-byte values

This improves analysis fidelity without changing wire format behavior.

### 2.5 Profile Generator Validation

`generator/profile_gen.py` now validates profile structure more strictly, including:

- include/exclude conflicts
- unknown explicit message IDs
- malformed profile sections

This is not an AEP-84 wire-format issue, but it reduces the chance of silently generating incorrect protocol profiles.

---

## 3. Validation Performed

The following checks were run successfully after the standard correction and generator updates:

- `python3 generator/tests/validation_test.py`
- `python3 generator/dli_gen.py`
- `python3 generator/dli_gen_python.py`
- `python3 generator/ics_gen.py`
- `python3 generator/dissector_gen.py`
- `python3 generator/profile_gen.py`
- `python3 idl/python/tests/verify_python_dli.py`
- `env CCACHE_DISABLE=1 cmake --build build -j4`

These checks confirm that the reviewed message set, generated artifacts, and build outputs remain internally consistent after the compliance fixes.

---

## 4. Remaining Scope Limits

This report does not claim full certification of the entire STANAG 4586 ecosystem.

The following remain outside the scope of this review:

- message tables not currently represented in `definitions/messages/`
- runtime interoperability with third-party NATO/UAS implementations
- transport/network behavior beyond local build and protocol-generation validation
- operational CONOPS, LOI mission usage, or platform certification concerns

In short: the current repository subset was reviewed and corrected where evidence was clear, but this should be read as an implementation compliance audit, not a formal external conformance certification.

---

## 5. Final Assessment

For the message subset currently implemented in this repository, the generator and wire-format path are in good shape after review. One confirmed AEP-84 field-width mismatch was found in `Message #1`, corrected, regenerated, tested, and built successfully.

No additional confirmed message-definition mismatches remain in the reviewed subset based on the local PDF-backed audit.

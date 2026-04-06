import os
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "generator"))
sys.path.insert(0, os.path.join(ROOT, "idl", "python"))

from validation import SDLIValidationError, validate_message_definition, validate_types_definition
from dli_gen import DLIGenerator
from dli_gen_python import DLIPythonGenerator
from ics_gen import ICSGenerator
from dissector_gen import DissectorGenerator
from profile_gen import ProfileGenerator
import yaml


def load_types():
    with open(os.path.join(ROOT, "definitions/common/types.sdli"), "r") as f:
        types = yaml.safe_load(f)["types"]
    validate_types_definition(types, os.path.join(ROOT, "definitions/common/types.sdli"))
    return types


def test_duplicate_pv_bit_rejected():
    types = load_types()
    msg = {
        "id": 99999,
        "name": "BrokenMessage",
        "pv": {"size": 1, "type": "uint8"},
        "fields": [
            {"name": "A", "pv_bit": 0, "type": "uint8"},
            {"name": "B", "pv_bit": 0, "type": "uint8"},
        ],
    }
    try:
        validate_message_definition(msg, types, "broken.sdli")
    except SDLIValidationError as exc:
        assert "reuses pv_bit 0" in str(exc)
        return
    raise AssertionError("duplicate pv_bit should fail validation")


def test_unknown_type_rejected():
    types = load_types()
    msg = {
        "id": 99998,
        "name": "BrokenTypeMessage",
        "pv": {"size": 1, "type": "uint8"},
        "fields": [
            {"name": "Mystery", "pv_bit": 0, "type": "NopeType"},
        ],
    }
    try:
        validate_message_definition(msg, types, "broken_type.sdli")
    except SDLIValidationError as exc:
        assert "unknown type 'NopeType'" in str(exc)
        return
    raise AssertionError("unknown field type should fail validation")


def test_existing_definition_passes():
    types = load_types()
    path = os.path.join(ROOT, "definitions/messages/16002_Heartbeat.sdli")
    with open(path, "r") as f:
        msg = yaml.safe_load(f)
    validate_message_definition(msg, types, path)


def test_five_byte_presence_vector_passes():
    types = load_types()
    path = os.path.join(ROOT, "definitions/messages/03007_EngineOperatingStates.sdli")
    with open(path, "r") as f:
        msg = yaml.safe_load(f)
    validate_message_definition(msg, types, path)


def test_presence_vector_type_size_mismatch_rejected():
    types = load_types()
    msg = {
        "id": 99997,
        "name": "BrokenPresenceVector",
        "pv": {"size": 5, "type": "uint32"},
        "fields": [
            {"name": "A", "pv_bit": 0, "type": "uint8"},
        ],
    }
    try:
        validate_message_definition(msg, types, "broken_pv.sdli")
    except SDLIValidationError as exc:
        assert "pv.type 'uint32'" in str(exc)
        return
    raise AssertionError("mismatched pv.type and pv.size should fail validation")


def test_cpp_generator_preserves_uint16_width():
    gen = DLIGenerator(ROOT)
    path = os.path.join(ROOT, "definitions/messages/00004_PositiveHandoverAuthorisationRequest.sdli")
    with open(path, "r") as f:
        msg = yaml.safe_load(f)
    fields = {field["name"]: field for field in gen._resolve_fields(msg["fields"])}
    assert fields["Vehicle Type"]["cpp_type"] == "uint16_t"
    assert fields["Controlled Station 1-16"]["cpp_type"] == "uint16_t"


def test_generators_preserve_scaled_field_storage_width():
    cpp_gen = DLIGenerator(ROOT)
    py_gen = DLIPythonGenerator(ROOT)
    path = os.path.join(ROOT, "definitions/messages/04000_InertialStates.sdli")
    with open(path, "r") as f:
        msg = yaml.safe_load(f)

    cpp_fields = {field["name"]: field for field in cpp_gen._resolve_fields(msg["fields"])}
    py_fields = {field["safe_name"]: field for field in py_gen._resolve_fields(msg["fields"])}

    assert cpp_fields["U_Speed"]["cpp_type"] == "double"
    assert "to_scaled<int16_t>" in cpp_fields["U_Speed"]["serialize_expr"]
    assert "int16_t tmp_u_speed" in cpp_fields["U_Speed"]["deserialize_expr"]

    assert py_fields["u_speed"]["default_val"] == "0.0"
    assert "write_int16" in py_fields["u_speed"]["serialize_expr"]
    assert "read_int16" in py_fields["u_speed"]["deserialize_expr"]


def test_ics_generator_uses_sdli_type_widths_and_scales():
    ics_gen = ICSGenerator(ROOT)

    altitude = ics_gen._resolve_type_info("Altitude")
    assert altitude["length"] == 4
    assert "scale=0.01" in altitude["encoding"]

    uint24 = ics_gen._resolve_type_info("uint24")
    assert uint24["length"] == 3
    assert uint24["encoding"] == "uint24"

    path = os.path.join(ROOT, "definitions/messages/04000_InertialStates.sdli")
    with open(path, "r") as f:
        msg = yaml.safe_load(f)
    fields = {field["name"]: field for field in ics_gen._resolve_fields_for_ics(msg["fields"])}
    assert fields["U_Speed"]["length"] == 2
    assert "Field scale=0.05" in fields["U_Speed"]["encoding"]


def test_python_uint24_support_and_template_use_unsigned_pv():
    from dli.core.bit_cursor import BitCursor

    buf = bytearray(3)
    cursor = BitCursor(buf)
    cursor.write_uint24(0xFEDCBA)
    assert list(buf) == [0xFE, 0xDC, 0xBA]

    cursor = BitCursor(buf)
    assert cursor.read_uint24() == 0xFEDCBA

    template_path = os.path.join(ROOT, "generator/templates/message.py.template")
    with open(template_path, "r") as f:
        template = f.read()
    assert "cursor.write_uint24(self.pv)" in template
    assert "self.pv = cursor.read_uint24()" in template


def test_python_generator_uses_unsigned_uint24():
    py_gen = DLIPythonGenerator(ROOT)
    path = os.path.join(ROOT, "definitions/messages/02007_UnmannedAircraftLights.sdli")
    with open(path, "r") as f:
        msg = yaml.safe_load(f)
    fields = {field["safe_name"]: field for field in py_gen._resolve_fields(msg["fields"])}
    assert "write_uint24" in fields["activity_id"]["serialize_expr"]
    assert "read_uint24" in fields["activity_id"]["deserialize_expr"]


def test_dissector_generator_preserves_24_and_40_bit_widths():
    dissector = DissectorGenerator(ROOT)
    uint24 = dissector.get_field_info("uint24")
    uint40 = dissector.get_field_info("uint40")
    int24 = dissector.get_field_info("int24")

    assert uint24["size"] == 3 and uint24["signed"] is False
    assert uint40["size"] == 5 and uint40["signed"] is False
    assert int24["size"] == 3 and int24["signed"] is True


def test_flattened_pv_bit_zero_is_preserved():
    synthetic_fields = [
        {"name": "Position", "type": "GlobalPos", "composition": "flattened", "pv_bit": 0},
    ]

    cpp_gen = DLIGenerator(ROOT)
    py_gen = DLIPythonGenerator(ROOT)
    ics_gen = ICSGenerator(ROOT)

    cpp_fields = cpp_gen._resolve_fields(synthetic_fields)
    py_fields = py_gen._resolve_fields(synthetic_fields)
    ics_fields = ics_gen._resolve_fields_for_ics(synthetic_fields)

    assert [field["pv_bit"] for field in cpp_fields] == [0, 1, 2]
    assert [field["pv_bit"] for field in py_fields] == [0, 1, 2]
    assert [field["pv_bit"] for field in ics_fields] == [0, 1, 2]


def test_profile_generator_validates_and_applies_exclude_groups():
    prof_gen = ProfileGenerator(ROOT)
    prof_gen._validate_profile(
        {
            "name": "Valid_Profile",
            "loi": 2,
            "include_groups": ["SystemID"],
            "exclude_groups": ["FlightVehicleStatus"],
            "include_messages": [16002],
            "exclude_messages": [3],
        },
        "valid.profile",
    )

    try:
        prof_gen._validate_profile(
            {
                "name": "Broken_Profile",
                "loi": 2,
                "include_groups": ["SystemID"],
                "exclude_groups": ["SystemID"],
            },
            "broken.profile",
        )
    except ValueError as exc:
        assert "both included and excluded" in str(exc)
    else:
        raise AssertionError("conflicting include/exclude groups should fail validation")

    with tempfile.TemporaryDirectory() as tmp_root:
        messages_dir = os.path.join(tmp_root, "definitions/messages")
        profiles_dir = os.path.join(tmp_root, "definitions/profiles")
        os.makedirs(messages_dir)
        os.makedirs(profiles_dir)

        with open(os.path.join(messages_dir, "00001_Test.sdli"), "w") as f:
            f.write("id: 1\nname: MsgA\ngroup: GroupA\n")
        with open(os.path.join(messages_dir, "00002_Test.sdli"), "w") as f:
            f.write("id: 2\nname: MsgB\ngroup: GroupB\n")
        with open(os.path.join(profiles_dir, "Test.profile"), "w") as f:
            f.write(
                "name: Test_Profile\n"
                "loi: 2\n"
                "include_groups:\n"
                "  - GroupA\n"
                "exclude_groups:\n"
                "  - GroupB\n"
            )

        temp_prof_gen = ProfileGenerator(tmp_root)
        temp_prof_gen.generate()
        profiles_hpp = os.path.join(tmp_root, "idl/cpp/dli/generated/profiles/Profiles.hpp")
        profiles_py = os.path.join(tmp_root, "idl/python/dli/generated/profiles/__init__.py")
        with open(profiles_hpp, "r") as f:
            generated = f.read()
        assert "p.allow(1); // MsgA (GroupA)" in generated
        assert "p.deny(2); // MsgB (GroupB)" in generated
        with open(profiles_py, "r") as f:
            generated_py = f.read()
        assert "def Test()" in generated_py
        assert "p.allow(1)  # MsgA (GroupA)" in generated_py
        assert "p.deny(2)  # MsgB (GroupB)" in generated_py


if __name__ == "__main__":
    test_duplicate_pv_bit_rejected()
    test_unknown_type_rejected()
    test_existing_definition_passes()
    test_five_byte_presence_vector_passes()
    test_presence_vector_type_size_mismatch_rejected()
    test_cpp_generator_preserves_uint16_width()
    test_generators_preserve_scaled_field_storage_width()
    test_ics_generator_uses_sdli_type_widths_and_scales()
    test_python_uint24_support_and_template_use_unsigned_pv()
    test_python_generator_uses_unsigned_uint24()
    test_dissector_generator_preserves_24_and_40_bit_widths()
    test_flattened_pv_bit_zero_is_preserved()
    test_profile_generator_validates_and_applies_exclude_groups()
    print("generator validation tests passed")

import os


BUILTIN_SCALAR_TYPES = {
    "uint8",
    "uint16",
    "uint24",
    "uint32",
    "uint40",
    "int8",
    "int16",
    "int24",
    "int32",
}

SCALAR_TYPE_SIZES = {
    "uint8": 1,
    "uint16": 2,
    "uint24": 3,
    "uint32": 4,
    "uint40": 5,
    "int8": 1,
    "int16": 2,
    "int24": 3,
    "int32": 4,
}

SUPPORTED_PV_SIZES = {1, 2, 3, 4, 5}


class SDLIValidationError(ValueError):
    pass


def _error(path, message):
    raise SDLIValidationError(f"{os.path.basename(path)}: {message}")


def sanitize_field_name(name):
    safe_name = (
        str(name)
        .lower()
        .replace(" ", "_")
        .replace("&", "and")
        .replace("-", "_")
        .replace("(", "")
        .replace(")", "")
        .replace("/", "_")
    )
    if not safe_name:
        return safe_name
    if safe_name[0].isdigit():
        safe_name = "f_" + safe_name
    return safe_name


def validate_types_definition(types, path):
    if not isinstance(types, dict):
        _error(path, "top-level 'types' mapping is missing or invalid")

    for type_name, type_def in types.items():
        if not isinstance(type_name, str) or not type_name.strip():
            _error(path, "type names must be non-empty strings")
        if not isinstance(type_def, dict):
            _error(path, f"type '{type_name}' must be a mapping")

        composition = type_def.get("composition")
        if composition is not None and composition != "flattened":
            _error(path, f"type '{type_name}' uses unsupported composition '{composition}'")

        if composition == "flattened":
            fields = type_def.get("fields")
            if not isinstance(fields, list) or not fields:
                _error(path, f"flattened type '{type_name}' must define a non-empty 'fields' list")


def _resolve_and_validate_fields(fields, types, path, *, parent_name, start_pv_bit=None, seen_pv_bits=None, seen_names=None):
    if not isinstance(fields, list) or not fields:
        _error(path, f"{parent_name} must define a non-empty 'fields' list")

    if seen_pv_bits is None:
        seen_pv_bits = {}
    if seen_names is None:
        seen_names = {}

    current_pv_bit = start_pv_bit
    resolved_count = 0

    for index, field in enumerate(fields):
        if not isinstance(field, dict):
            _error(path, f"{parent_name} field at index {index} must be a mapping")

        f_name = field.get("name")
        if not isinstance(f_name, str) or not f_name.strip():
            _error(path, f"{parent_name} field at index {index} is missing a valid 'name'")

        safe_name = sanitize_field_name(f_name)
        if not safe_name:
            _error(path, f"{parent_name} field '{f_name}' sanitizes to an empty identifier")
        if safe_name in seen_names:
            _error(
                path,
                f"{parent_name} field '{f_name}' collides with '{seen_names[safe_name]}' after identifier sanitization",
            )
        seen_names[safe_name] = f_name

        f_type_name = field.get("type")
        if not isinstance(f_type_name, str) or not f_type_name.strip():
            _error(path, f"{parent_name} field '{f_name}' is missing a valid 'type'")

        f_type_def = types.get(f_type_name, {})
        if f_type_name not in BUILTIN_SCALAR_TYPES and f_type_name not in types:
            _error(path, f"{parent_name} field '{f_name}' references unknown type '{f_type_name}'")

        composition = field.get("composition") or f_type_def.get("composition")
        if composition is not None and composition != "flattened":
            _error(path, f"{parent_name} field '{f_name}' uses unsupported composition '{composition}'")

        if composition == "flattened":
            sub_fields = f_type_def.get("fields")
            if not isinstance(sub_fields, list) or not sub_fields:
                _error(path, f"{parent_name} field '{f_name}' references flattened type '{f_type_name}' without fields")

            f_pv_bit = field.get("pv_bit")
            if f_pv_bit is None:
                f_pv_bit = current_pv_bit
            if f_pv_bit is None:
                _error(path, f"{parent_name} field '{f_name}' requires an explicit 'pv_bit' or inherited PV position")
            if not isinstance(f_pv_bit, int) or f_pv_bit < 0:
                _error(path, f"{parent_name} field '{f_name}' has invalid pv_bit '{f_pv_bit}'")

            sub_count = _resolve_and_validate_fields(
                sub_fields,
                types,
                path,
                parent_name=f"{parent_name} field '{f_name}'",
                start_pv_bit=f_pv_bit,
                seen_pv_bits=seen_pv_bits,
                seen_names=seen_names,
            )
            resolved_count += sub_count
            if current_pv_bit is not None:
                current_pv_bit += sub_count
            continue

        f_bit = field.get("pv_bit")
        if f_bit is None and current_pv_bit is not None:
            f_bit = current_pv_bit
            current_pv_bit += 1

        if f_bit is None:
            _error(path, f"{parent_name} field '{f_name}' requires a 'pv_bit'")
        if not isinstance(f_bit, int) or f_bit < 0:
            _error(path, f"{parent_name} field '{f_name}' has invalid pv_bit '{f_bit}'")
        if f_bit in seen_pv_bits:
            _error(path, f"{parent_name} field '{f_name}' reuses pv_bit {f_bit} already used by '{seen_pv_bits[f_bit]}'")
        seen_pv_bits[f_bit] = f_name

        scale = field.get("scale")
        if scale is not None:
            if not isinstance(scale, (int, float)) or scale == 0:
                _error(path, f"{parent_name} field '{f_name}' has invalid scale '{scale}'")
            if f_type_name not in BUILTIN_SCALAR_TYPES:
                _error(path, f"{parent_name} field '{f_name}' uses scale with non-scalar type '{f_type_name}'")

        resolved_count += 1

    return resolved_count


def validate_message_definition(msg, types, path):
    if not isinstance(msg, dict):
        _error(path, "message definition must be a mapping")

    for key in ("id", "name", "pv", "fields"):
        if key not in msg:
            _error(path, f"message is missing required key '{key}'")

    if not isinstance(msg["id"], int) or msg["id"] < 0:
        _error(path, "message 'id' must be a non-negative integer")
    if not isinstance(msg["name"], str) or not msg["name"].strip():
        _error(path, "message 'name' must be a non-empty string")

    pv = msg["pv"]
    if not isinstance(pv, dict):
        _error(path, "message 'pv' must be a mapping")

    pv_size = pv.get("size")
    if not isinstance(pv_size, int) or pv_size not in SUPPORTED_PV_SIZES:
        _error(path, f"message '{msg['name']}' has unsupported pv.size '{pv_size}'")

    pv_type = pv.get("type")
    if not isinstance(pv_type, str) or not pv_type.strip():
        _error(path, f"message '{msg['name']}' must define a non-empty pv.type")
    if pv_type not in SCALAR_TYPE_SIZES:
        _error(path, f"message '{msg['name']}' has unsupported pv.type '{pv_type}'")
    if SCALAR_TYPE_SIZES[pv_type] != pv_size:
        _error(
            path,
            f"message '{msg['name']}' uses pv.type '{pv_type}' with size {SCALAR_TYPE_SIZES[pv_type]}, "
            f"but pv.size is {pv_size}",
        )

    seen_pv_bits = {}
    seen_names = {}
    resolved_field_count = _resolve_and_validate_fields(
        msg["fields"],
        types,
        path,
        parent_name=f"message '{msg['name']}'",
        seen_pv_bits=seen_pv_bits,
        seen_names=seen_names,
    )

    pv_capacity = pv_size * 8
    for pv_bit in seen_pv_bits:
        if pv_bit >= pv_capacity:
            _error(
                path,
                f"message '{msg['name']}' uses pv_bit {pv_bit}, but pv.size={pv_size} only supports bits 0..{pv_capacity - 1}",
            )

    if resolved_field_count == 0:
        _error(path, f"message '{msg['name']}' resolved to zero serializable fields")

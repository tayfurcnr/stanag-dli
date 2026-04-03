import yaml
import os
import sys
import re

from validation import validate_message_definition, validate_types_definition

CPP_SCALAR_TYPES = {
    "uint8": {"cpp_type": "uint8_t", "bytes": 1},
    "uint16": {"cpp_type": "uint16_t", "bytes": 2},
    "uint24": {"cpp_type": "uint32_t", "bytes": 3},
    "uint32": {"cpp_type": "uint32_t", "bytes": 4},
    "uint40": {"cpp_type": "uint64_t", "bytes": 5},
    "int8": {"cpp_type": "int8_t", "bytes": 1},
    "int16": {"cpp_type": "int16_t", "bytes": 2},
    "int24": {"cpp_type": "int32_t", "bytes": 3},
    "int32": {"cpp_type": "int32_t", "bytes": 4},
}

# Simple Template Renderer (Jinja2-Lite)
def render_template(template_str, context):
    # Handle loops: {% for item in items %} ... {% endfor %}
    loop_pattern = re.compile(r'{% for (\w+) in (\w+) %}(.*?){% endfor %}', re.DOTALL)
    while True:
        match = loop_pattern.search(template_str)
        if not match: break
        var_name, list_name, loop_body = match.groups()
        items = context.get(list_name, [])
        rendered_loop = ""
        for item in items:
            item_context = context.copy()
            item_context[var_name] = item
            rendered_loop += render_template(loop_body, item_context)
        template_str = template_str[:match.start()] + rendered_loop + template_str[match.end():]
    
    # Handle conditionals: {% if condition %} ... {% else %} ... {% endif %}
    if_pattern = re.compile(r'{% if (.*?) %}(.*?)(?:{% else %}(.*?))?{% endif %}', re.DOTALL)
    while True:
        match = if_pattern.search(template_str)
        if not match: break
        cond_expr, if_body, else_body = match.groups()
        
        # Resolve path in context
        path = cond_expr.strip().split(' is ')[0].strip()
        parts = path.split('.')
        val = context
        for p in parts:
            if isinstance(val, dict): val = val.get(p.strip())
            else: val = getattr(val, p.strip(), None)
            if val is None: break
        
        # Support "is not none"
        if "is not none" in cond_expr:
            condition_met = (val is not None)
        elif "is none" in cond_expr:
            condition_met = (val is None)
        else:
            condition_met = (val is not None and val is not False)
            
        if condition_met:
            template_str = template_str[:match.start()] + if_body + template_str[match.end():]
        else:
            template_str = template_str[:match.start()] + (else_body or "") + template_str[match.end():]

    # Handle variables: {{ var }} or {{ var.sub }}
    var_pattern = re.compile(r'{{ (.*?) }}')
    def replace_var(match):
        expr = match.group(1).strip()
        parts = expr.split('.')
        val = context
        for p in parts:
            if isinstance(val, dict): val = val.get(p.strip(), "")
            else: val = getattr(val, p.strip(), "")
        return str(val)
    
    return var_pattern.sub(replace_var, template_str)

class DLIGenerator:
    def __init__(self, root):
        self.root = root
        with open(os.path.join(root, "definitions/common/types.sdli"), 'r') as f:
            self.types = yaml.safe_load(f)['types']
        validate_types_definition(self.types, os.path.join(root, "definitions/common/types.sdli"))
        with open(os.path.join(root, "definitions/common/policies.sdli"), 'r') as f:
            self.policies = yaml.safe_load(f)['policies']

    def _sanitize_name(self, field_name):
        safe_name = field_name.lower().replace(" ", "_").replace("&", "and").replace("-", "_").replace("(", "").replace(")", "").replace("/", "_")
        if safe_name[0].isdigit():
            safe_name = "f_" + safe_name
        return safe_name

    def _resolve_type_metadata(self, type_name):
        if type_name in CPP_SCALAR_TYPES:
            return {"kind": "scalar", **CPP_SCALAR_TYPES[type_name]}

        type_def = self.types.get(type_name, {})
        encoding = type_def.get("encoding")

        if encoding == "bam":
            return {
                "kind": "bam",
                "cpp_type": "double",
                "storage": self._resolve_type_metadata(type_def["type"]),
            }

        if encoding == "scaled":
            return {
                "kind": "scaled",
                "cpp_type": "double",
                "storage": self._resolve_type_metadata(type_def["type"]),
                "offset": type_def.get("offset", 0.0),
                "scale": type_def["scale"],
            }

        if type_def.get("base") == "buffer":
            return {
                "kind": "buffer",
                "cpp_type": f"std::array<uint8_t, {type_def['length']}>",
                "length": type_def["length"],
            }

        if "type" in type_def:
            return self._resolve_type_metadata(type_def["type"])

        raise KeyError(f"Unsupported type metadata for '{type_name}'")

    def _cpp_write_expr(self, var_name, storage):
        if storage["bytes"] in (1, 2, 4):
            return f"cursor.write({var_name});"
        return f"cursor.write_int({var_name}, {storage['bytes']});"

    def _cpp_read_expr(self, var_name, storage):
        if storage["bytes"] in (1, 2, 4):
            return f"cursor.read({var_name});"
        return f"cursor.read_int({var_name}, {storage['bytes']});"

    def _resolve_fields(self, sdli_fields, start_pv_bit=None):
        resolved_fields = []
        current_pv_bit = start_pv_bit
        
        for field in sdli_fields:
            f_name = field['name']
            f_type_name = field['type']
            f_type_def = self.types.get(f_type_name, {})
            
            # Recursive flattening
            if field.get('composition') == 'flattened' or f_type_def.get('composition') == 'flattened':
                sub_fields = f_type_def.get('fields', [])
                # Pass the current pv_bit to the sub-fields for expansion
                # If field has a pv_bit, it's the start bit for the sub-fields
                f_pv_bit = field.get('pv_bit')
                if f_pv_bit is None:
                    f_pv_bit = current_pv_bit
                resolved_fields.extend(self._resolve_fields(sub_fields, start_pv_bit=f_pv_bit))
                
                # Heuristic: Increment bit counter by length of sub-fields if we were tracking
                if current_pv_bit is not None:
                    current_pv_bit += len(sub_fields)
                continue

            # Actual bit for this specific field
            f_bit = field.get('pv_bit')
            if f_bit is None and current_pv_bit is not None:
                f_bit = current_pv_bit
                current_pv_bit += 1
            
            safe_name = self._sanitize_name(f_name)
            type_meta = self._resolve_type_metadata(f_type_name)
            cpp_type = type_meta["cpp_type"]

            if type_meta["kind"] == "scalar":
                ser = self._cpp_write_expr(safe_name, type_meta)
                deser = self._cpp_read_expr(safe_name, type_meta)
            elif type_meta["kind"] == "bam":
                storage = type_meta["storage"]
                if storage["bytes"] == 2:
                    ser = f"cursor.write(bam::to_bam16({safe_name}));"
                    deser = f"uint16_t tmp_{safe_name}; cursor.read(tmp_{safe_name}); {safe_name} = bam::from_bam16(tmp_{safe_name});"
                elif storage["bytes"] == 4:
                    ser = f"cursor.write(bam::to_bam32({safe_name}));"
                    deser = f"uint32_t tmp_{safe_name}; cursor.read(tmp_{safe_name}); {safe_name} = bam::from_bam32(tmp_{safe_name});"
                else:
                    raise ValueError(f"Unsupported BAM storage width for '{f_type_name}'")
            elif type_meta["kind"] == "scaled":
                storage = type_meta["storage"]
                scaled_expr = f"scaled::to_scaled<{storage['cpp_type']}>({safe_name}, {type_meta['offset']}, {type_meta['scale']})"
                if storage["bytes"] in (1, 2, 4):
                    ser = f"cursor.write({scaled_expr});"
                else:
                    ser = f"cursor.write_int({scaled_expr}, {storage['bytes']});"
                deser = (
                    f"{storage['cpp_type']} tmp_{safe_name}; "
                    f"{self._cpp_read_expr(f'tmp_{safe_name}', storage)} "
                    f"{safe_name} = scaled::from_scaled<{storage['cpp_type']}, double>(tmp_{safe_name}, {type_meta['offset']}, {type_meta['scale']});"
                )
            elif type_meta["kind"] == "buffer":
                ser = f"for (const auto& byte : {safe_name}) {{ cursor.write(byte); }}"
                deser = f"for (auto& byte : {safe_name}) {{ cursor.read(byte); }}"
            else:
                raise ValueError(f"Unsupported type kind for '{f_type_name}'")

            if field.get('scale') is not None:
                storage = type_meta if type_meta["kind"] == "scalar" else type_meta["storage"]
                cpp_type = "double"
                scaled_expr = f"scaled::to_scaled<{storage['cpp_type']}>({safe_name}, 0.0, {field['scale']})"
                if storage["bytes"] in (1, 2, 4):
                    ser = f"cursor.write({scaled_expr});"
                else:
                    ser = f"cursor.write_int({scaled_expr}, {storage['bytes']});"
                deser = (
                    f"{storage['cpp_type']} tmp_{safe_name}; "
                    f"{self._cpp_read_expr(f'tmp_{safe_name}', storage)} "
                    f"{safe_name} = scaled::from_scaled<{storage['cpp_type']}, double>(tmp_{safe_name}, 0.0, {field['scale']});"
                )

            resolved_fields.append({
                'name': f_name,
                'safe_name': safe_name,
                'cpp_type': cpp_type,
                'pv_bit': f_bit,
                'serialize_expr': ser,
                'deserialize_expr': deser,
                'unit': field.get('unit') or f_type_def.get('unit')
            })
        return resolved_fields

    def generate_message(self, message_sdli_path):
        with open(message_sdli_path, 'r') as f:
            msg = yaml.safe_load(f)
        validate_message_definition(msg, self.types, message_sdli_path)
        
        pv_info = msg['pv']
        pv_size = 4 
        if isinstance(pv_info.get('size'), int):
            pv_size = pv_info['size']
            
        context = {
            'id': msg['id'],
            'name': msg['name'],
            'pv_size': pv_size,
            'fields': self._resolve_fields(msg['fields'])
        }
            
        template_path = os.path.join(self.root, "generator/templates/message.hpp.template")
        with open(template_path, 'r') as f:
            template_content = f.read()
            
        output = render_template(template_content, context)
        
        self.output_dir = os.path.join(self.root, "idl/cpp/dli/generated/messages")
        os.makedirs(self.output_dir, exist_ok=True)
        
        out_path = os.path.join(self.output_dir, f"{msg['name']}.hpp")
        with open(out_path, 'w') as f:
            f.write(output)
        print(f"Generated [C++]: {out_path}")

if __name__ == "__main__":
    # Dynamically find project root based on script location
    root_path = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    gen = DLIGenerator(root_path)
    msg_dir = os.path.join(root_path, "definitions/messages")
    for filename in os.listdir(msg_dir):
        if filename.endswith(".sdli"):
            gen.generate_message(os.path.join(msg_dir, filename))

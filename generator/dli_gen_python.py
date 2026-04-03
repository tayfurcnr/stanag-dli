import yaml
import os
import sys
import re

from validation import validate_message_definition, validate_types_definition

PY_SCALAR_TYPES = {
    "uint8": {"bytes": 1, "write": "write_uint8", "read": "read_uint8"},
    "uint16": {"bytes": 2, "write": "write_uint16", "read": "read_uint16"},
    "uint24": {"bytes": 3, "write": "write_uint24", "read": "read_uint24"},
    "uint32": {"bytes": 4, "write": "write_uint32", "read": "read_uint32"},
    "uint40": {"bytes": 5, "write": "write_uint40", "read": "read_uint40"},
    "int8": {"bytes": 1, "write": "write_int8", "read": "read_int8"},
    "int16": {"bytes": 2, "write": "write_int16", "read": "read_int16"},
    "int24": {"bytes": 3, "write": "write_int24", "read": "read_int24"},
    "int32": {"bytes": 4, "write": "write_int32", "read": "read_int32"},
}

# Simple Template Renderer (Copied from dli_gen.py)
def render_template(template_str, context):
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
    
    if_pattern = re.compile(r'{% if (.*?) %}(.*?)(?:{% else %}(.*?))?{% endif %}', re.DOTALL)
    while True:
        match = if_pattern.search(template_str)
        if not match: break
        cond_expr, if_body, else_body = match.groups()
        path = cond_expr.strip().split(' == ')[0].strip()
        val_to_compare = None
        if ' == ' in cond_expr:
            val_to_compare = int(cond_expr.split(' == ')[1].strip())
        
        parts = path.split('.')
        val = context
        for p in parts:
            if isinstance(val, dict): val = val.get(p.strip())
            else: val = getattr(val, p.strip(), None)
            if val is None: break
        
        if val_to_compare is not None:
            condition_met = (val == val_to_compare)
        else:
            condition_met = (val is not None and val is not False)
            
        if condition_met:
            template_str = template_str[:match.start()] + if_body + template_str[match.end():]
        else:
            template_str = template_str[:match.start()] + (else_body or "") + template_str[match.end():]

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

class DLIPythonGenerator:
    def __init__(self, root):
        self.root = root
        with open(os.path.join(root, "definitions/common/types.sdli"), 'r') as f:
            self.types = yaml.safe_load(f)['types']
        validate_types_definition(self.types, os.path.join(root, "definitions/common/types.sdli"))

    def _sanitize_name(self, field_name):
        safe_name = field_name.lower().replace(" ", "_").replace("&", "and").replace("-", "_").replace("(", "").replace(")", "").replace("/", "_")
        if safe_name[0].isdigit():
            safe_name = "f_" + safe_name
        return safe_name

    def _resolve_type_metadata(self, type_name):
        if type_name in PY_SCALAR_TYPES:
            return {"kind": "scalar", **PY_SCALAR_TYPES[type_name]}

        type_def = self.types.get(type_name, {})
        encoding = type_def.get("encoding")

        if encoding == "bam":
            return {
                "kind": "bam",
                "storage": self._resolve_type_metadata(type_def["type"]),
            }

        if encoding == "scaled":
            return {
                "kind": "scaled",
                "storage": self._resolve_type_metadata(type_def["type"]),
                "offset": type_def.get("offset", 0.0),
                "scale": type_def["scale"],
            }

        if type_def.get("base") == "buffer":
            return {
                "kind": "buffer",
                "length": type_def["length"],
            }

        if "type" in type_def:
            return self._resolve_type_metadata(type_def["type"])

        raise KeyError(f"Unsupported type metadata for '{type_name}'")

    def _resolve_fields(self, sdli_fields, start_pv_bit=None):
        resolved_fields = []
        current_pv_bit = start_pv_bit
        
        for field in sdli_fields:
            f_name = field['name']
            f_type_name = field['type']
            f_type_def = self.types.get(f_type_name, {})
            
            if field.get('composition') == 'flattened' or f_type_def.get('composition') == 'flattened':
                sub_fields = f_type_def.get('fields', [])
                f_pv_bit = field.get('pv_bit')
                if f_pv_bit is None:
                    f_pv_bit = current_pv_bit
                resolved_fields.extend(self._resolve_fields(sub_fields, start_pv_bit=f_pv_bit))
                if current_pv_bit is not None: current_pv_bit += len(sub_fields)
                continue

            f_bit = field.get('pv_bit')
            if f_bit is None and current_pv_bit is not None:
                f_bit = current_pv_bit
                current_pv_bit += 1
            
            safe_name = self._sanitize_name(f_name)
            type_meta = self._resolve_type_metadata(f_type_name)

            default_val = "0"
            ser = f"cursor.{type_meta['write']}(self.{safe_name})" if type_meta["kind"] == "scalar" else ""
            deser = f"self.{safe_name} = cursor.{type_meta['read']}()" if type_meta["kind"] == "scalar" else ""

            if type_meta["kind"] == "bam":
                default_val = "0.0"
                storage = type_meta["storage"]
                if storage["bytes"] == 2:
                    ser = f"cursor.write_uint16(BAM.to_bam16(self.{safe_name}))"
                    deser = f"self.{safe_name} = BAM.from_bam16(cursor.read_uint16())"
                elif storage["bytes"] == 4:
                    ser = f"cursor.write_uint32(BAM.to_bam32(self.{safe_name}))"
                    deser = f"self.{safe_name} = BAM.from_bam32(cursor.read_uint32())"
                else:
                    raise ValueError(f"Unsupported BAM storage width for '{f_type_name}'")
            elif type_meta["kind"] == "scaled":
                default_val = "0.0"
                storage = type_meta["storage"]
                ser = f"cursor.{storage['write']}(Scaled.to_scaled(self.{safe_name}, {type_meta['offset']}, {type_meta['scale']}))"
                deser = f"self.{safe_name} = Scaled.from_scaled(cursor.{storage['read']}(), {type_meta['offset']}, {type_meta['scale']})"
            elif type_meta["kind"] == "buffer":
                default_val = f"bytearray({type_meta['length']})"
                ser = f"for _byte in self.{safe_name}: cursor.write_uint8(_byte)"
                deser = f"self.{safe_name} = bytearray(cursor.read_uint8() for _ in range({type_meta['length']}))"

            # Handle scaling if present in fields
            if field.get('scale'):
                default_val = "0.0"
                storage = type_meta if type_meta["kind"] == "scalar" else type_meta["storage"]
                ser = f"cursor.{storage['write']}(Scaled.to_scaled(self.{safe_name}, 0.0, {field['scale']}))"
                deser = f"self.{safe_name} = Scaled.from_scaled(cursor.{storage['read']}(), 0.0, {field['scale']})"

            resolved_fields.append({
                'safe_name': safe_name,
                'default_val': default_val,
                'pv_bit': f_bit,
                'serialize_expr': ser,
                'deserialize_expr': deser
            })
        return resolved_fields

    def generate_message(self, message_sdli_path):
        with open(message_sdli_path, 'r') as f:
            msg = yaml.safe_load(f)
        validate_message_definition(msg, self.types, message_sdli_path)
        
        pv_info = msg['pv']
        pv_size = pv_info.get('size', 4)
            
        context = {
            'name': msg['name'],
            'pv_size': pv_size,
            'fields': self._resolve_fields(msg['fields'])
        }
            
        template_path = os.path.join(self.root, "generator/templates/message.py.template")
        with open(template_path, 'r') as f:
            template_content = f.read()
            
        output = render_template(template_content, context)
        
        output_dir = os.path.join(self.root, "idl/python/dli/generated/messages")
        os.makedirs(output_dir, exist_ok=True)
        
        out_path = os.path.join(output_dir, f"{msg['name']}.py")
        with open(out_path, 'w') as f:
            f.write(output)
        print(f"Generated [Python]: {out_path}")

if __name__ == "__main__":
    root_path = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    gen = DLIPythonGenerator(root_path)
    msg_dir = os.path.join(root_path, "definitions/messages")
    for filename in os.listdir(msg_dir):
        if filename.endswith(".sdli"):
            gen.generate_message(os.path.join(msg_dir, filename))

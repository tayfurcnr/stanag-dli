import yaml
import os

class DissectorGenerator:
    def __init__(self, root_dir):
        self.root_dir = root_dir
        self.types = self._load_common_types()
        self.messages = self._load_messages()

    def _load_common_types(self):
        with open(os.path.join(self.root_dir, "definitions/common/types.sdli"), 'r') as f:
            return yaml.safe_load(f)['types']

    def _load_messages(self):
        msg_dir = os.path.join(self.root_dir, "definitions/messages")
        messages = []
        for filename in sorted(os.listdir(msg_dir)):
            if filename.endswith(".sdli"):
                with open(os.path.join(msg_dir, filename), 'r') as f:
                    messages.append(yaml.safe_load(f))
        return messages

    def get_field_info(self, type_name):
        scalar_types = {
            "uint8": {"size": 1, "signed": False, "ws_type": "uint8"},
            "uint16": {"size": 2, "signed": False, "ws_type": "uint16"},
            "uint24": {"size": 3, "signed": False, "ws_type": "uint32"},
            "uint32": {"size": 4, "signed": False, "ws_type": "uint32"},
            "uint40": {"size": 5, "signed": False, "ws_type": "uint64"},
            "int8": {"size": 1, "signed": True, "ws_type": "int8"},
            "int16": {"size": 2, "signed": True, "ws_type": "int16"},
            "int24": {"size": 3, "signed": True, "ws_type": "int32"},
            "int32": {"size": 4, "signed": True, "ws_type": "int32"},
        }
        if type_name in scalar_types:
            return scalar_types[type_name]

        t_def = self.types.get(type_name, {})
        if not t_def:
            raise KeyError(f"Unsupported dissector type '{type_name}'")

        if t_def.get("base") == "buffer":
            return {"size": t_def["length"], "signed": False, "ws_type": "string"}

        if "size" in t_def:
            size = t_def["size"]
            ws_type = "uint8" if size == 1 else "uint16" if size == 2 else "uint32" if size <= 4 else "uint64"
            return {"size": size, "signed": False, "ws_type": ws_type}

        if "type" in t_def:
            return self.get_field_info(t_def["type"])

        raise KeyError(f"Unsupported dissector type metadata for '{type_name}'")

    def generate(self):
        lua = []
        lua.append("-- STANAG 4586 DLI Dissector (Auto-generated)")
        lua.append("local dli_proto = Proto('dli', 'STANAG 4586 DLI')\n")
        # Decoding Helpers
        lua.append("-- Compatibility: Find bit library")
        lua.append("local bit = bit32 or bit or require('bit')\n")
        
        lua.append("-- Decoding Helpers")
        lua.append("function decode_bam(val, bits, min_val, max_val)")
        lua.append("    local range = max_val - min_val")
        lua.append("    local max_int = math.pow(2, bits)")
        lua.append("    return min_val + (val / max_int) * range")
        lua.append("end\n")

        lua.append("function decode_scaled(val, scale, offset)")
        lua.append("    return (val * scale) + offset")
        lua.append("end\n")

        lua.append("function read_uint_be(buffer, offset, size)")
        lua.append("    local value = 0")
        lua.append("    for i = 0, size - 1 do")
        lua.append("        value = value * 256 + buffer(offset + i, 1):uint()")
        lua.append("    end")
        lua.append("    return value")
        lua.append("end\n")

        lua.append("function read_int_be(buffer, offset, size)")
        lua.append("    local value = read_uint_be(buffer, offset, size)")
        lua.append("    local sign_bit = math.pow(2, size * 8 - 1)")
        lua.append("    if value >= sign_bit then")
        lua.append("        value = value - math.pow(2, size * 8)")
        lua.append("    end")
        lua.append("    return value")
        lua.append("end\n")

        lua.append("local f = dli_proto.fields")
        lua.append("f.res1 = ProtoField.uint16('dli.res1', 'Reserved 1', base.HEX)")
        lua.append("f.len  = ProtoField.uint16('dli.len',  'Payload Length', base.DEC)")
        lua.append("f.src  = ProtoField.uint32('dli.src',  'Source ID', base.DEC)")
        lua.append("f.dst  = ProtoField.uint32('dli.dst',  'Destination ID', base.DEC)")
        lua.append("f.type = ProtoField.uint16('dli.type', 'Message Type', base.DEC)")
        lua.append("f.prop = ProtoField.uint16('dli.prop', 'Message Properties', base.HEX)")
        lua.append("f.res2 = ProtoField.uint32('dli.res2', 'Reserved 2', base.HEX)\n")

        for msg in self.messages:
            lua.append(f"-- Fields for {msg['id']} {msg['name']}")
            self._gen_field_defs(msg['fields'], msg['name'], lua)

        lua.append("\nfunction dli_proto.dissector(buffer, pinfo, tree)")
        lua.append("    local length = buffer:len()")
        lua.append("    if length < 20 then return end\n")
        lua.append("    pinfo.cols.protocol = 'DLI'")
        lua.append("    local subtree = tree:add(dli_proto, buffer(), 'STANAG 4586 DLI Packet')\n")
        
        lua.append("    subtree:add(f.res1, buffer(0, 2))")
        lua.append("    subtree:add(f.len,  buffer(2, 2))")
        lua.append("    subtree:add(f.src,  buffer(4, 4))")
        lua.append("    subtree:add(f.dst,  buffer(8, 4))")
        lua.append("    local msg_type = buffer(12, 2):uint()")
        lua.append("    subtree:add(f.type, buffer(12, 2))")
        lua.append("    subtree:add(f.prop, buffer(14, 2))")
        lua.append("    subtree:add(f.res2, buffer(16, 4))\n")

        lua.append("    local payload_len = buffer(2, 2):uint()")
        lua.append("    if payload_len > 0 and length >= 20 + payload_len then")
        lua.append("        local pay_tree = subtree:add(dli_proto, buffer(20, payload_len), 'Payload')")
        lua.append("        local offset = 20\n")
        
        first = True
        for msg in self.messages:
            cond = "if" if first else "elseif"
            first = False
            lua.append(f"        {cond} msg_type == {msg['id']} then")
            lua.append(f"            pinfo.cols.info = '{msg['name']}'")
            
            pv_size = msg.get('pv', {}).get('size', 4)
            lua.append(f"            local pv = read_uint_be(buffer, offset, {pv_size})")
            lua.append(f"            pay_tree:add(buffer(offset, {pv_size}), 'Presence Vector: ' .. string.format('0x%X', pv))")
            lua.append(f"            offset = offset + {pv_size}\n")
            
            self._gen_dissection_logic(msg['fields'], msg['name'], lua)
        
        lua.append("        end")
        lua.append("    end")
        lua.append("end\n")
        
        lua.append("local udp_table = DissectorTable.get('udp.port')")
        lua.append("udp_table:add(30001, dli_proto)")

        output_dir = os.path.join(self.root_dir, "idl/lua")
        os.makedirs(output_dir, exist_ok=True)
            
        output_path = os.path.join(output_dir, "dli.lua")
        with open(output_path, 'w') as f:
            f.write("\n".join(lua))

    def _gen_field_defs(self, fields, prefix, lua):
        for field in fields:
            name = field['name']
            ftype = field['type']
            if field.get('composition') == 'flattened':
                comp_def = self.types.get(ftype, {})
                self._gen_field_defs(comp_def['fields'], f"{prefix}_{name}", lua)
                continue
            type_info = self.get_field_info(ftype)
            lua_ws_type = type_info["ws_type"]
            
            base_display = "base.ASCII" if lua_ws_type == "string" else "base.DEC"
            lua.append(f"f.{prefix}_{name} = ProtoField.{lua_ws_type}('dli.{prefix}.{name}', '{name}', {base_display})")

    def _gen_dissection_logic(self, fields, prefix, lua):
        for field in fields:
            name = field['name']
            ftype = field['type']
            pv_bit = field.get('pv_bit')

            if field.get('composition') == 'flattened':
                comp_def = self.types.get(ftype, {})
                self._gen_dissection_logic(comp_def['fields'], f"{prefix}_{name}", lua)
                continue

            type_info = self.get_field_info(ftype)
            size = type_info["size"]
            indent = "            "
            if pv_bit is not None:
                lua.append(f"{indent}if bit.band(pv, bit.lshift(1, {pv_bit})) ~= 0 then")
                indent += "    "
            
            t_def = self.types.get(ftype, {})
            # Field addition with engineering decoding
            if t_def.get('encoding') == 'bam':
                low, high = t_def['range']
                lua.append(f"{indent}local raw = read_uint_be(buffer, offset, {size})")
                lua.append(f"{indent}local eng = decode_bam(raw, {size*8}, {low}, {high})")
                lua.append(f"{indent}pay_tree:add(f.{prefix}_{name}, buffer(offset, {size})):append_text(string.format(' (Eng: %.6f)', eng))")
            elif t_def.get('encoding') == 'scaled':
                scale = t_def['scale']
                offset = t_def.get('offset', 0.0)
                read_fn = "read_int_be" if type_info["signed"] else "read_uint_be"
                lua.append(f"{indent}local raw = {read_fn}(buffer, offset, {size})")
                lua.append(f"{indent}local eng = decode_scaled(raw, {scale}, {offset})")
                lua.append(f"{indent}pay_tree:add(f.{prefix}_{name}, buffer(offset, {size})):append_text(string.format(' (Eng: %.3f %s)', eng, '{t_def.get('unit', '')}'))")
            else:
                lua.append(f"{indent}pay_tree:add(f.{prefix}_{name}, buffer(offset, {size}))")
            
            lua.append(f"{indent}offset = offset + {size}")
            if pv_bit is not None:
                lua.append("            end")

if __name__ == "__main__":
    root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    DissectorGenerator(root).generate()
    print("Generated: dli.lua")

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
        if type_name in ["uint8", "int8"]: return 1, "uint8"
        if type_name in ["uint16", "int16"]: return 2, "uint16"
        if type_name in ["uint32", "int32"]: return 4, "uint32"
        if type_name in ["uint64", "int64"]: return 8, "uint64"
        if type_name == "float": return 4, "float"
        if type_name == "double": return 8, "double"
        
        t_def = self.types.get(type_name, {})
        if not t_def: return 4, "uint32"

        if 'length' in t_def: return t_def['length'], "string"
        if 'size' in t_def:
            size = t_def['size']
            if size <= 1: return 1, "uint8"
            if size <= 2: return 2, "uint16"
            if size <= 4: return 4, "uint32"
            return size, "uint64"

        if 'type' in t_def: return self.get_field_info(t_def['type'])
        return 4, "uint32"

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
            lua.append(f"            local pv = buffer(offset, {pv_size}):uint()")
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
            size, ws_type = self.get_field_info(ftype)
            lua_ws_type = "uint32" if ws_type == "uint24" else ws_type
            
            base_display = "base.ASCII" if ws_type == "string" else "base.DEC"
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

            size, _ = self.get_field_info(ftype)
            indent = "            "
            if pv_bit is not None:
                lua.append(f"{indent}if bit.band(pv, bit.lshift(1, {pv_bit})) ~= 0 then")
                indent += "    "
            
            t_def = self.types.get(ftype, {})
            # Field addition with engineering decoding
            if t_def.get('encoding') == 'bam':
                low, high = t_def['range']
                lua.append(f"{indent}local raw = buffer(offset, {size}):uint()")
                lua.append(f"{indent}local eng = decode_bam(raw, {size*8}, {low}, {high})")
                lua.append(f"{indent}pay_tree:add(f.{prefix}_{name}, buffer(offset, {size})):append_text(string.format(' (Eng: %.6f)', eng))")
            elif t_def.get('encoding') == 'scaled':
                scale = t_def['scale']
                offset = t_def.get('offset', 0.0)
                lua.append(f"{indent}local raw = buffer(offset, {size}):int()")
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

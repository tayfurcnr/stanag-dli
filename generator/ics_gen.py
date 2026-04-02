import yaml
import os
import sys

class ICSGenerator:
    def __init__(self, root):
        self.root = root
        with open(os.path.join(root, "definitions/common/types.sdli"), 'r') as f:
            self.types = yaml.safe_load(f)['types']
        self.messages_dir = os.path.join(root, "definitions/messages")
        self.profiles_dir = os.path.join(root, "definitions/profiles")

    def _get_type_info(self, t_name):
        t_def = self.types.get(t_name, {})
        length = 1 # Default
        encoding = t_name
        
        if t_name == "Timestamp": length = 5; encoding = "uint40 (Scaled 1ms)"
        elif t_name == "BAM16": length = 2; encoding = "BAM16"
        elif t_name == "BAM32": length = 4; encoding = "BAM32"
        elif t_name == "Altitude": length = 3; encoding = "int24 (Scaled 0.02m)"
        elif t_name == "uint32": length = 4; encoding = "uint32"
        elif t_name == "uint16": length = 2; encoding = "uint16"
        elif t_name == "uint8": length = 1; encoding = "uint8"
        elif t_name == "int16": length = 2; encoding = "int16"
        else: length = t_def.get('length', 1)
        
        return length, encoding

    def _resolve_fields_for_ics(self, sdli_fields, start_pv_bit=None):
        resolved = []
        current_pv_bit = start_pv_bit
        for field in sdli_fields:
            f_name = field['name']
            f_type_name = field['type']
            f_type_def = self.types.get(f_type_name, {})
            if field.get('composition') == 'flattened' or f_type_def.get('composition') == 'flattened':
                sub_fields = f_type_def.get('fields', [])
                f_pv_bit = field.get('pv_bit') or current_pv_bit
                resolved.extend(self._resolve_fields_for_ics(sub_fields, start_pv_bit=f_pv_bit))
                if current_pv_bit is not None: current_pv_bit += len(sub_fields)
                continue
            
            f_bit = field.get('pv_bit')
            if f_bit is None and current_pv_bit is not None:
                f_bit = current_pv_bit
                current_pv_bit += 1
            length, encoding = self._get_type_info(f_type_name)
            resolved.append({
                'name': f_name, 'pv_bit': f_bit, 'type': f_type_name,
                'length': length, 'encoding': encoding,
                'unit': field.get('unit') or f_type_def.get('unit', '-'),
                'mandatory': 'M' if f_bit is None else 'O'
            })
        return resolved

    def generate_report(self):
        print("[ICS] Generating High-Fidelity Audit-Friendly ICS...")
        report = "# DLI Interface Control Sheet (ICS) - v1.0 (Draft Aligned to STANAG 4586)\n\n"
        report += "> [!IMPORTANT]\n"
        report += "> This document is a framework-generated ICS draft aligned to STANAG 4586. All PV bits are sequential LSB 0.\n\n"
        
        messages = []
        for filename in sorted(os.listdir(self.messages_dir)):
            if not filename.endswith(".sdli"): continue
            with open(os.path.join(self.messages_dir, filename), 'r') as f:
                msg = yaml.safe_load(f)
                msg['resolved_fields'] = self._resolve_fields_for_ics(msg['fields'])
                messages.append(msg)
        
        report += "## 1. Message Catalog\n\n"
        report += "| ID | Name | Group | Fields | Source | Direction | Latency | Payload Length (Max) |\n"
        report += "| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |\n"
        for msg in messages:
            total_len = msg['pv']['size'] + sum(f['length'] for f in msg['resolved_fields'])
            report += f"| {msg['id']} | {msg['name']} | {msg['group']} | {len(msg['resolved_fields'])} | {msg.get('source','-')} | {msg.get('direction','-')} | {msg.get('latency','-')} | {total_len} B |\n"
        
        report += "\n## 2. Detailed Bit Layouts\n\n"
        for msg in messages:
            report += f"### Message #{msg['id']}: {msg['name']}\n"
            report += f"**Group:** {msg['group']} | **Source:** {msg.get('source','-')} | **Direction:** {msg.get('direction','-')} | **Latency:** {msg.get('latency','-')}\n\n"
            report += "| Offset | PV Bit | Field Name | Type | Length | Encoding | Unit | M/O |\n"
            report += "| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |\n"
            current_offset = msg['pv']['size']
            report += f"| 0 | - | **Presence Vector** | {msg['pv']['type']} | {msg['pv']['size']} B | Bitmapped | - | M |\n"
            for f in msg['resolved_fields']:
                report += f"| {current_offset} | {f['pv_bit'] if f['pv_bit'] is not None else '-'} | {f['name']} | {f['type']} | {f['length']} B | {f['encoding']} | {f['unit']} | {f['mandatory']} |\n"
                current_offset += f['length']
            report += "\n"
            
        report += "## 3. Capability Profile Mapping\n\n"
        for filename in sorted(os.listdir(self.profiles_dir)):
            if not filename.endswith(".profile"): continue
            with open(os.path.join(self.profiles_dir, filename), 'r') as f:
                prof = yaml.safe_load(f)
                report += f"### Profile: {prof['name']} (LOI {prof['loi']})\n"
                report += f"**Mode:** {prof['mode']}\n"
                # Check for the tailored note in comments or metadata
                report += "**Included Groups:** " + ", ".join(prof.get('include_groups', [])) + "\n"
                if prof.get('optional_groups'):
                    report += "**Optional Groups:** " + ", ".join(prof.get('optional_groups', [])) + "\n"
                report += "**Supported Messages:**\n"
                for msg in messages:
                    if msg['group'] in prof.get('include_groups', []):
                        report += f"- #{msg['id']} {msg['name']} (Full Support)\n"
                    elif msg['group'] in prof.get('optional_groups', []):
                        report += f"- #{msg['id']} {msg['name']} (Optional / profile-dependent)\n"
                report += "\n"

        out_path = os.path.join(self.root, "docs/ICS_Report.md")
        os.makedirs(os.path.dirname(out_path), exist_ok=True)
        with open(out_path, 'w') as f: f.write(report)
        print(f"Generated: {out_path}")

if __name__ == "__main__":
    gen = ICSGenerator("/home/tayfurcnr/Desktop/STANAG/DLI")
    gen.generate_report()

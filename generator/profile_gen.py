import yaml
import os
import sys

class ProfileGenerator:
    def __init__(self, root):
        self.root = root
        self.messages_dir = os.path.join(root, "definitions/messages")
        self.profiles_dir = os.path.join(root, "definitions/profiles")
        self.output_dir = os.path.join(root, "idl/cpp/dli/generated/profiles")
        os.makedirs(self.output_dir, exist_ok=True)
        
        self.groups = {} # group_name -> set of msg_ids
        self.messages = {} # msg_id -> msg_name
        self._load_definitions()

    def _load_definitions(self):
        for filename in os.listdir(self.messages_dir):
            if not filename.endswith(".sdli"): continue
            with open(os.path.join(self.messages_dir, filename), 'r') as f:
                msg = yaml.safe_load(f)
                msg_id = msg['id']
                group = msg.get('group', 'Unknown')
                
                self.messages[msg_id] = msg['name']
                if group not in self.groups:
                    self.groups[group] = set()
                self.groups[group].add(msg_id)

    def generate(self):
        print(f"[Profiles] Generating C++ classes for {len(self.groups)} groups...")
        self._gen_profiles_hpp()
        print(f"[Profiles] Generated: {os.path.join(self.output_dir, 'Profiles.hpp')}")

    def _gen_profiles_hpp(self):
        hpp = []
        hpp.append("#pragma once")
        hpp.append("\n#include <dli/protocol/Profile.hpp>")
        hpp.append("#include <vector>")
        hpp.append("\nnamespace dli {\nnamespace generated {\n")
        hpp.append("/**\n * @brief Auto-generated Profiles based on AEP-84 definitions.\n */")
        hpp.append("class Profiles {")
        hpp.append("public:")

        for filename in sorted(os.listdir(self.profiles_dir)):
            if not filename.endswith(".profile"): continue
            with open(os.path.join(self.profiles_dir, filename), 'r') as f:
                prof = yaml.safe_load(f)
                p_name = prof['name']
                method_name = p_name.replace("_Profile", "").replace(" ", "_")
                
                hpp.append(f"    static Profile {method_name}() {{")
                hpp.append(f"        Profile p(\"{p_name}\", {prof['loi']});")
                
                # 1. Include Groups
                for group in prof.get('include_groups', []):
                    if group in self.groups:
                        for mid in sorted(self.groups[group]):
                            hpp.append(f"        p.allow({mid}); // {self.messages[mid]} ({group})")
                
                # 2. Include Specific Messages
                for mid in prof.get('include_messages', []):
                    hpp.append(f"        p.allow({mid}); // Manual include")

                # 3. Exclude Specific Messages
                for mid in prof.get('exclude_messages', []):
                    hpp.append(f"        p.deny({mid}); // Manual exclude")

                hpp.append("        return p;")
                hpp.append("    }\n")

        hpp.append("};")
        hpp.append("\n} // namespace generated")
        hpp.append("} // namespace dli")

        with open(os.path.join(self.output_dir, "Profiles.hpp"), 'w') as f:
            f.write("\n".join(hpp))

if __name__ == "__main__":
    root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    ProfileGenerator(root).generate()

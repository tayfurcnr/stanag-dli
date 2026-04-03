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

    def _validate_profile(self, prof, profile_path):
        if not isinstance(prof, dict):
            raise ValueError(f"{profile_path}: profile must be a mapping")
        for key in ("name", "loi"):
            if key not in prof:
                raise ValueError(f"{profile_path}: missing required key '{key}'")

        for key in ("include_groups", "optional_groups", "exclude_groups"):
            groups = prof.get(key, [])
            if not isinstance(groups, list):
                raise ValueError(f"{profile_path}: '{key}' must be a list")

        for key in ("include_messages", "exclude_messages"):
            msg_ids = prof.get(key, [])
            if not isinstance(msg_ids, list):
                raise ValueError(f"{profile_path}: '{key}' must be a list")
            unknown = sorted(mid for mid in set(msg_ids) if mid not in self.messages)
            if unknown:
                raise ValueError(f"{profile_path}: unknown message ids in '{key}': {', '.join(str(mid) for mid in unknown)}")

        include_groups = set(prof.get("include_groups", []))
        exclude_groups = set(prof.get("exclude_groups", []))
        conflicting_groups = sorted(include_groups & exclude_groups)
        if conflicting_groups:
            raise ValueError(f"{profile_path}: groups cannot be both included and excluded: {', '.join(conflicting_groups)}")

        include_messages = set(prof.get("include_messages", []))
        exclude_messages = set(prof.get("exclude_messages", []))
        conflicting_messages = sorted(include_messages & exclude_messages)
        if conflicting_messages:
            raise ValueError(
                f"{profile_path}: message ids cannot be both included and excluded: {', '.join(str(mid) for mid in conflicting_messages)}"
            )

    def _load_profile(self, filename):
        profile_path = os.path.join(self.profiles_dir, filename)
        with open(profile_path, 'r') as f:
            prof = yaml.safe_load(f)
        self._validate_profile(prof, profile_path)
        return prof

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
            prof = self._load_profile(filename)
            p_name = prof['name']
            method_name = p_name.replace("_Profile", "").replace(" ", "_")
            
            hpp.append(f"    static Profile {method_name}() {{")
            hpp.append(f"        Profile p(\"{p_name}\", {prof['loi']});")
            
            # 1. Include Groups
            for group in prof.get('include_groups', []):
                if group not in self.groups:
                    continue
                for mid in sorted(self.groups[group]):
                    hpp.append(f"        p.allow({mid}); // {self.messages[mid]} ({group})")

            # 2. Include Specific Messages
            for mid in prof.get('include_messages', []):
                hpp.append(f"        p.allow({mid}); // Manual include")

            # 3. Exclude Groups
            for group in prof.get('exclude_groups', []):
                if group not in self.groups:
                    continue
                for mid in sorted(self.groups[group]):
                    hpp.append(f"        p.deny({mid}); // {self.messages[mid]} ({group})")

            # 4. Exclude Specific Messages
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

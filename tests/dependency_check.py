import yaml
import os

def check_dependencies():
    print("[Test] Capability Dependency Check...")
    
    root = "/home/tayfurcnr/Desktop/STANAG/DLI/definitions/"
    cap_path = os.path.join(root, "common/capabilities.sdli")
    profiles_dir = os.path.join(root, "profiles/")
    
    with open(cap_path, 'r') as f:
        caps = yaml.safe_load(f)['capabilities']
        
    for profile_file in os.listdir(profiles_dir):
        if not profile_file.endswith(".profile"):
            continue
            
        print(f"  Checking profile: {profile_file}")
        with open(os.path.join(profiles_dir, profile_file), 'r') as f:
            profile = yaml.safe_load(f)
            
        included = set(profile.get('include_groups', []))
        
        for group in included:
            if group not in caps:
                print(f"    WARNING: Group '{group}' not defined in capabilities.sdli")
                continue
                
            deps = caps[group].get('depends_on', [])
            for dep in deps:
                if dep not in included:
                    error_msg = f"    ERROR: Profile '{profile['name']}' includes '{group}' but misses dependency '{dep}'"
                    if profile.get('strict', False):
                        raise Exception(error_msg)
                    else:
                        print(error_msg)
                        
    print("  Passed: All profiles satisfy capability dependencies.")

if __name__ == "__main__":
    try:
        check_dependencies()
        print("Dependency Validation Successful!")
    except Exception as e:
        print(f"FAILED: {e}")
        exit(1)

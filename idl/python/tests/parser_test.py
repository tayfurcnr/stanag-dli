import yaml
import os

def test_dsl_parsing():
    print("[Test] DSL Parsing & GlobalPos Resolution...")
    
    repo_root = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
    root = os.path.join(repo_root, "definitions", "common")
    types_path = os.path.join(root, "types.sdli")
    policies_path = os.path.join(root, "policies.sdli")
    
    with open(types_path, 'r') as f:
        types = yaml.safe_load(f)
    
    with open(policies_path, 'r') as f:
        policies = yaml.safe_load(f)
        
    assert 'types' in types
    assert 'GlobalPos' in types['types']
    
    global_pos = types['types']['GlobalPos']
    assert global_pos['composition'] == 'flattened'
    
    # Simulate flattening resolution
    fields = global_pos['fields']
    field_names = [f['name'] for f in fields]
    assert 'latitude' in field_names
    assert 'longitude' in field_names
    assert 'altitude' in field_names
    
    print("  Passed: DSL files are valid YAML and GlobalPos structure is correct.")

if __name__ == "__main__":
    try:
        test_dsl_parsing()
        print("All Parser Smoke Tests Passed!")
    except Exception as e:
        print(f"FAILED: {e}")
        exit(1)

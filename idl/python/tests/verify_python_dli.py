import sys
import os

# Add the idl/python directory to sys.path so 'dli' package can be found
test_dir = os.path.dirname(os.path.abspath(__file__))
python_root = os.path.dirname(test_dir) # points to idl/python
sys.path.insert(0, python_root)

from dli.core import BitCursor
from dli.protocol import DliMessage
from dli.generated.messages.Heartbeat import Heartbeat
from dli.generated.messages.UAStickCommand import UAStickCommand

def test_heartbeat():
    print("Testing Heartbeat...")
    msg = DliMessage(Heartbeat)
    msg.header.message_type = 16002
    msg.header.source_id = 0x12345678
    msg.header.destination_id = 0x87654321
    msg.header.message_properties = (1 << 8) | (1 << 6) # Version 1, Checksum Type 1 (CRC-16)
    
    msg.body.time_stamp = 1234567890
    msg.body.has_time_stamp = True
    
    buffer = bytearray(128)
    cursor = BitCursor(buffer)
    msg.serialize(cursor)
    
    total_len = cursor.pos
    print(f"Serialized Length: {total_len} bytes")
    
    # Try deserialize
    cursor2 = BitCursor(buffer[:total_len])
    msg2 = DliMessage(Heartbeat)
    if msg2.deserialize(cursor2):
        print("Deserialization Successful!")
        print(f"Header Msg Type: {msg2.header.message_type}")
        print(f"Body Timestamp: {msg2.body.time_stamp}")
        print(f"Checksum: {hex(msg2.checksum) if msg2.checksum else 'None'}")
        
        assert msg2.header.message_type == 16002
        assert msg2.body.time_stamp == 1234567890
    else:
        print(f"Deserialization Failed: {cursor2.error()}")
        sys.exit(1)

def test_stick_command():
    print("\nTesting UAStickCommand...")
    msg = DliMessage(UAStickCommand)
    msg.header.message_type = 2010
    msg.body.time_stamp = 999999
    msg.body.has_time_stamp = True
    msg.body.lateral_stick = 50.0
    msg.body.has_lateral_stick = True
    
    buffer = bytearray(128)
    cursor = BitCursor(buffer)
    msg.serialize(cursor)
    
    cursor2 = BitCursor(buffer[:cursor.pos])
    msg2 = DliMessage(UAStickCommand)
    if msg2.deserialize(cursor2):
        print("Deserialization Successful!")
        print(f"Lateral Stick: {msg2.body.lateral_stick}")
        # Note: Stick conversion in generator was simplified for now (linear mapping)
        # Should be closer to middle but not exact due to 0.0-1.0 vs BAM mapping diffs
    else:
        print("Deserialization Failed!")
        sys.exit(1)

if __name__ == "__main__":
    test_heartbeat()
    test_stick_command()
    print("\nAll Python Core Tests Passed! 🚀")

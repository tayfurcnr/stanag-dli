from dli.core.bit_cursor import BitCursor
from dli.utils import BAM, Scaled
import math

class EngineCommand:
    def __init__(self):
        # Presence Vector
        self.pv = 0
        
        self.time_stamp = 0
        self.has_time_stamp = False
        
        self.engine_number = 0
        self.has_engine_number = False
        
        self.engine_command = 0
        self.has_engine_command = False
        
        self.reverse_thrust_power = 0
        self.has_reverse_thrust_power = False
        
        self.reverse_thrust = 0
        self.has_reverse_thrust = False
        
        self.ignition_switch_power = 0
        self.has_ignition_switch_power = False
        
        self.ignition_switch_activation = 0
        self.has_ignition_switch_activation = False
        
        self.activity_id = 0
        self.has_activity_id = False
        

    def serialize(self, cursor: BitCursor):
        # 1. Prepare PV
        self.pv = 0
        
        if self.has_time_stamp:
            self.pv |= (1 << 0)
        
        if self.has_engine_number:
            self.pv |= (1 << 1)
        
        if self.has_engine_command:
            self.pv |= (1 << 2)
        
        if self.has_reverse_thrust_power:
            self.pv |= (1 << 3)
        
        if self.has_reverse_thrust:
            self.pv |= (1 << 4)
        
        if self.has_ignition_switch_power:
            self.pv |= (1 << 5)
        
        if self.has_ignition_switch_activation:
            self.pv |= (1 << 6)
        
        if self.has_activity_id:
            self.pv |= (1 << 7)
        

        # 2. Write PV
        
        cursor.write_uint8(self.pv)
        
        
        
        
        

        # 3. Write Fields
        
        if self.has_time_stamp:
            cursor.write_uint40(self.time_stamp)
        
        if self.has_engine_number:
            cursor.write_uint8(self.engine_number)
        
        if self.has_engine_command:
            cursor.write_uint8(self.engine_command)
        
        if self.has_reverse_thrust_power:
            cursor.write_uint8(self.reverse_thrust_power)
        
        if self.has_reverse_thrust:
            cursor.write_uint8(self.reverse_thrust)
        
        if self.has_ignition_switch_power:
            cursor.write_uint8(self.ignition_switch_power)
        
        if self.has_ignition_switch_activation:
            cursor.write_uint8(self.ignition_switch_activation)
        
        if self.has_activity_id:
            cursor.write_uint24(self.activity_id)
        

    def deserialize(self, cursor: BitCursor):
        # 1. Read PV
        
        self.pv = cursor.read_uint8()
        
        
        
        
        

        # 2. Read Fields
        
        if self.pv & (1 << 0):
            self.has_time_stamp = True
            self.time_stamp = cursor.read_uint40()
        else:
            self.has_time_stamp = False
        
        if self.pv & (1 << 1):
            self.has_engine_number = True
            self.engine_number = cursor.read_uint8()
        else:
            self.has_engine_number = False
        
        if self.pv & (1 << 2):
            self.has_engine_command = True
            self.engine_command = cursor.read_uint8()
        else:
            self.has_engine_command = False
        
        if self.pv & (1 << 3):
            self.has_reverse_thrust_power = True
            self.reverse_thrust_power = cursor.read_uint8()
        else:
            self.has_reverse_thrust_power = False
        
        if self.pv & (1 << 4):
            self.has_reverse_thrust = True
            self.reverse_thrust = cursor.read_uint8()
        else:
            self.has_reverse_thrust = False
        
        if self.pv & (1 << 5):
            self.has_ignition_switch_power = True
            self.ignition_switch_power = cursor.read_uint8()
        else:
            self.has_ignition_switch_power = False
        
        if self.pv & (1 << 6):
            self.has_ignition_switch_activation = True
            self.ignition_switch_activation = cursor.read_uint8()
        else:
            self.has_ignition_switch_activation = False
        
        if self.pv & (1 << 7):
            self.has_activity_id = True
            self.activity_id = cursor.read_uint24()
        else:
            self.has_activity_id = False
        

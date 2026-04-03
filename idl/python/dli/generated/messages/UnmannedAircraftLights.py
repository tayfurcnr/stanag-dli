from dli.core.bit_cursor import BitCursor
from dli.utils import BAM, Scaled
import math

class UnmannedAircraftLights:
    def __init__(self):
        # Presence Vector
        self.pv = 0
        
        self.time_stamp = 0
        self.has_time_stamp = False
        
        self.set_lights = 0
        self.has_set_lights = False
        
        self.activity_id = 0
        self.has_activity_id = False
        

    def serialize(self, cursor: BitCursor):
        # 1. Prepare PV
        self.pv = 0
        
        if self.has_time_stamp:
            self.pv |= (1 << 0)
        
        if self.has_set_lights:
            self.pv |= (1 << 1)
        
        if self.has_activity_id:
            self.pv |= (1 << 2)
        

        # 2. Write PV
        
        cursor.write_uint8(self.pv)
        
        
        
        
        

        # 3. Write Fields
        
        if self.has_time_stamp:
            cursor.write_uint40(self.time_stamp)
        
        if self.has_set_lights:
            cursor.write_uint16(self.set_lights)
        
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
            self.has_set_lights = True
            self.set_lights = cursor.read_uint16()
        else:
            self.has_set_lights = False
        
        if self.pv & (1 << 2):
            self.has_activity_id = True
            self.activity_id = cursor.read_uint24()
        else:
            self.has_activity_id = False
        

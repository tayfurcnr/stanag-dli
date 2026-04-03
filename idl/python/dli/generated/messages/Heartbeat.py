from dli.core.bit_cursor import BitCursor
from dli.utils import BAM, Scaled
import math

class Heartbeat:
    def __init__(self):
        # Presence Vector
        self.pv = 0
        
        self.time_stamp = 0
        self.has_time_stamp = False
        

    def serialize(self, cursor: BitCursor):
        # 1. Prepare PV
        self.pv = 0
        
        if self.has_time_stamp:
            self.pv |= (1 << 0)
        

        # 2. Write PV
        
        cursor.write_uint8(self.pv)
        
        
        
        
        

        # 3. Write Fields
        
        if self.has_time_stamp:
            cursor.write_uint40(self.time_stamp)
        

    def deserialize(self, cursor: BitCursor):
        # 1. Read PV
        
        self.pv = cursor.read_uint8()
        
        
        
        
        

        # 2. Read Fields
        
        if self.pv & (1 << 0):
            self.has_time_stamp = True
            self.time_stamp = cursor.read_uint40()
        else:
            self.has_time_stamp = False
        

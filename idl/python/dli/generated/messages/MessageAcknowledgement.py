from dli.core.bit_cursor import BitCursor
from dli.utils import BAM, Scaled
import math

class MessageAcknowledgement:
    def __init__(self):
        # Presence Vector
        self.pv = 0
        
        self.time_stamp = 0
        self.has_time_stamp = False
        
        self.original_message_time_stamp = 0
        self.has_original_message_time_stamp = False
        
        self.original_message_type = 0
        self.has_original_message_type = False
        
        self.acknowledgement_type = 0
        self.has_acknowledgement_type = False
        

    def serialize(self, cursor: BitCursor):
        # 1. Prepare PV
        self.pv = 0
        
        if self.has_time_stamp:
            self.pv |= (1 << 0)
        
        if self.has_original_message_time_stamp:
            self.pv |= (1 << 1)
        
        if self.has_original_message_type:
            self.pv |= (1 << 2)
        
        if self.has_acknowledgement_type:
            self.pv |= (1 << 3)
        

        # 2. Write PV
        
        cursor.write_uint8(self.pv)
        
        
        
        
        

        # 3. Write Fields
        
        if self.has_time_stamp:
            cursor.write_uint40(self.time_stamp)
        
        if self.has_original_message_time_stamp:
            cursor.write_uint40(self.original_message_time_stamp)
        
        if self.has_original_message_type:
            cursor.write_uint16(self.original_message_type)
        
        if self.has_acknowledgement_type:
            cursor.write_uint8(self.acknowledgement_type)
        

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
            self.has_original_message_time_stamp = True
            self.original_message_time_stamp = cursor.read_uint40()
        else:
            self.has_original_message_time_stamp = False
        
        if self.pv & (1 << 2):
            self.has_original_message_type = True
            self.original_message_type = cursor.read_uint16()
        else:
            self.has_original_message_type = False
        
        if self.pv & (1 << 3):
            self.has_acknowledgement_type = True
            self.acknowledgement_type = cursor.read_uint8()
        else:
            self.has_acknowledgement_type = False
        

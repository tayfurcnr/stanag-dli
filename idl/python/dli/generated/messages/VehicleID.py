from dli.core.bit_cursor import BitCursor
from dli.utils import BAM, Scaled
import math

class VehicleID:
    def __init__(self):
        # Presence Vector
        self.pv = 0
        
        self.time_stamp = 0
        self.has_time_stamp = False
        
        self.vsm_id = 0
        self.has_vsm_id = False
        
        self.vehicle_id_update = 0
        self.has_vehicle_id_update = False
        
        self.vehicle_type = 0
        self.has_vehicle_type = False
        
        self.vehicle_subtype = 0
        self.has_vehicle_subtype = False
        
        self.owning_id = 0
        self.has_owning_id = False
        
        self.tail_number = bytearray(16)
        self.has_tail_number = False
        
        self.mission_id = bytearray(20)
        self.has_mission_id = False
        
        self.atc_call_sign = bytearray(32)
        self.has_atc_call_sign = False
        
        self.configuration_checksum = 0
        self.has_configuration_checksum = False
        

    def serialize(self, cursor: BitCursor):
        # 1. Prepare PV
        self.pv = 0
        
        if self.has_time_stamp:
            self.pv |= (1 << 0)
        
        if self.has_vsm_id:
            self.pv |= (1 << 1)
        
        if self.has_vehicle_id_update:
            self.pv |= (1 << 2)
        
        if self.has_vehicle_type:
            self.pv |= (1 << 3)
        
        if self.has_vehicle_subtype:
            self.pv |= (1 << 4)
        
        if self.has_owning_id:
            self.pv |= (1 << 5)
        
        if self.has_tail_number:
            self.pv |= (1 << 6)
        
        if self.has_mission_id:
            self.pv |= (1 << 7)
        
        if self.has_atc_call_sign:
            self.pv |= (1 << 8)
        
        if self.has_configuration_checksum:
            self.pv |= (1 << 9)
        

        # 2. Write PV
        
        
        cursor.write_uint16(self.pv)
        
        
        
        

        # 3. Write Fields
        
        if self.has_time_stamp:
            cursor.write_uint40(self.time_stamp)
        
        if self.has_vsm_id:
            cursor.write_uint32(self.vsm_id)
        
        if self.has_vehicle_id_update:
            cursor.write_uint32(self.vehicle_id_update)
        
        if self.has_vehicle_type:
            cursor.write_uint16(self.vehicle_type)
        
        if self.has_vehicle_subtype:
            cursor.write_uint16(self.vehicle_subtype)
        
        if self.has_owning_id:
            cursor.write_uint8(self.owning_id)
        
        if self.has_tail_number:
            for _byte in self.tail_number: cursor.write_uint8(_byte)
        
        if self.has_mission_id:
            for _byte in self.mission_id: cursor.write_uint8(_byte)
        
        if self.has_atc_call_sign:
            for _byte in self.atc_call_sign: cursor.write_uint8(_byte)
        
        if self.has_configuration_checksum:
            cursor.write_uint16(self.configuration_checksum)
        

    def deserialize(self, cursor: BitCursor):
        # 1. Read PV
        
        
        self.pv = cursor.read_uint16()
        
        
        
        

        # 2. Read Fields
        
        if self.pv & (1 << 0):
            self.has_time_stamp = True
            self.time_stamp = cursor.read_uint40()
        else:
            self.has_time_stamp = False
        
        if self.pv & (1 << 1):
            self.has_vsm_id = True
            self.vsm_id = cursor.read_uint32()
        else:
            self.has_vsm_id = False
        
        if self.pv & (1 << 2):
            self.has_vehicle_id_update = True
            self.vehicle_id_update = cursor.read_uint32()
        else:
            self.has_vehicle_id_update = False
        
        if self.pv & (1 << 3):
            self.has_vehicle_type = True
            self.vehicle_type = cursor.read_uint16()
        else:
            self.has_vehicle_type = False
        
        if self.pv & (1 << 4):
            self.has_vehicle_subtype = True
            self.vehicle_subtype = cursor.read_uint16()
        else:
            self.has_vehicle_subtype = False
        
        if self.pv & (1 << 5):
            self.has_owning_id = True
            self.owning_id = cursor.read_uint8()
        else:
            self.has_owning_id = False
        
        if self.pv & (1 << 6):
            self.has_tail_number = True
            self.tail_number = bytearray(cursor.read_uint8() for _ in range(16))
        else:
            self.has_tail_number = False
        
        if self.pv & (1 << 7):
            self.has_mission_id = True
            self.mission_id = bytearray(cursor.read_uint8() for _ in range(20))
        else:
            self.has_mission_id = False
        
        if self.pv & (1 << 8):
            self.has_atc_call_sign = True
            self.atc_call_sign = bytearray(cursor.read_uint8() for _ in range(32))
        else:
            self.has_atc_call_sign = False
        
        if self.pv & (1 << 9):
            self.has_configuration_checksum = True
            self.configuration_checksum = cursor.read_uint16()
        else:
            self.has_configuration_checksum = False
        

from dli.core.bit_cursor import BitCursor
from dli.utils import BAM, Scaled
import math

class LoiterConfigurationReport:
    def __init__(self):
        # Presence Vector
        self.pv = 0
        
        self.time_stamp = 0
        self.has_time_stamp = False
        
        self.loiter_type = 0
        self.has_loiter_type = False
        
        self.loiter_radius = 0.0
        self.has_loiter_radius = False
        
        self.loiter_length = 0.0
        self.has_loiter_length = False
        
        self.loiter_length_units = 0
        self.has_loiter_length_units = False
        
        self.loiter_bearing = 0.0
        self.has_loiter_bearing = False
        
        self.loiter_direction = 0
        self.has_loiter_direction = False
        
        self.loiter_altitude = 0.0
        self.has_loiter_altitude = False
        
        self.altitude_type = 0
        self.has_altitude_type = False
        
        self.loiter_speed = 0.0
        self.has_loiter_speed = False
        
        self.speed_type = 0
        self.has_speed_type = False
        
        self.flying_behaviour = 0
        self.has_flying_behaviour = False
        
        self.loiter_duration = 0
        self.has_loiter_duration = False
        
        self.loiter_duration_units = 0
        self.has_loiter_duration_units = False
        

    def serialize(self, cursor: BitCursor):
        # 1. Prepare PV
        self.pv = 0
        
        if self.has_time_stamp:
            self.pv |= (1 << 0)
        
        if self.has_loiter_type:
            self.pv |= (1 << 1)
        
        if self.has_loiter_radius:
            self.pv |= (1 << 2)
        
        if self.has_loiter_length:
            self.pv |= (1 << 3)
        
        if self.has_loiter_length_units:
            self.pv |= (1 << 4)
        
        if self.has_loiter_bearing:
            self.pv |= (1 << 5)
        
        if self.has_loiter_direction:
            self.pv |= (1 << 6)
        
        if self.has_loiter_altitude:
            self.pv |= (1 << 7)
        
        if self.has_altitude_type:
            self.pv |= (1 << 8)
        
        if self.has_loiter_speed:
            self.pv |= (1 << 9)
        
        if self.has_speed_type:
            self.pv |= (1 << 10)
        
        if self.has_flying_behaviour:
            self.pv |= (1 << 11)
        
        if self.has_loiter_duration:
            self.pv |= (1 << 12)
        
        if self.has_loiter_duration_units:
            self.pv |= (1 << 13)
        

        # 2. Write PV
        
        
        cursor.write_uint16(self.pv)
        
        
        
        

        # 3. Write Fields
        
        if self.has_time_stamp:
            cursor.write_uint40(self.time_stamp)
        
        if self.has_loiter_type:
            cursor.write_uint8(self.loiter_type)
        
        if self.has_loiter_radius:
            cursor.write_uint16(Scaled.to_scaled(self.loiter_radius, 0.0, 1.5))
        
        if self.has_loiter_length:
            cursor.write_uint16(Scaled.to_scaled(self.loiter_length, 0.0, 1.5))
        
        if self.has_loiter_length_units:
            cursor.write_uint8(self.loiter_length_units)
        
        if self.has_loiter_bearing:
            cursor.write_uint16(BAM.to_bam16(self.loiter_bearing))
        
        if self.has_loiter_direction:
            cursor.write_uint8(self.loiter_direction)
        
        if self.has_loiter_altitude:
            cursor.write_int24(Scaled.to_scaled(self.loiter_altitude, 0.0, 0.02))
        
        if self.has_altitude_type:
            cursor.write_uint8(self.altitude_type)
        
        if self.has_loiter_speed:
            cursor.write_uint16(Scaled.to_scaled(self.loiter_speed, 0.0, 0.5))
        
        if self.has_speed_type:
            cursor.write_uint8(self.speed_type)
        
        if self.has_flying_behaviour:
            cursor.write_uint8(self.flying_behaviour)
        
        if self.has_loiter_duration:
            cursor.write_uint16(self.loiter_duration)
        
        if self.has_loiter_duration_units:
            cursor.write_uint8(self.loiter_duration_units)
        

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
            self.has_loiter_type = True
            self.loiter_type = cursor.read_uint8()
        else:
            self.has_loiter_type = False
        
        if self.pv & (1 << 2):
            self.has_loiter_radius = True
            self.loiter_radius = Scaled.from_scaled(cursor.read_uint16(), 0.0, 1.5)
        else:
            self.has_loiter_radius = False
        
        if self.pv & (1 << 3):
            self.has_loiter_length = True
            self.loiter_length = Scaled.from_scaled(cursor.read_uint16(), 0.0, 1.5)
        else:
            self.has_loiter_length = False
        
        if self.pv & (1 << 4):
            self.has_loiter_length_units = True
            self.loiter_length_units = cursor.read_uint8()
        else:
            self.has_loiter_length_units = False
        
        if self.pv & (1 << 5):
            self.has_loiter_bearing = True
            self.loiter_bearing = BAM.from_bam16(cursor.read_uint16())
        else:
            self.has_loiter_bearing = False
        
        if self.pv & (1 << 6):
            self.has_loiter_direction = True
            self.loiter_direction = cursor.read_uint8()
        else:
            self.has_loiter_direction = False
        
        if self.pv & (1 << 7):
            self.has_loiter_altitude = True
            self.loiter_altitude = Scaled.from_scaled(cursor.read_int24(), 0.0, 0.02)
        else:
            self.has_loiter_altitude = False
        
        if self.pv & (1 << 8):
            self.has_altitude_type = True
            self.altitude_type = cursor.read_uint8()
        else:
            self.has_altitude_type = False
        
        if self.pv & (1 << 9):
            self.has_loiter_speed = True
            self.loiter_speed = Scaled.from_scaled(cursor.read_uint16(), 0.0, 0.5)
        else:
            self.has_loiter_speed = False
        
        if self.pv & (1 << 10):
            self.has_speed_type = True
            self.speed_type = cursor.read_uint8()
        else:
            self.has_speed_type = False
        
        if self.pv & (1 << 11):
            self.has_flying_behaviour = True
            self.flying_behaviour = cursor.read_uint8()
        else:
            self.has_flying_behaviour = False
        
        if self.pv & (1 << 12):
            self.has_loiter_duration = True
            self.loiter_duration = cursor.read_uint16()
        else:
            self.has_loiter_duration = False
        
        if self.pv & (1 << 13):
            self.has_loiter_duration_units = True
            self.loiter_duration_units = cursor.read_uint8()
        else:
            self.has_loiter_duration_units = False
        

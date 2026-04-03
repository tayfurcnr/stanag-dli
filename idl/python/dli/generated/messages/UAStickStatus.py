from dli.core.bit_cursor import BitCursor
from dli.utils import BAM, Scaled
import math

class UAStickStatus:
    def __init__(self):
        # Presence Vector
        self.pv = 0
        
        self.time_stamp = 0
        self.has_time_stamp = False
        
        self.lateral_stick = 0
        self.has_lateral_stick = False
        
        self.longitudinal_stick = 0
        self.has_longitudinal_stick = False
        
        self.rotational_stick_rudder = 0
        self.has_rotational_stick_rudder = False
        
        self.throttle_stick___engine_1 = 0
        self.has_throttle_stick___engine_1 = False
        
        self.pitch_stick___engine_1 = 0
        self.has_pitch_stick___engine_1 = False
        
        self.throttle_stick___engine_2 = 0
        self.has_throttle_stick___engine_2 = False
        
        self.pitch_stick___engine_2 = 0
        self.has_pitch_stick___engine_2 = False
        
        self.throttle_stick___engine_3 = 0
        self.has_throttle_stick___engine_3 = False
        
        self.pitch_stick___engine_3 = 0
        self.has_pitch_stick___engine_3 = False
        
        self.throttle_stick___engine_4 = 0
        self.has_throttle_stick___engine_4 = False
        
        self.pitch_stick___engine_4 = 0
        self.has_pitch_stick___engine_4 = False
        
        self.taxi_stick = 0
        self.has_taxi_stick = False
        

    def serialize(self, cursor: BitCursor):
        # 1. Prepare PV
        self.pv = 0
        
        if self.has_time_stamp:
            self.pv |= (1 << 0)
        
        if self.has_lateral_stick:
            self.pv |= (1 << 1)
        
        if self.has_longitudinal_stick:
            self.pv |= (1 << 2)
        
        if self.has_rotational_stick_rudder:
            self.pv |= (1 << 3)
        
        if self.has_throttle_stick___engine_1:
            self.pv |= (1 << 4)
        
        if self.has_pitch_stick___engine_1:
            self.pv |= (1 << 5)
        
        if self.has_throttle_stick___engine_2:
            self.pv |= (1 << 6)
        
        if self.has_pitch_stick___engine_2:
            self.pv |= (1 << 7)
        
        if self.has_throttle_stick___engine_3:
            self.pv |= (1 << 8)
        
        if self.has_pitch_stick___engine_3:
            self.pv |= (1 << 9)
        
        if self.has_throttle_stick___engine_4:
            self.pv |= (1 << 10)
        
        if self.has_pitch_stick___engine_4:
            self.pv |= (1 << 11)
        
        if self.has_taxi_stick:
            self.pv |= (1 << 12)
        

        # 2. Write PV
        
        
        cursor.write_uint16(self.pv)
        
        
        
        

        # 3. Write Fields
        
        if self.has_time_stamp:
            cursor.write_uint40(self.time_stamp)
        
        if self.has_lateral_stick:
            cursor.write_int8(self.lateral_stick)
        
        if self.has_longitudinal_stick:
            cursor.write_int8(self.longitudinal_stick)
        
        if self.has_rotational_stick_rudder:
            cursor.write_int8(self.rotational_stick_rudder)
        
        if self.has_throttle_stick___engine_1:
            cursor.write_uint8(self.throttle_stick___engine_1)
        
        if self.has_pitch_stick___engine_1:
            cursor.write_int8(self.pitch_stick___engine_1)
        
        if self.has_throttle_stick___engine_2:
            cursor.write_uint8(self.throttle_stick___engine_2)
        
        if self.has_pitch_stick___engine_2:
            cursor.write_int8(self.pitch_stick___engine_2)
        
        if self.has_throttle_stick___engine_3:
            cursor.write_uint8(self.throttle_stick___engine_3)
        
        if self.has_pitch_stick___engine_3:
            cursor.write_int8(self.pitch_stick___engine_3)
        
        if self.has_throttle_stick___engine_4:
            cursor.write_uint8(self.throttle_stick___engine_4)
        
        if self.has_pitch_stick___engine_4:
            cursor.write_int8(self.pitch_stick___engine_4)
        
        if self.has_taxi_stick:
            cursor.write_int8(self.taxi_stick)
        

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
            self.has_lateral_stick = True
            self.lateral_stick = cursor.read_int8()
        else:
            self.has_lateral_stick = False
        
        if self.pv & (1 << 2):
            self.has_longitudinal_stick = True
            self.longitudinal_stick = cursor.read_int8()
        else:
            self.has_longitudinal_stick = False
        
        if self.pv & (1 << 3):
            self.has_rotational_stick_rudder = True
            self.rotational_stick_rudder = cursor.read_int8()
        else:
            self.has_rotational_stick_rudder = False
        
        if self.pv & (1 << 4):
            self.has_throttle_stick___engine_1 = True
            self.throttle_stick___engine_1 = cursor.read_uint8()
        else:
            self.has_throttle_stick___engine_1 = False
        
        if self.pv & (1 << 5):
            self.has_pitch_stick___engine_1 = True
            self.pitch_stick___engine_1 = cursor.read_int8()
        else:
            self.has_pitch_stick___engine_1 = False
        
        if self.pv & (1 << 6):
            self.has_throttle_stick___engine_2 = True
            self.throttle_stick___engine_2 = cursor.read_uint8()
        else:
            self.has_throttle_stick___engine_2 = False
        
        if self.pv & (1 << 7):
            self.has_pitch_stick___engine_2 = True
            self.pitch_stick___engine_2 = cursor.read_int8()
        else:
            self.has_pitch_stick___engine_2 = False
        
        if self.pv & (1 << 8):
            self.has_throttle_stick___engine_3 = True
            self.throttle_stick___engine_3 = cursor.read_uint8()
        else:
            self.has_throttle_stick___engine_3 = False
        
        if self.pv & (1 << 9):
            self.has_pitch_stick___engine_3 = True
            self.pitch_stick___engine_3 = cursor.read_int8()
        else:
            self.has_pitch_stick___engine_3 = False
        
        if self.pv & (1 << 10):
            self.has_throttle_stick___engine_4 = True
            self.throttle_stick___engine_4 = cursor.read_uint8()
        else:
            self.has_throttle_stick___engine_4 = False
        
        if self.pv & (1 << 11):
            self.has_pitch_stick___engine_4 = True
            self.pitch_stick___engine_4 = cursor.read_int8()
        else:
            self.has_pitch_stick___engine_4 = False
        
        if self.pv & (1 << 12):
            self.has_taxi_stick = True
            self.taxi_stick = cursor.read_int8()
        else:
            self.has_taxi_stick = False
        

from dli.core.bit_cursor import BitCursor
from dli.utils import BAM, Scaled
import math

class InertialStates:
    def __init__(self):
        # Presence Vector
        self.pv = 0
        
        self.time_stamp = 0
        self.has_time_stamp = False
        
        self.latitude = 0.0
        self.has_latitude = False
        
        self.longitude = 0.0
        self.has_longitude = False
        
        self.altitude = 0.0
        self.has_altitude = False
        
        self.altitude_type = 0
        self.has_altitude_type = False
        
        self.u_speed = 0.0
        self.has_u_speed = False
        
        self.v_speed = 0.0
        self.has_v_speed = False
        
        self.w_speed = 0.0
        self.has_w_speed = False
        
        self.u_accel = 0.0
        self.has_u_accel = False
        
        self.v_accel = 0.0
        self.has_v_accel = False
        
        self.w_accel = 0.0
        self.has_w_accel = False
        
        self.roll = 0.0
        self.has_roll = False
        
        self.pitch = 0.0
        self.has_pitch = False
        
        self.heading = 0.0
        self.has_heading = False
        
        self.roll_rate = 0.0
        self.has_roll_rate = False
        
        self.pitch_rate = 0.0
        self.has_pitch_rate = False
        
        self.turn_rate = 0.0
        self.has_turn_rate = False
        
        self.magnetic_variation = 0.0
        self.has_magnetic_variation = False
        

    def serialize(self, cursor: BitCursor):
        # 1. Prepare PV
        self.pv = 0
        
        if self.has_time_stamp:
            self.pv |= (1 << 0)
        
        if self.has_latitude:
            self.pv |= (1 << 1)
        
        if self.has_longitude:
            self.pv |= (1 << 2)
        
        if self.has_altitude:
            self.pv |= (1 << 3)
        
        if self.has_altitude_type:
            self.pv |= (1 << 4)
        
        if self.has_u_speed:
            self.pv |= (1 << 5)
        
        if self.has_v_speed:
            self.pv |= (1 << 6)
        
        if self.has_w_speed:
            self.pv |= (1 << 7)
        
        if self.has_u_accel:
            self.pv |= (1 << 8)
        
        if self.has_v_accel:
            self.pv |= (1 << 9)
        
        if self.has_w_accel:
            self.pv |= (1 << 10)
        
        if self.has_roll:
            self.pv |= (1 << 11)
        
        if self.has_pitch:
            self.pv |= (1 << 12)
        
        if self.has_heading:
            self.pv |= (1 << 13)
        
        if self.has_roll_rate:
            self.pv |= (1 << 14)
        
        if self.has_pitch_rate:
            self.pv |= (1 << 15)
        
        if self.has_turn_rate:
            self.pv |= (1 << 16)
        
        if self.has_magnetic_variation:
            self.pv |= (1 << 17)
        

        # 2. Write PV
        
        
        
        cursor.write_uint24(self.pv)
        
        
        

        # 3. Write Fields
        
        if self.has_time_stamp:
            cursor.write_uint40(self.time_stamp)
        
        if self.has_latitude:
            cursor.write_uint32(BAM.to_bam32(self.latitude))
        
        if self.has_longitude:
            cursor.write_uint32(BAM.to_bam32(self.longitude))
        
        if self.has_altitude:
            cursor.write_int24(Scaled.to_scaled(self.altitude, 0.0, 0.02))
        
        if self.has_altitude_type:
            cursor.write_uint8(self.altitude_type)
        
        if self.has_u_speed:
            cursor.write_int16(Scaled.to_scaled(self.u_speed, 0.0, 0.05))
        
        if self.has_v_speed:
            cursor.write_int16(Scaled.to_scaled(self.v_speed, 0.0, 0.05))
        
        if self.has_w_speed:
            cursor.write_int16(Scaled.to_scaled(self.w_speed, 0.0, 0.05))
        
        if self.has_u_accel:
            cursor.write_int16(Scaled.to_scaled(self.u_accel, 0.0, 0.005))
        
        if self.has_v_accel:
            cursor.write_int16(Scaled.to_scaled(self.v_accel, 0.0, 0.005))
        
        if self.has_w_accel:
            cursor.write_int16(Scaled.to_scaled(self.w_accel, 0.0, 0.005))
        
        if self.has_roll:
            cursor.write_uint16(BAM.to_bam16(self.roll))
        
        if self.has_pitch:
            cursor.write_uint16(BAM.to_bam16(self.pitch))
        
        if self.has_heading:
            cursor.write_uint16(BAM.to_bam16(self.heading))
        
        if self.has_roll_rate:
            cursor.write_int16(Scaled.to_scaled(self.roll_rate, 0.0, 0.005))
        
        if self.has_pitch_rate:
            cursor.write_int16(Scaled.to_scaled(self.pitch_rate, 0.0, 0.005))
        
        if self.has_turn_rate:
            cursor.write_int16(Scaled.to_scaled(self.turn_rate, 0.0, 0.005))
        
        if self.has_magnetic_variation:
            cursor.write_uint16(BAM.to_bam16(self.magnetic_variation))
        

    def deserialize(self, cursor: BitCursor):
        # 1. Read PV
        
        
        
        self.pv = cursor.read_uint24()
        
        
        

        # 2. Read Fields
        
        if self.pv & (1 << 0):
            self.has_time_stamp = True
            self.time_stamp = cursor.read_uint40()
        else:
            self.has_time_stamp = False
        
        if self.pv & (1 << 1):
            self.has_latitude = True
            self.latitude = BAM.from_bam32(cursor.read_uint32())
        else:
            self.has_latitude = False
        
        if self.pv & (1 << 2):
            self.has_longitude = True
            self.longitude = BAM.from_bam32(cursor.read_uint32())
        else:
            self.has_longitude = False
        
        if self.pv & (1 << 3):
            self.has_altitude = True
            self.altitude = Scaled.from_scaled(cursor.read_int24(), 0.0, 0.02)
        else:
            self.has_altitude = False
        
        if self.pv & (1 << 4):
            self.has_altitude_type = True
            self.altitude_type = cursor.read_uint8()
        else:
            self.has_altitude_type = False
        
        if self.pv & (1 << 5):
            self.has_u_speed = True
            self.u_speed = Scaled.from_scaled(cursor.read_int16(), 0.0, 0.05)
        else:
            self.has_u_speed = False
        
        if self.pv & (1 << 6):
            self.has_v_speed = True
            self.v_speed = Scaled.from_scaled(cursor.read_int16(), 0.0, 0.05)
        else:
            self.has_v_speed = False
        
        if self.pv & (1 << 7):
            self.has_w_speed = True
            self.w_speed = Scaled.from_scaled(cursor.read_int16(), 0.0, 0.05)
        else:
            self.has_w_speed = False
        
        if self.pv & (1 << 8):
            self.has_u_accel = True
            self.u_accel = Scaled.from_scaled(cursor.read_int16(), 0.0, 0.005)
        else:
            self.has_u_accel = False
        
        if self.pv & (1 << 9):
            self.has_v_accel = True
            self.v_accel = Scaled.from_scaled(cursor.read_int16(), 0.0, 0.005)
        else:
            self.has_v_accel = False
        
        if self.pv & (1 << 10):
            self.has_w_accel = True
            self.w_accel = Scaled.from_scaled(cursor.read_int16(), 0.0, 0.005)
        else:
            self.has_w_accel = False
        
        if self.pv & (1 << 11):
            self.has_roll = True
            self.roll = BAM.from_bam16(cursor.read_uint16())
        else:
            self.has_roll = False
        
        if self.pv & (1 << 12):
            self.has_pitch = True
            self.pitch = BAM.from_bam16(cursor.read_uint16())
        else:
            self.has_pitch = False
        
        if self.pv & (1 << 13):
            self.has_heading = True
            self.heading = BAM.from_bam16(cursor.read_uint16())
        else:
            self.has_heading = False
        
        if self.pv & (1 << 14):
            self.has_roll_rate = True
            self.roll_rate = Scaled.from_scaled(cursor.read_int16(), 0.0, 0.005)
        else:
            self.has_roll_rate = False
        
        if self.pv & (1 << 15):
            self.has_pitch_rate = True
            self.pitch_rate = Scaled.from_scaled(cursor.read_int16(), 0.0, 0.005)
        else:
            self.has_pitch_rate = False
        
        if self.pv & (1 << 16):
            self.has_turn_rate = True
            self.turn_rate = Scaled.from_scaled(cursor.read_int16(), 0.0, 0.005)
        else:
            self.has_turn_rate = False
        
        if self.pv & (1 << 17):
            self.has_magnetic_variation = True
            self.magnetic_variation = BAM.from_bam16(cursor.read_uint16())
        else:
            self.has_magnetic_variation = False
        

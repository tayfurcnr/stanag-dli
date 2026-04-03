from dli.core.bit_cursor import BitCursor
from dli.utils import BAM, Scaled
import math

class VehicleOperatingModeCommand:
    def __init__(self):
        # Presence Vector
        self.pv = 0
        
        self.time_stamp = 0
        self.has_time_stamp = False
        
        self.select_flight_path_control_mode = 0
        self.has_select_flight_path_control_mode = False
        
        self.altitude_command_type = 0
        self.has_altitude_command_type = False
        
        self.commanded_altitude = 0.0
        self.has_commanded_altitude = False
        
        self.commanded_vertical_speed = 0.0
        self.has_commanded_vertical_speed = False
        
        self.heading_command_type = 0
        self.has_heading_command_type = False
        
        self.heading_reference = 0
        self.has_heading_reference = False
        
        self.commanded_heading = 0.0
        self.has_commanded_heading = False
        
        self.commanded_course = 0.0
        self.has_commanded_course = False
        
        self.commanded_turn_rate = 0.0
        self.has_commanded_turn_rate = False
        
        self.commanded_roll_rate = 0.0
        self.has_commanded_roll_rate = False
        
        self.commanded_roll = 0.0
        self.has_commanded_roll = False
        
        self.commanded_speed = 0.0
        self.has_commanded_speed = False
        
        self.speed_type = 0
        self.has_speed_type = False
        
        self.commanded_waypoint_number = 0
        self.has_commanded_waypoint_number = False
        
        self.altimeter_setting = 0.0
        self.has_altimeter_setting = False
        
        self.altitude_type = 0
        self.has_altitude_type = False
        
        self.loiter_position_latitude = 0.0
        self.has_loiter_position_latitude = False
        
        self.loiter_position_longitude = 0.0
        self.has_loiter_position_longitude = False
        
        self.loiter_altitude_change_behaviour = 0
        self.has_loiter_altitude_change_behaviour = False
        
        self.thrust_direction = 0.0
        self.has_thrust_direction = False
        
        self.thrust = 0
        self.has_thrust = False
        
        self.activity_id = 0
        self.has_activity_id = False
        

    def serialize(self, cursor: BitCursor):
        # 1. Prepare PV
        self.pv = 0
        
        if self.has_time_stamp:
            self.pv |= (1 << 0)
        
        if self.has_select_flight_path_control_mode:
            self.pv |= (1 << 1)
        
        if self.has_altitude_command_type:
            self.pv |= (1 << 2)
        
        if self.has_commanded_altitude:
            self.pv |= (1 << 3)
        
        if self.has_commanded_vertical_speed:
            self.pv |= (1 << 4)
        
        if self.has_heading_command_type:
            self.pv |= (1 << 5)
        
        if self.has_heading_reference:
            self.pv |= (1 << 6)
        
        if self.has_commanded_heading:
            self.pv |= (1 << 7)
        
        if self.has_commanded_course:
            self.pv |= (1 << 8)
        
        if self.has_commanded_turn_rate:
            self.pv |= (1 << 9)
        
        if self.has_commanded_roll_rate:
            self.pv |= (1 << 10)
        
        if self.has_commanded_roll:
            self.pv |= (1 << 11)
        
        if self.has_commanded_speed:
            self.pv |= (1 << 12)
        
        if self.has_speed_type:
            self.pv |= (1 << 13)
        
        if self.has_commanded_waypoint_number:
            self.pv |= (1 << 14)
        
        if self.has_altimeter_setting:
            self.pv |= (1 << 15)
        
        if self.has_altitude_type:
            self.pv |= (1 << 16)
        
        if self.has_loiter_position_latitude:
            self.pv |= (1 << 17)
        
        if self.has_loiter_position_longitude:
            self.pv |= (1 << 18)
        
        if self.has_loiter_altitude_change_behaviour:
            self.pv |= (1 << 19)
        
        if self.has_thrust_direction:
            self.pv |= (1 << 20)
        
        if self.has_thrust:
            self.pv |= (1 << 21)
        
        if self.has_activity_id:
            self.pv |= (1 << 22)
        

        # 2. Write PV
        
        
        
        cursor.write_uint24(self.pv)
        
        
        

        # 3. Write Fields
        
        if self.has_time_stamp:
            cursor.write_uint40(self.time_stamp)
        
        if self.has_select_flight_path_control_mode:
            cursor.write_uint8(self.select_flight_path_control_mode)
        
        if self.has_altitude_command_type:
            cursor.write_uint8(self.altitude_command_type)
        
        if self.has_commanded_altitude:
            cursor.write_int24(Scaled.to_scaled(self.commanded_altitude, 0.0, 0.02))
        
        if self.has_commanded_vertical_speed:
            cursor.write_int16(Scaled.to_scaled(self.commanded_vertical_speed, 0.0, 0.05))
        
        if self.has_heading_command_type:
            cursor.write_uint8(self.heading_command_type)
        
        if self.has_heading_reference:
            cursor.write_uint8(self.heading_reference)
        
        if self.has_commanded_heading:
            cursor.write_uint16(BAM.to_bam16(self.commanded_heading))
        
        if self.has_commanded_course:
            cursor.write_uint16(BAM.to_bam16(self.commanded_course))
        
        if self.has_commanded_turn_rate:
            cursor.write_int16(Scaled.to_scaled(self.commanded_turn_rate, 0.0, 0.005))
        
        if self.has_commanded_roll_rate:
            cursor.write_int16(Scaled.to_scaled(self.commanded_roll_rate, 0.0, 0.005))
        
        if self.has_commanded_roll:
            cursor.write_uint16(BAM.to_bam16(self.commanded_roll))
        
        if self.has_commanded_speed:
            cursor.write_uint16(Scaled.to_scaled(self.commanded_speed, 0.0, 0.5))
        
        if self.has_speed_type:
            cursor.write_uint8(self.speed_type)
        
        if self.has_commanded_waypoint_number:
            cursor.write_uint16(self.commanded_waypoint_number)
        
        if self.has_altimeter_setting:
            cursor.write_uint16(Scaled.to_scaled(self.altimeter_setting, 0.0, 10.0))
        
        if self.has_altitude_type:
            cursor.write_uint8(self.altitude_type)
        
        if self.has_loiter_position_latitude:
            cursor.write_uint32(BAM.to_bam32(self.loiter_position_latitude))
        
        if self.has_loiter_position_longitude:
            cursor.write_uint32(BAM.to_bam32(self.loiter_position_longitude))
        
        if self.has_loiter_altitude_change_behaviour:
            cursor.write_uint8(self.loiter_altitude_change_behaviour)
        
        if self.has_thrust_direction:
            cursor.write_uint16(BAM.to_bam16(self.thrust_direction))
        
        if self.has_thrust:
            cursor.write_uint8(self.thrust)
        
        if self.has_activity_id:
            cursor.write_uint24(self.activity_id)
        

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
            self.has_select_flight_path_control_mode = True
            self.select_flight_path_control_mode = cursor.read_uint8()
        else:
            self.has_select_flight_path_control_mode = False
        
        if self.pv & (1 << 2):
            self.has_altitude_command_type = True
            self.altitude_command_type = cursor.read_uint8()
        else:
            self.has_altitude_command_type = False
        
        if self.pv & (1 << 3):
            self.has_commanded_altitude = True
            self.commanded_altitude = Scaled.from_scaled(cursor.read_int24(), 0.0, 0.02)
        else:
            self.has_commanded_altitude = False
        
        if self.pv & (1 << 4):
            self.has_commanded_vertical_speed = True
            self.commanded_vertical_speed = Scaled.from_scaled(cursor.read_int16(), 0.0, 0.05)
        else:
            self.has_commanded_vertical_speed = False
        
        if self.pv & (1 << 5):
            self.has_heading_command_type = True
            self.heading_command_type = cursor.read_uint8()
        else:
            self.has_heading_command_type = False
        
        if self.pv & (1 << 6):
            self.has_heading_reference = True
            self.heading_reference = cursor.read_uint8()
        else:
            self.has_heading_reference = False
        
        if self.pv & (1 << 7):
            self.has_commanded_heading = True
            self.commanded_heading = BAM.from_bam16(cursor.read_uint16())
        else:
            self.has_commanded_heading = False
        
        if self.pv & (1 << 8):
            self.has_commanded_course = True
            self.commanded_course = BAM.from_bam16(cursor.read_uint16())
        else:
            self.has_commanded_course = False
        
        if self.pv & (1 << 9):
            self.has_commanded_turn_rate = True
            self.commanded_turn_rate = Scaled.from_scaled(cursor.read_int16(), 0.0, 0.005)
        else:
            self.has_commanded_turn_rate = False
        
        if self.pv & (1 << 10):
            self.has_commanded_roll_rate = True
            self.commanded_roll_rate = Scaled.from_scaled(cursor.read_int16(), 0.0, 0.005)
        else:
            self.has_commanded_roll_rate = False
        
        if self.pv & (1 << 11):
            self.has_commanded_roll = True
            self.commanded_roll = BAM.from_bam16(cursor.read_uint16())
        else:
            self.has_commanded_roll = False
        
        if self.pv & (1 << 12):
            self.has_commanded_speed = True
            self.commanded_speed = Scaled.from_scaled(cursor.read_uint16(), 0.0, 0.5)
        else:
            self.has_commanded_speed = False
        
        if self.pv & (1 << 13):
            self.has_speed_type = True
            self.speed_type = cursor.read_uint8()
        else:
            self.has_speed_type = False
        
        if self.pv & (1 << 14):
            self.has_commanded_waypoint_number = True
            self.commanded_waypoint_number = cursor.read_uint16()
        else:
            self.has_commanded_waypoint_number = False
        
        if self.pv & (1 << 15):
            self.has_altimeter_setting = True
            self.altimeter_setting = Scaled.from_scaled(cursor.read_uint16(), 0.0, 10.0)
        else:
            self.has_altimeter_setting = False
        
        if self.pv & (1 << 16):
            self.has_altitude_type = True
            self.altitude_type = cursor.read_uint8()
        else:
            self.has_altitude_type = False
        
        if self.pv & (1 << 17):
            self.has_loiter_position_latitude = True
            self.loiter_position_latitude = BAM.from_bam32(cursor.read_uint32())
        else:
            self.has_loiter_position_latitude = False
        
        if self.pv & (1 << 18):
            self.has_loiter_position_longitude = True
            self.loiter_position_longitude = BAM.from_bam32(cursor.read_uint32())
        else:
            self.has_loiter_position_longitude = False
        
        if self.pv & (1 << 19):
            self.has_loiter_altitude_change_behaviour = True
            self.loiter_altitude_change_behaviour = cursor.read_uint8()
        else:
            self.has_loiter_altitude_change_behaviour = False
        
        if self.pv & (1 << 20):
            self.has_thrust_direction = True
            self.thrust_direction = BAM.from_bam16(cursor.read_uint16())
        else:
            self.has_thrust_direction = False
        
        if self.pv & (1 << 21):
            self.has_thrust = True
            self.thrust = cursor.read_uint8()
        else:
            self.has_thrust = False
        
        if self.pv & (1 << 22):
            self.has_activity_id = True
            self.activity_id = cursor.read_uint24()
        else:
            self.has_activity_id = False
        

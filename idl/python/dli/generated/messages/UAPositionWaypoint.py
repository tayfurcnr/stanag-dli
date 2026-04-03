from dli.core.bit_cursor import BitCursor
from dli.utils import BAM, Scaled
import math

class UAPositionWaypoint:
    def __init__(self):
        # Presence Vector
        self.pv = 0
        
        self.time_stamp = 0
        self.has_time_stamp = False
        
        self.waypoint_number = 0
        self.has_waypoint_number = False
        
        self.waypoint_to_latitude_or_relative_y = 0.0
        self.has_waypoint_to_latitude_or_relative_y = False
        
        self.waypoint_to_longitude_or_relative_x = 0.0
        self.has_waypoint_to_longitude_or_relative_x = False
        
        self.location_type = 0
        self.has_location_type = False
        
        self.waypoint_to_altitude = 0.0
        self.has_waypoint_to_altitude = False
        
        self.waypoint_altitude_type = 0
        self.has_waypoint_altitude_type = False
        
        self.altitude_change_behaviour = 0
        self.has_altitude_change_behaviour = False
        
        self.waypoint_to_speed = 0.0
        self.has_waypoint_to_speed = False
        
        self.waypoint_speed_type = 0
        self.has_waypoint_speed_type = False
        
        self.next_waypoint = 0
        self.has_next_waypoint = False
        
        self.turn_type = 0
        self.has_turn_type = False
        
        self.optional_messages_for_waypoint = 0
        self.has_optional_messages_for_waypoint = False
        
        self.waypoint_type = 0
        self.has_waypoint_type = False
        
        self.limit_type = 0
        self.has_limit_type = False
        
        self.loop_limit = 0
        self.has_loop_limit = False
        
        self.arrival_time = 0
        self.has_arrival_time = False
        
        self.activity_id = 0
        self.has_activity_id = False
        

    def serialize(self, cursor: BitCursor):
        # 1. Prepare PV
        self.pv = 0
        
        if self.has_time_stamp:
            self.pv |= (1 << 0)
        
        if self.has_waypoint_number:
            self.pv |= (1 << 1)
        
        if self.has_waypoint_to_latitude_or_relative_y:
            self.pv |= (1 << 2)
        
        if self.has_waypoint_to_longitude_or_relative_x:
            self.pv |= (1 << 3)
        
        if self.has_location_type:
            self.pv |= (1 << 4)
        
        if self.has_waypoint_to_altitude:
            self.pv |= (1 << 5)
        
        if self.has_waypoint_altitude_type:
            self.pv |= (1 << 6)
        
        if self.has_altitude_change_behaviour:
            self.pv |= (1 << 7)
        
        if self.has_waypoint_to_speed:
            self.pv |= (1 << 8)
        
        if self.has_waypoint_speed_type:
            self.pv |= (1 << 9)
        
        if self.has_next_waypoint:
            self.pv |= (1 << 10)
        
        if self.has_turn_type:
            self.pv |= (1 << 11)
        
        if self.has_optional_messages_for_waypoint:
            self.pv |= (1 << 12)
        
        if self.has_waypoint_type:
            self.pv |= (1 << 13)
        
        if self.has_limit_type:
            self.pv |= (1 << 14)
        
        if self.has_loop_limit:
            self.pv |= (1 << 15)
        
        if self.has_arrival_time:
            self.pv |= (1 << 16)
        
        if self.has_activity_id:
            self.pv |= (1 << 17)
        

        # 2. Write PV
        
        
        
        cursor.write_uint24(self.pv)
        
        
        

        # 3. Write Fields
        
        if self.has_time_stamp:
            cursor.write_uint40(self.time_stamp)
        
        if self.has_waypoint_number:
            cursor.write_uint16(self.waypoint_number)
        
        if self.has_waypoint_to_latitude_or_relative_y:
            cursor.write_uint32(BAM.to_bam32(self.waypoint_to_latitude_or_relative_y))
        
        if self.has_waypoint_to_longitude_or_relative_x:
            cursor.write_uint32(BAM.to_bam32(self.waypoint_to_longitude_or_relative_x))
        
        if self.has_location_type:
            cursor.write_uint8(self.location_type)
        
        if self.has_waypoint_to_altitude:
            cursor.write_int24(Scaled.to_scaled(self.waypoint_to_altitude, 0.0, 0.02))
        
        if self.has_waypoint_altitude_type:
            cursor.write_uint8(self.waypoint_altitude_type)
        
        if self.has_altitude_change_behaviour:
            cursor.write_uint8(self.altitude_change_behaviour)
        
        if self.has_waypoint_to_speed:
            cursor.write_uint16(Scaled.to_scaled(self.waypoint_to_speed, 0.0, 0.5))
        
        if self.has_waypoint_speed_type:
            cursor.write_uint8(self.waypoint_speed_type)
        
        if self.has_next_waypoint:
            cursor.write_uint16(self.next_waypoint)
        
        if self.has_turn_type:
            cursor.write_uint8(self.turn_type)
        
        if self.has_optional_messages_for_waypoint:
            cursor.write_uint8(self.optional_messages_for_waypoint)
        
        if self.has_waypoint_type:
            cursor.write_uint8(self.waypoint_type)
        
        if self.has_limit_type:
            cursor.write_uint8(self.limit_type)
        
        if self.has_loop_limit:
            cursor.write_uint16(self.loop_limit)
        
        if self.has_arrival_time:
            cursor.write_uint40(self.arrival_time)
        
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
            self.has_waypoint_number = True
            self.waypoint_number = cursor.read_uint16()
        else:
            self.has_waypoint_number = False
        
        if self.pv & (1 << 2):
            self.has_waypoint_to_latitude_or_relative_y = True
            self.waypoint_to_latitude_or_relative_y = BAM.from_bam32(cursor.read_uint32())
        else:
            self.has_waypoint_to_latitude_or_relative_y = False
        
        if self.pv & (1 << 3):
            self.has_waypoint_to_longitude_or_relative_x = True
            self.waypoint_to_longitude_or_relative_x = BAM.from_bam32(cursor.read_uint32())
        else:
            self.has_waypoint_to_longitude_or_relative_x = False
        
        if self.pv & (1 << 4):
            self.has_location_type = True
            self.location_type = cursor.read_uint8()
        else:
            self.has_location_type = False
        
        if self.pv & (1 << 5):
            self.has_waypoint_to_altitude = True
            self.waypoint_to_altitude = Scaled.from_scaled(cursor.read_int24(), 0.0, 0.02)
        else:
            self.has_waypoint_to_altitude = False
        
        if self.pv & (1 << 6):
            self.has_waypoint_altitude_type = True
            self.waypoint_altitude_type = cursor.read_uint8()
        else:
            self.has_waypoint_altitude_type = False
        
        if self.pv & (1 << 7):
            self.has_altitude_change_behaviour = True
            self.altitude_change_behaviour = cursor.read_uint8()
        else:
            self.has_altitude_change_behaviour = False
        
        if self.pv & (1 << 8):
            self.has_waypoint_to_speed = True
            self.waypoint_to_speed = Scaled.from_scaled(cursor.read_uint16(), 0.0, 0.5)
        else:
            self.has_waypoint_to_speed = False
        
        if self.pv & (1 << 9):
            self.has_waypoint_speed_type = True
            self.waypoint_speed_type = cursor.read_uint8()
        else:
            self.has_waypoint_speed_type = False
        
        if self.pv & (1 << 10):
            self.has_next_waypoint = True
            self.next_waypoint = cursor.read_uint16()
        else:
            self.has_next_waypoint = False
        
        if self.pv & (1 << 11):
            self.has_turn_type = True
            self.turn_type = cursor.read_uint8()
        else:
            self.has_turn_type = False
        
        if self.pv & (1 << 12):
            self.has_optional_messages_for_waypoint = True
            self.optional_messages_for_waypoint = cursor.read_uint8()
        else:
            self.has_optional_messages_for_waypoint = False
        
        if self.pv & (1 << 13):
            self.has_waypoint_type = True
            self.waypoint_type = cursor.read_uint8()
        else:
            self.has_waypoint_type = False
        
        if self.pv & (1 << 14):
            self.has_limit_type = True
            self.limit_type = cursor.read_uint8()
        else:
            self.has_limit_type = False
        
        if self.pv & (1 << 15):
            self.has_loop_limit = True
            self.loop_limit = cursor.read_uint16()
        else:
            self.has_loop_limit = False
        
        if self.pv & (1 << 16):
            self.has_arrival_time = True
            self.arrival_time = cursor.read_uint40()
        else:
            self.has_arrival_time = False
        
        if self.pv & (1 << 17):
            self.has_activity_id = True
            self.activity_id = cursor.read_uint24()
        else:
            self.has_activity_id = False
        

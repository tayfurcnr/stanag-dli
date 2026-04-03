from dli.core.bit_cursor import BitCursor
from dli.utils import BAM, Scaled
import math

class FromToNextWaypointStates:
    def __init__(self):
        # Presence Vector
        self.pv = 0
        
        self.time_stamp = 0
        self.has_time_stamp = False
        
        self.altitude_type = 0
        self.has_altitude_type = False
        
        self.speed_type = 0
        self.has_speed_type = False
        
        self.from_waypoint_–_latitude = 0.0
        self.has_from_waypoint_–_latitude = False
        
        self.from_waypoint_–_longitude = 0.0
        self.has_from_waypoint_–_longitude = False
        
        self.from_waypoint_altitude = 0.0
        self.has_from_waypoint_altitude = False
        
        self.from_waypoint_time = 0
        self.has_from_waypoint_time = False
        
        self.from_waypoint_number = 0
        self.has_from_waypoint_number = False
        
        self.to_waypoint_–_latitude = 0.0
        self.has_to_waypoint_–_latitude = False
        
        self.to_waypoint_–_longitude = 0.0
        self.has_to_waypoint_–_longitude = False
        
        self.to_waypoint_altitude = 0.0
        self.has_to_waypoint_altitude = False
        
        self.to_waypoint_speed = 0.0
        self.has_to_waypoint_speed = False
        
        self.to_waypoint_time = 0
        self.has_to_waypoint_time = False
        
        self.to_waypoint_number = 0
        self.has_to_waypoint_number = False
        
        self.next_waypoint_–_latitude = 0.0
        self.has_next_waypoint_–_latitude = False
        
        self.next_waypoint_–_longitude = 0.0
        self.has_next_waypoint_–_longitude = False
        
        self.next_waypoint_altitude = 0.0
        self.has_next_waypoint_altitude = False
        
        self.next_waypoint_speed = 0.0
        self.has_next_waypoint_speed = False
        
        self.next_waypoint_time = 0
        self.has_next_waypoint_time = False
        
        self.next_waypoint_number = 0
        self.has_next_waypoint_number = False
        
        self.loiter_configuration_report_validity_for_“to_waypoint” = 0
        self.has_loiter_configuration_report_validity_for_“to_waypoint” = False
        

    def serialize(self, cursor: BitCursor):
        # 1. Prepare PV
        self.pv = 0
        
        if self.has_time_stamp:
            self.pv |= (1 << 0)
        
        if self.has_altitude_type:
            self.pv |= (1 << 1)
        
        if self.has_speed_type:
            self.pv |= (1 << 2)
        
        if self.has_from_waypoint_–_latitude:
            self.pv |= (1 << 3)
        
        if self.has_from_waypoint_–_longitude:
            self.pv |= (1 << 4)
        
        if self.has_from_waypoint_altitude:
            self.pv |= (1 << 5)
        
        if self.has_from_waypoint_time:
            self.pv |= (1 << 6)
        
        if self.has_from_waypoint_number:
            self.pv |= (1 << 7)
        
        if self.has_to_waypoint_–_latitude:
            self.pv |= (1 << 8)
        
        if self.has_to_waypoint_–_longitude:
            self.pv |= (1 << 9)
        
        if self.has_to_waypoint_altitude:
            self.pv |= (1 << 10)
        
        if self.has_to_waypoint_speed:
            self.pv |= (1 << 11)
        
        if self.has_to_waypoint_time:
            self.pv |= (1 << 12)
        
        if self.has_to_waypoint_number:
            self.pv |= (1 << 13)
        
        if self.has_next_waypoint_–_latitude:
            self.pv |= (1 << 14)
        
        if self.has_next_waypoint_–_longitude:
            self.pv |= (1 << 15)
        
        if self.has_next_waypoint_altitude:
            self.pv |= (1 << 16)
        
        if self.has_next_waypoint_speed:
            self.pv |= (1 << 17)
        
        if self.has_next_waypoint_time:
            self.pv |= (1 << 18)
        
        if self.has_next_waypoint_number:
            self.pv |= (1 << 19)
        
        if self.has_loiter_configuration_report_validity_for_“to_waypoint”:
            self.pv |= (1 << 20)
        

        # 2. Write PV
        
        
        
        cursor.write_uint24(self.pv)
        
        
        

        # 3. Write Fields
        
        if self.has_time_stamp:
            cursor.write_uint40(self.time_stamp)
        
        if self.has_altitude_type:
            cursor.write_uint8(self.altitude_type)
        
        if self.has_speed_type:
            cursor.write_uint8(self.speed_type)
        
        if self.has_from_waypoint_–_latitude:
            cursor.write_uint32(BAM.to_bam32(self.from_waypoint_–_latitude))
        
        if self.has_from_waypoint_–_longitude:
            cursor.write_uint32(BAM.to_bam32(self.from_waypoint_–_longitude))
        
        if self.has_from_waypoint_altitude:
            cursor.write_int24(Scaled.to_scaled(self.from_waypoint_altitude, 0.0, 0.02))
        
        if self.has_from_waypoint_time:
            cursor.write_uint40(self.from_waypoint_time)
        
        if self.has_from_waypoint_number:
            cursor.write_uint16(self.from_waypoint_number)
        
        if self.has_to_waypoint_–_latitude:
            cursor.write_uint32(BAM.to_bam32(self.to_waypoint_–_latitude))
        
        if self.has_to_waypoint_–_longitude:
            cursor.write_uint32(BAM.to_bam32(self.to_waypoint_–_longitude))
        
        if self.has_to_waypoint_altitude:
            cursor.write_int24(Scaled.to_scaled(self.to_waypoint_altitude, 0.0, 0.02))
        
        if self.has_to_waypoint_speed:
            cursor.write_uint16(Scaled.to_scaled(self.to_waypoint_speed, 0.0, 0.5))
        
        if self.has_to_waypoint_time:
            cursor.write_uint40(self.to_waypoint_time)
        
        if self.has_to_waypoint_number:
            cursor.write_uint16(self.to_waypoint_number)
        
        if self.has_next_waypoint_–_latitude:
            cursor.write_uint32(BAM.to_bam32(self.next_waypoint_–_latitude))
        
        if self.has_next_waypoint_–_longitude:
            cursor.write_uint32(BAM.to_bam32(self.next_waypoint_–_longitude))
        
        if self.has_next_waypoint_altitude:
            cursor.write_int24(Scaled.to_scaled(self.next_waypoint_altitude, 0.0, 0.02))
        
        if self.has_next_waypoint_speed:
            cursor.write_uint16(Scaled.to_scaled(self.next_waypoint_speed, 0.0, 0.5))
        
        if self.has_next_waypoint_time:
            cursor.write_uint40(self.next_waypoint_time)
        
        if self.has_next_waypoint_number:
            cursor.write_uint16(self.next_waypoint_number)
        
        if self.has_loiter_configuration_report_validity_for_“to_waypoint”:
            cursor.write_uint8(self.loiter_configuration_report_validity_for_“to_waypoint”)
        

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
            self.has_altitude_type = True
            self.altitude_type = cursor.read_uint8()
        else:
            self.has_altitude_type = False
        
        if self.pv & (1 << 2):
            self.has_speed_type = True
            self.speed_type = cursor.read_uint8()
        else:
            self.has_speed_type = False
        
        if self.pv & (1 << 3):
            self.has_from_waypoint_–_latitude = True
            self.from_waypoint_–_latitude = BAM.from_bam32(cursor.read_uint32())
        else:
            self.has_from_waypoint_–_latitude = False
        
        if self.pv & (1 << 4):
            self.has_from_waypoint_–_longitude = True
            self.from_waypoint_–_longitude = BAM.from_bam32(cursor.read_uint32())
        else:
            self.has_from_waypoint_–_longitude = False
        
        if self.pv & (1 << 5):
            self.has_from_waypoint_altitude = True
            self.from_waypoint_altitude = Scaled.from_scaled(cursor.read_int24(), 0.0, 0.02)
        else:
            self.has_from_waypoint_altitude = False
        
        if self.pv & (1 << 6):
            self.has_from_waypoint_time = True
            self.from_waypoint_time = cursor.read_uint40()
        else:
            self.has_from_waypoint_time = False
        
        if self.pv & (1 << 7):
            self.has_from_waypoint_number = True
            self.from_waypoint_number = cursor.read_uint16()
        else:
            self.has_from_waypoint_number = False
        
        if self.pv & (1 << 8):
            self.has_to_waypoint_–_latitude = True
            self.to_waypoint_–_latitude = BAM.from_bam32(cursor.read_uint32())
        else:
            self.has_to_waypoint_–_latitude = False
        
        if self.pv & (1 << 9):
            self.has_to_waypoint_–_longitude = True
            self.to_waypoint_–_longitude = BAM.from_bam32(cursor.read_uint32())
        else:
            self.has_to_waypoint_–_longitude = False
        
        if self.pv & (1 << 10):
            self.has_to_waypoint_altitude = True
            self.to_waypoint_altitude = Scaled.from_scaled(cursor.read_int24(), 0.0, 0.02)
        else:
            self.has_to_waypoint_altitude = False
        
        if self.pv & (1 << 11):
            self.has_to_waypoint_speed = True
            self.to_waypoint_speed = Scaled.from_scaled(cursor.read_uint16(), 0.0, 0.5)
        else:
            self.has_to_waypoint_speed = False
        
        if self.pv & (1 << 12):
            self.has_to_waypoint_time = True
            self.to_waypoint_time = cursor.read_uint40()
        else:
            self.has_to_waypoint_time = False
        
        if self.pv & (1 << 13):
            self.has_to_waypoint_number = True
            self.to_waypoint_number = cursor.read_uint16()
        else:
            self.has_to_waypoint_number = False
        
        if self.pv & (1 << 14):
            self.has_next_waypoint_–_latitude = True
            self.next_waypoint_–_latitude = BAM.from_bam32(cursor.read_uint32())
        else:
            self.has_next_waypoint_–_latitude = False
        
        if self.pv & (1 << 15):
            self.has_next_waypoint_–_longitude = True
            self.next_waypoint_–_longitude = BAM.from_bam32(cursor.read_uint32())
        else:
            self.has_next_waypoint_–_longitude = False
        
        if self.pv & (1 << 16):
            self.has_next_waypoint_altitude = True
            self.next_waypoint_altitude = Scaled.from_scaled(cursor.read_int24(), 0.0, 0.02)
        else:
            self.has_next_waypoint_altitude = False
        
        if self.pv & (1 << 17):
            self.has_next_waypoint_speed = True
            self.next_waypoint_speed = Scaled.from_scaled(cursor.read_uint16(), 0.0, 0.5)
        else:
            self.has_next_waypoint_speed = False
        
        if self.pv & (1 << 18):
            self.has_next_waypoint_time = True
            self.next_waypoint_time = cursor.read_uint40()
        else:
            self.has_next_waypoint_time = False
        
        if self.pv & (1 << 19):
            self.has_next_waypoint_number = True
            self.next_waypoint_number = cursor.read_uint16()
        else:
            self.has_next_waypoint_number = False
        
        if self.pv & (1 << 20):
            self.has_loiter_configuration_report_validity_for_“to_waypoint” = True
            self.loiter_configuration_report_validity_for_“to_waypoint” = cursor.read_uint8()
        else:
            self.has_loiter_configuration_report_validity_for_“to_waypoint” = False
        

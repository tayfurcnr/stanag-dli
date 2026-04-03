from dli.core.bit_cursor import BitCursor
from dli.utils import BAM, Scaled
import math

class PositiveHandoverAuthorisationGranted:
    def __init__(self):
        # Presence Vector
        self.pv = 0
        
        self.time_stamp = 0
        self.has_time_stamp = False
        
        self.vsm_id = 0
        self.has_vsm_id = False
        
        self.data_link_id = 0
        self.has_data_link_id = False
        
        self.loi_authorized = 0
        self.has_loi_authorized = False
        
        self.flight_mode_offset = 0
        self.has_flight_mode_offset = False
        
        self.flight_modes_authorized = 0
        self.has_flight_modes_authorized = False
        
        self.controlled_station_1_16_authorized = 0
        self.has_controlled_station_1_16_authorized = False
        
        self.component_number_authorized = 0
        self.has_component_number_authorized = False
        
        self.sub_component_number_authorized = 0
        self.has_sub_component_number_authorized = False
        
        self.vehicle_type = 0
        self.has_vehicle_type = False
        
        self.vehicle_subtype = 0
        self.has_vehicle_subtype = False
        
        self.requesting_cucs_type = 0
        self.has_requesting_cucs_type = False
        
        self.requesting_cucs_subtype = 0
        self.has_requesting_cucs_subtype = False
        
        self.requesting_cucs_id = 0
        self.has_requesting_cucs_id = False
        
        self.presence_vector_support = 0
        self.has_presence_vector_support = False
        
        self.controlled_station_17_32_authorized = 0
        self.has_controlled_station_17_32_authorized = False
        

    def serialize(self, cursor: BitCursor):
        # 1. Prepare PV
        self.pv = 0
        
        if self.has_time_stamp:
            self.pv |= (1 << 0)
        
        if self.has_vsm_id:
            self.pv |= (1 << 1)
        
        if self.has_data_link_id:
            self.pv |= (1 << 2)
        
        if self.has_loi_authorized:
            self.pv |= (1 << 3)
        
        if self.has_flight_mode_offset:
            self.pv |= (1 << 4)
        
        if self.has_flight_modes_authorized:
            self.pv |= (1 << 5)
        
        if self.has_controlled_station_1_16_authorized:
            self.pv |= (1 << 6)
        
        if self.has_component_number_authorized:
            self.pv |= (1 << 7)
        
        if self.has_sub_component_number_authorized:
            self.pv |= (1 << 8)
        
        if self.has_vehicle_type:
            self.pv |= (1 << 9)
        
        if self.has_vehicle_subtype:
            self.pv |= (1 << 10)
        
        if self.has_requesting_cucs_type:
            self.pv |= (1 << 11)
        
        if self.has_requesting_cucs_subtype:
            self.pv |= (1 << 12)
        
        if self.has_requesting_cucs_id:
            self.pv |= (1 << 13)
        
        if self.has_presence_vector_support:
            self.pv |= (1 << 14)
        
        if self.has_controlled_station_17_32_authorized:
            self.pv |= (1 << 15)
        

        # 2. Write PV
        
        
        
        cursor.write_uint24(self.pv)
        
        
        

        # 3. Write Fields
        
        if self.has_time_stamp:
            cursor.write_uint40(self.time_stamp)
        
        if self.has_vsm_id:
            cursor.write_uint32(self.vsm_id)
        
        if self.has_data_link_id:
            cursor.write_uint32(self.data_link_id)
        
        if self.has_loi_authorized:
            cursor.write_uint8(self.loi_authorized)
        
        if self.has_flight_mode_offset:
            cursor.write_uint8(self.flight_mode_offset)
        
        if self.has_flight_modes_authorized:
            cursor.write_uint32(self.flight_modes_authorized)
        
        if self.has_controlled_station_1_16_authorized:
            cursor.write_uint16(self.controlled_station_1_16_authorized)
        
        if self.has_component_number_authorized:
            cursor.write_uint16(self.component_number_authorized)
        
        if self.has_sub_component_number_authorized:
            cursor.write_uint16(self.sub_component_number_authorized)
        
        if self.has_vehicle_type:
            cursor.write_uint16(self.vehicle_type)
        
        if self.has_vehicle_subtype:
            cursor.write_uint16(self.vehicle_subtype)
        
        if self.has_requesting_cucs_type:
            cursor.write_uint8(self.requesting_cucs_type)
        
        if self.has_requesting_cucs_subtype:
            cursor.write_uint16(self.requesting_cucs_subtype)
        
        if self.has_requesting_cucs_id:
            cursor.write_uint32(self.requesting_cucs_id)
        
        if self.has_presence_vector_support:
            cursor.write_uint8(self.presence_vector_support)
        
        if self.has_controlled_station_17_32_authorized:
            cursor.write_uint16(self.controlled_station_17_32_authorized)
        

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
            self.has_vsm_id = True
            self.vsm_id = cursor.read_uint32()
        else:
            self.has_vsm_id = False
        
        if self.pv & (1 << 2):
            self.has_data_link_id = True
            self.data_link_id = cursor.read_uint32()
        else:
            self.has_data_link_id = False
        
        if self.pv & (1 << 3):
            self.has_loi_authorized = True
            self.loi_authorized = cursor.read_uint8()
        else:
            self.has_loi_authorized = False
        
        if self.pv & (1 << 4):
            self.has_flight_mode_offset = True
            self.flight_mode_offset = cursor.read_uint8()
        else:
            self.has_flight_mode_offset = False
        
        if self.pv & (1 << 5):
            self.has_flight_modes_authorized = True
            self.flight_modes_authorized = cursor.read_uint32()
        else:
            self.has_flight_modes_authorized = False
        
        if self.pv & (1 << 6):
            self.has_controlled_station_1_16_authorized = True
            self.controlled_station_1_16_authorized = cursor.read_uint16()
        else:
            self.has_controlled_station_1_16_authorized = False
        
        if self.pv & (1 << 7):
            self.has_component_number_authorized = True
            self.component_number_authorized = cursor.read_uint16()
        else:
            self.has_component_number_authorized = False
        
        if self.pv & (1 << 8):
            self.has_sub_component_number_authorized = True
            self.sub_component_number_authorized = cursor.read_uint16()
        else:
            self.has_sub_component_number_authorized = False
        
        if self.pv & (1 << 9):
            self.has_vehicle_type = True
            self.vehicle_type = cursor.read_uint16()
        else:
            self.has_vehicle_type = False
        
        if self.pv & (1 << 10):
            self.has_vehicle_subtype = True
            self.vehicle_subtype = cursor.read_uint16()
        else:
            self.has_vehicle_subtype = False
        
        if self.pv & (1 << 11):
            self.has_requesting_cucs_type = True
            self.requesting_cucs_type = cursor.read_uint8()
        else:
            self.has_requesting_cucs_type = False
        
        if self.pv & (1 << 12):
            self.has_requesting_cucs_subtype = True
            self.requesting_cucs_subtype = cursor.read_uint16()
        else:
            self.has_requesting_cucs_subtype = False
        
        if self.pv & (1 << 13):
            self.has_requesting_cucs_id = True
            self.requesting_cucs_id = cursor.read_uint32()
        else:
            self.has_requesting_cucs_id = False
        
        if self.pv & (1 << 14):
            self.has_presence_vector_support = True
            self.presence_vector_support = cursor.read_uint8()
        else:
            self.has_presence_vector_support = False
        
        if self.pv & (1 << 15):
            self.has_controlled_station_17_32_authorized = True
            self.controlled_station_17_32_authorized = cursor.read_uint16()
        else:
            self.has_controlled_station_17_32_authorized = False
        

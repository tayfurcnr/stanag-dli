from dli.core.bit_cursor import BitCursor
from dli.utils import BAM, Scaled
import math

class CUCSAuthorisationRequest:
    def __init__(self):
        # Presence Vector
        self.pv = 0
        
        self.time_stamp = 0
        self.has_time_stamp = False
        
        self.vsm_id = 0
        self.has_vsm_id = False
        
        self.data_link_id = 0
        self.has_data_link_id = False
        
        self.vehicle_type = 0
        self.has_vehicle_type = False
        
        self.vehicle_subtype = 0
        self.has_vehicle_subtype = False
        
        self.requested_handover_loi = 0
        self.has_requested_handover_loi = False
        
        self.requested_handover_access = 0
        self.has_requested_handover_access = False
        
        self.requested_flight_mode = 0
        self.has_requested_flight_mode = False
        
        self.controlled_station_1_16 = 0
        self.has_controlled_station_1_16 = False
        
        self.component_number = 0
        self.has_component_number = False
        
        self.sub_component_number = 0
        self.has_sub_component_number = False
        
        self.payload_type = 0
        self.has_payload_type = False
        
        self.asset_mode = 0
        self.has_asset_mode = False
        
        self.wait_for_vehicle_data_link_transition_coordination_message = 0
        self.has_wait_for_vehicle_data_link_transition_coordination_message = False
        
        self.cucs_type = 0
        self.has_cucs_type = False
        
        self.cucs_subtype = 0
        self.has_cucs_subtype = False
        
        self.presence_vector_support = 0
        self.has_presence_vector_support = False
        
        self.controlled_station_17_32 = 0
        self.has_controlled_station_17_32 = False
        

    def serialize(self, cursor: BitCursor):
        # 1. Prepare PV
        self.pv = 0
        
        if self.has_time_stamp:
            self.pv |= (1 << 0)
        
        if self.has_vsm_id:
            self.pv |= (1 << 1)
        
        if self.has_data_link_id:
            self.pv |= (1 << 2)
        
        if self.has_vehicle_type:
            self.pv |= (1 << 3)
        
        if self.has_vehicle_subtype:
            self.pv |= (1 << 4)
        
        if self.has_requested_handover_loi:
            self.pv |= (1 << 5)
        
        if self.has_requested_handover_access:
            self.pv |= (1 << 6)
        
        if self.has_requested_flight_mode:
            self.pv |= (1 << 7)
        
        if self.has_controlled_station_1_16:
            self.pv |= (1 << 8)
        
        if self.has_component_number:
            self.pv |= (1 << 9)
        
        if self.has_sub_component_number:
            self.pv |= (1 << 10)
        
        if self.has_payload_type:
            self.pv |= (1 << 11)
        
        if self.has_asset_mode:
            self.pv |= (1 << 12)
        
        if self.has_wait_for_vehicle_data_link_transition_coordination_message:
            self.pv |= (1 << 13)
        
        if self.has_cucs_type:
            self.pv |= (1 << 14)
        
        if self.has_cucs_subtype:
            self.pv |= (1 << 15)
        
        if self.has_presence_vector_support:
            self.pv |= (1 << 16)
        
        if self.has_controlled_station_17_32:
            self.pv |= (1 << 17)
        

        # 2. Write PV
        
        
        
        cursor.write_uint24(self.pv)
        
        
        

        # 3. Write Fields
        
        if self.has_time_stamp:
            cursor.write_uint40(self.time_stamp)
        
        if self.has_vsm_id:
            cursor.write_uint32(self.vsm_id)
        
        if self.has_data_link_id:
            cursor.write_uint32(self.data_link_id)
        
        if self.has_vehicle_type:
            cursor.write_uint16(self.vehicle_type)
        
        if self.has_vehicle_subtype:
            cursor.write_uint16(self.vehicle_subtype)
        
        if self.has_requested_handover_loi:
            cursor.write_uint8(self.requested_handover_loi)
        
        if self.has_requested_handover_access:
            cursor.write_uint8(self.requested_handover_access)
        
        if self.has_requested_flight_mode:
            cursor.write_uint8(self.requested_flight_mode)
        
        if self.has_controlled_station_1_16:
            cursor.write_uint16(self.controlled_station_1_16)
        
        if self.has_component_number:
            cursor.write_uint16(self.component_number)
        
        if self.has_sub_component_number:
            cursor.write_uint16(self.sub_component_number)
        
        if self.has_payload_type:
            cursor.write_uint8(self.payload_type)
        
        if self.has_asset_mode:
            cursor.write_uint8(self.asset_mode)
        
        if self.has_wait_for_vehicle_data_link_transition_coordination_message:
            cursor.write_uint8(self.wait_for_vehicle_data_link_transition_coordination_message)
        
        if self.has_cucs_type:
            cursor.write_uint8(self.cucs_type)
        
        if self.has_cucs_subtype:
            cursor.write_uint16(self.cucs_subtype)
        
        if self.has_presence_vector_support:
            cursor.write_uint8(self.presence_vector_support)
        
        if self.has_controlled_station_17_32:
            cursor.write_uint16(self.controlled_station_17_32)
        

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
            self.has_requested_handover_loi = True
            self.requested_handover_loi = cursor.read_uint8()
        else:
            self.has_requested_handover_loi = False
        
        if self.pv & (1 << 6):
            self.has_requested_handover_access = True
            self.requested_handover_access = cursor.read_uint8()
        else:
            self.has_requested_handover_access = False
        
        if self.pv & (1 << 7):
            self.has_requested_flight_mode = True
            self.requested_flight_mode = cursor.read_uint8()
        else:
            self.has_requested_flight_mode = False
        
        if self.pv & (1 << 8):
            self.has_controlled_station_1_16 = True
            self.controlled_station_1_16 = cursor.read_uint16()
        else:
            self.has_controlled_station_1_16 = False
        
        if self.pv & (1 << 9):
            self.has_component_number = True
            self.component_number = cursor.read_uint16()
        else:
            self.has_component_number = False
        
        if self.pv & (1 << 10):
            self.has_sub_component_number = True
            self.sub_component_number = cursor.read_uint16()
        else:
            self.has_sub_component_number = False
        
        if self.pv & (1 << 11):
            self.has_payload_type = True
            self.payload_type = cursor.read_uint8()
        else:
            self.has_payload_type = False
        
        if self.pv & (1 << 12):
            self.has_asset_mode = True
            self.asset_mode = cursor.read_uint8()
        else:
            self.has_asset_mode = False
        
        if self.pv & (1 << 13):
            self.has_wait_for_vehicle_data_link_transition_coordination_message = True
            self.wait_for_vehicle_data_link_transition_coordination_message = cursor.read_uint8()
        else:
            self.has_wait_for_vehicle_data_link_transition_coordination_message = False
        
        if self.pv & (1 << 14):
            self.has_cucs_type = True
            self.cucs_type = cursor.read_uint8()
        else:
            self.has_cucs_type = False
        
        if self.pv & (1 << 15):
            self.has_cucs_subtype = True
            self.cucs_subtype = cursor.read_uint16()
        else:
            self.has_cucs_subtype = False
        
        if self.pv & (1 << 16):
            self.has_presence_vector_support = True
            self.presence_vector_support = cursor.read_uint8()
        else:
            self.has_presence_vector_support = False
        
        if self.pv & (1 << 17):
            self.has_controlled_station_17_32 = True
            self.controlled_station_17_32 = cursor.read_uint16()
        else:
            self.has_controlled_station_17_32 = False
        

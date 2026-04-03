-- STANAG 4586 DLI Dissector (Auto-generated)
local dli_proto = Proto('dli', 'STANAG 4586 DLI')

-- Compatibility: Find bit library
local bit = bit32 or bit or require('bit')

-- Decoding Helpers
function decode_bam(val, bits, min_val, max_val)
    local range = max_val - min_val
    local max_int = math.pow(2, bits)
    return min_val + (val / max_int) * range
end

function decode_scaled(val, scale, offset)
    return (val * scale) + offset
end

local f = dli_proto.fields
f.res1 = ProtoField.uint16('dli.res1', 'Reserved 1', base.HEX)
f.len  = ProtoField.uint16('dli.len',  'Payload Length', base.DEC)
f.src  = ProtoField.uint32('dli.src',  'Source ID', base.DEC)
f.dst  = ProtoField.uint32('dli.dst',  'Destination ID', base.DEC)
f.type = ProtoField.uint16('dli.type', 'Message Type', base.DEC)
f.prop = ProtoField.uint16('dli.prop', 'Message Properties', base.HEX)
f.res2 = ProtoField.uint32('dli.res2', 'Reserved 2', base.HEX)

-- Fields for 1 CUCSAuthorisationRequest
f.CUCSAuthorisationRequest_time_stamp = ProtoField.uint64('dli.CUCSAuthorisationRequest.time_stamp', 'time_stamp', base.DEC)
f.CUCSAuthorisationRequest_vsm_id = ProtoField.uint32('dli.CUCSAuthorisationRequest.vsm_id', 'vsm_id', base.DEC)
f.CUCSAuthorisationRequest_data_link_id = ProtoField.uint32('dli.CUCSAuthorisationRequest.data_link_id', 'data_link_id', base.DEC)
f.CUCSAuthorisationRequest_vehicle_type = ProtoField.uint16('dli.CUCSAuthorisationRequest.vehicle_type', 'vehicle_type', base.DEC)
f.CUCSAuthorisationRequest_vehicle_subtype = ProtoField.uint16('dli.CUCSAuthorisationRequest.vehicle_subtype', 'vehicle_subtype', base.DEC)
f.CUCSAuthorisationRequest_requested_handover_loi = ProtoField.uint8('dli.CUCSAuthorisationRequest.requested_handover_loi', 'requested_handover_loi', base.DEC)
f.CUCSAuthorisationRequest_requested_handover_access = ProtoField.uint8('dli.CUCSAuthorisationRequest.requested_handover_access', 'requested_handover_access', base.DEC)
f.CUCSAuthorisationRequest_requested_flight_mode = ProtoField.uint8('dli.CUCSAuthorisationRequest.requested_flight_mode', 'requested_flight_mode', base.DEC)
f.CUCSAuthorisationRequest_controlled_stn_1_16 = ProtoField.uint16('dli.CUCSAuthorisationRequest.controlled_stn_1_16', 'controlled_stn_1_16', base.DEC)
f.CUCSAuthorisationRequest_component_number = ProtoField.uint16('dli.CUCSAuthorisationRequest.component_number', 'component_number', base.DEC)
f.CUCSAuthorisationRequest_sub_component_number = ProtoField.uint16('dli.CUCSAuthorisationRequest.sub_component_number', 'sub_component_number', base.DEC)
f.CUCSAuthorisationRequest_payload_type = ProtoField.uint8('dli.CUCSAuthorisationRequest.payload_type', 'payload_type', base.DEC)
f.CUCSAuthorisationRequest_asset_mode = ProtoField.uint8('dli.CUCSAuthorisationRequest.asset_mode', 'asset_mode', base.DEC)
f.CUCSAuthorisationRequest_wait_for_transition_coord = ProtoField.uint8('dli.CUCSAuthorisationRequest.wait_for_transition_coord', 'wait_for_transition_coord', base.DEC)
f.CUCSAuthorisationRequest_cucs_type = ProtoField.uint16('dli.CUCSAuthorisationRequest.cucs_type', 'cucs_type', base.DEC)
f.CUCSAuthorisationRequest_cucs_subtype = ProtoField.uint16('dli.CUCSAuthorisationRequest.cucs_subtype', 'cucs_subtype', base.DEC)
f.CUCSAuthorisationRequest_presence_vector_support = ProtoField.uint8('dli.CUCSAuthorisationRequest.presence_vector_support', 'presence_vector_support', base.DEC)
f.CUCSAuthorisationRequest_controlled_stn_17_32 = ProtoField.uint16('dli.CUCSAuthorisationRequest.controlled_stn_17_32', 'controlled_stn_17_32', base.DEC)
-- Fields for 2 VSMAuthorisationResponse
f.VSMAuthorisationResponse_time_stamp = ProtoField.uint64('dli.VSMAuthorisationResponse.time_stamp', 'time_stamp', base.DEC)
f.VSMAuthorisationResponse_vsm_id = ProtoField.uint32('dli.VSMAuthorisationResponse.vsm_id', 'vsm_id', base.DEC)
f.VSMAuthorisationResponse_data_link_id = ProtoField.uint32('dli.VSMAuthorisationResponse.data_link_id', 'data_link_id', base.DEC)
f.VSMAuthorisationResponse_access_authorized = ProtoField.uint8('dli.VSMAuthorisationResponse.access_authorized', 'access_authorized', base.DEC)
f.VSMAuthorisationResponse_access_granted = ProtoField.uint8('dli.VSMAuthorisationResponse.access_granted', 'access_granted', base.DEC)
f.VSMAuthorisationResponse_loi_authorized = ProtoField.uint8('dli.VSMAuthorisationResponse.loi_authorized', 'loi_authorized', base.DEC)
f.VSMAuthorisationResponse_loi_granted = ProtoField.uint8('dli.VSMAuthorisationResponse.loi_granted', 'loi_granted', base.DEC)
f.VSMAuthorisationResponse_flight_modes_granted = ProtoField.uint32('dli.VSMAuthorisationResponse.flight_modes_granted', 'flight_modes_granted', base.DEC)
f.VSMAuthorisationResponse_controlled_stn_1_16 = ProtoField.uint16('dli.VSMAuthorisationResponse.controlled_stn_1_16', 'controlled_stn_1_16', base.DEC)
f.VSMAuthorisationResponse_component_number = ProtoField.uint16('dli.VSMAuthorisationResponse.component_number', 'component_number', base.DEC)
f.VSMAuthorisationResponse_sub_component_number = ProtoField.uint16('dli.VSMAuthorisationResponse.sub_component_number', 'sub_component_number', base.DEC)
f.VSMAuthorisationResponse_payload_type = ProtoField.uint8('dli.VSMAuthorisationResponse.payload_type', 'payload_type', base.DEC)
f.VSMAuthorisationResponse_access_requested = ProtoField.uint8('dli.VSMAuthorisationResponse.access_requested', 'access_requested', base.DEC)
f.VSMAuthorisationResponse_vehicle_type = ProtoField.uint16('dli.VSMAuthorisationResponse.vehicle_type', 'vehicle_type', base.DEC)
f.VSMAuthorisationResponse_vehicle_subtype = ProtoField.uint16('dli.VSMAuthorisationResponse.vehicle_subtype', 'vehicle_subtype', base.DEC)
f.VSMAuthorisationResponse_cucs_type = ProtoField.uint8('dli.VSMAuthorisationResponse.cucs_type', 'cucs_type', base.DEC)
f.VSMAuthorisationResponse_cucs_subtype = ProtoField.uint8('dli.VSMAuthorisationResponse.cucs_subtype', 'cucs_subtype', base.DEC)
f.VSMAuthorisationResponse_presence_vector_support = ProtoField.uint8('dli.VSMAuthorisationResponse.presence_vector_support', 'presence_vector_support', base.DEC)
f.VSMAuthorisationResponse_controlled_stn_17_32 = ProtoField.uint16('dli.VSMAuthorisationResponse.controlled_stn_17_32', 'controlled_stn_17_32', base.DEC)
-- Fields for 3 VehicleID
f.VehicleID_time_stamp = ProtoField.uint64('dli.VehicleID.time_stamp', 'time_stamp', base.DEC)
f.VehicleID_vsm_id = ProtoField.uint32('dli.VehicleID.vsm_id', 'vsm_id', base.DEC)
f.VehicleID_vehicle_id_update = ProtoField.uint32('dli.VehicleID.vehicle_id_update', 'vehicle_id_update', base.DEC)
f.VehicleID_vehicle_type = ProtoField.uint16('dli.VehicleID.vehicle_type', 'vehicle_type', base.DEC)
f.VehicleID_vehicle_subtype = ProtoField.uint16('dli.VehicleID.vehicle_subtype', 'vehicle_subtype', base.DEC)
f.VehicleID_owning_id = ProtoField.uint8('dli.VehicleID.owning_id', 'owning_id', base.DEC)
f.VehicleID_tail_number = ProtoField.string('dli.VehicleID.tail_number', 'tail_number', base.ASCII)
f.VehicleID_mission_id = ProtoField.string('dli.VehicleID.mission_id', 'mission_id', base.ASCII)
f.VehicleID_atc_call_sign = ProtoField.string('dli.VehicleID.atc_call_sign', 'atc_call_sign', base.ASCII)
-- Fields for 4 PositiveHandoverAuthorisationRequest
f.PositiveHandoverAuthorisationRequest_time_stamp = ProtoField.uint64('dli.PositiveHandoverAuthorisationRequest.time_stamp', 'time_stamp', base.DEC)
f.PositiveHandoverAuthorisationRequest_vsm_id = ProtoField.uint32('dli.PositiveHandoverAuthorisationRequest.vsm_id', 'vsm_id', base.DEC)
f.PositiveHandoverAuthorisationRequest_data_link_id = ProtoField.uint32('dli.PositiveHandoverAuthorisationRequest.data_link_id', 'data_link_id', base.DEC)
f.PositiveHandoverAuthorisationRequest_vehicle_type = ProtoField.uint16('dli.PositiveHandoverAuthorisationRequest.vehicle_type', 'vehicle_type', base.DEC)
f.PositiveHandoverAuthorisationRequest_vehicle_subtype = ProtoField.uint16('dli.PositiveHandoverAuthorisationRequest.vehicle_subtype', 'vehicle_subtype', base.DEC)
f.PositiveHandoverAuthorisationRequest_requested_handover_loi = ProtoField.uint8('dli.PositiveHandoverAuthorisationRequest.requested_handover_loi', 'requested_handover_loi', base.DEC)
f.PositiveHandoverAuthorisationRequest_flight_mode_offset = ProtoField.uint8('dli.PositiveHandoverAuthorisationRequest.flight_mode_offset', 'flight_mode_offset', base.DEC)
f.PositiveHandoverAuthorisationRequest_requested_flight_mode = ProtoField.uint32('dli.PositiveHandoverAuthorisationRequest.requested_flight_mode', 'requested_flight_mode', base.DEC)
f.PositiveHandoverAuthorisationRequest_controlled_stn_1_16 = ProtoField.uint16('dli.PositiveHandoverAuthorisationRequest.controlled_stn_1_16', 'controlled_stn_1_16', base.DEC)
f.PositiveHandoverAuthorisationRequest_component_number = ProtoField.uint16('dli.PositiveHandoverAuthorisationRequest.component_number', 'component_number', base.DEC)
f.PositiveHandoverAuthorisationRequest_sub_component_number = ProtoField.uint16('dli.PositiveHandoverAuthorisationRequest.sub_component_number', 'sub_component_number', base.DEC)
f.PositiveHandoverAuthorisationRequest_requesting_cucs_type = ProtoField.uint8('dli.PositiveHandoverAuthorisationRequest.requesting_cucs_type', 'requesting_cucs_type', base.DEC)
f.PositiveHandoverAuthorisationRequest_requesting_cucs_subtype = ProtoField.uint8('dli.PositiveHandoverAuthorisationRequest.requesting_cucs_subtype', 'requesting_cucs_subtype', base.DEC)
f.PositiveHandoverAuthorisationRequest_requesting_cucs_id = ProtoField.uint32('dli.PositiveHandoverAuthorisationRequest.requesting_cucs_id', 'requesting_cucs_id', base.DEC)
f.PositiveHandoverAuthorisationRequest_presence_vector_support = ProtoField.uint8('dli.PositiveHandoverAuthorisationRequest.presence_vector_support', 'presence_vector_support', base.DEC)
f.PositiveHandoverAuthorisationRequest_controlled_stn_17_32 = ProtoField.uint16('dli.PositiveHandoverAuthorisationRequest.controlled_stn_17_32', 'controlled_stn_17_32', base.DEC)
-- Fields for 5 PositiveHandoverAuthorisationGranted
f.PositiveHandoverAuthorisationGranted_time_stamp = ProtoField.uint64('dli.PositiveHandoverAuthorisationGranted.time_stamp', 'time_stamp', base.DEC)
f.PositiveHandoverAuthorisationGranted_vsm_id = ProtoField.uint32('dli.PositiveHandoverAuthorisationGranted.vsm_id', 'vsm_id', base.DEC)
f.PositiveHandoverAuthorisationGranted_data_link_id = ProtoField.uint32('dli.PositiveHandoverAuthorisationGranted.data_link_id', 'data_link_id', base.DEC)
f.PositiveHandoverAuthorisationGranted_loi_authorized = ProtoField.uint8('dli.PositiveHandoverAuthorisationGranted.loi_authorized', 'loi_authorized', base.DEC)
f.PositiveHandoverAuthorisationGranted_flight_mode_offset = ProtoField.uint8('dli.PositiveHandoverAuthorisationGranted.flight_mode_offset', 'flight_mode_offset', base.DEC)
f.PositiveHandoverAuthorisationGranted_flight_modes_authorized = ProtoField.uint32('dli.PositiveHandoverAuthorisationGranted.flight_modes_authorized', 'flight_modes_authorized', base.DEC)
f.PositiveHandoverAuthorisationGranted_controlled_stn_1_16 = ProtoField.uint16('dli.PositiveHandoverAuthorisationGranted.controlled_stn_1_16', 'controlled_stn_1_16', base.DEC)
f.PositiveHandoverAuthorisationGranted_component_number = ProtoField.uint16('dli.PositiveHandoverAuthorisationGranted.component_number', 'component_number', base.DEC)
f.PositiveHandoverAuthorisationGranted_sub_component_number = ProtoField.uint16('dli.PositiveHandoverAuthorisationGranted.sub_component_number', 'sub_component_number', base.DEC)
f.PositiveHandoverAuthorisationGranted_vehicle_type = ProtoField.uint16('dli.PositiveHandoverAuthorisationGranted.vehicle_type', 'vehicle_type', base.DEC)
f.PositiveHandoverAuthorisationGranted_vehicle_subtype = ProtoField.uint16('dli.PositiveHandoverAuthorisationGranted.vehicle_subtype', 'vehicle_subtype', base.DEC)
f.PositiveHandoverAuthorisationGranted_cucs_type = ProtoField.uint8('dli.PositiveHandoverAuthorisationGranted.cucs_type', 'cucs_type', base.DEC)
f.PositiveHandoverAuthorisationGranted_cucs_subtype = ProtoField.uint8('dli.PositiveHandoverAuthorisationGranted.cucs_subtype', 'cucs_subtype', base.DEC)
f.PositiveHandoverAuthorisationGranted_presence_vector_support = ProtoField.uint8('dli.PositiveHandoverAuthorisationGranted.presence_vector_support', 'presence_vector_support', base.DEC)
f.PositiveHandoverAuthorisationGranted_controlled_stn_17_32 = ProtoField.uint16('dli.PositiveHandoverAuthorisationGranted.controlled_stn_17_32', 'controlled_stn_17_32', base.DEC)
-- Fields for 2007 UnmannedAircraftLights
f.UnmannedAircraftLights_time_stamp = ProtoField.uint64('dli.UnmannedAircraftLights.time_stamp', 'time_stamp', base.DEC)
f.UnmannedAircraftLights_ua_lights = ProtoField.uint8('dli.UnmannedAircraftLights.ua_lights', 'ua_lights', base.DEC)
-- Fields for 2010 UAStickCommand
f.UAStickCommand_time_stamp = ProtoField.uint64('dli.UAStickCommand.time_stamp', 'time_stamp', base.DEC)
f.UAStickCommand_lateral_stick = ProtoField.uint8('dli.UAStickCommand.lateral_stick', 'lateral_stick', base.DEC)
f.UAStickCommand_longitudinal_stick = ProtoField.uint8('dli.UAStickCommand.longitudinal_stick', 'longitudinal_stick', base.DEC)
f.UAStickCommand_rotational_stick = ProtoField.uint8('dli.UAStickCommand.rotational_stick', 'rotational_stick', base.DEC)
f.UAStickCommand_throttle_stick_eng1 = ProtoField.uint8('dli.UAStickCommand.throttle_stick_eng1', 'throttle_stick_eng1', base.DEC)
f.UAStickCommand_pitch_stick_eng1 = ProtoField.uint8('dli.UAStickCommand.pitch_stick_eng1', 'pitch_stick_eng1', base.DEC)
f.UAStickCommand_throttle_stick_eng2 = ProtoField.uint8('dli.UAStickCommand.throttle_stick_eng2', 'throttle_stick_eng2', base.DEC)
f.UAStickCommand_pitch_stick_eng2 = ProtoField.uint8('dli.UAStickCommand.pitch_stick_eng2', 'pitch_stick_eng2', base.DEC)
f.UAStickCommand_throttle_stick_eng3 = ProtoField.uint8('dli.UAStickCommand.throttle_stick_eng3', 'throttle_stick_eng3', base.DEC)
f.UAStickCommand_pitch_stick_eng3 = ProtoField.uint8('dli.UAStickCommand.pitch_stick_eng3', 'pitch_stick_eng3', base.DEC)
f.UAStickCommand_throttle_stick_eng4 = ProtoField.uint8('dli.UAStickCommand.throttle_stick_eng4', 'throttle_stick_eng4', base.DEC)
f.UAStickCommand_pitch_stick_eng4 = ProtoField.uint8('dli.UAStickCommand.pitch_stick_eng4', 'pitch_stick_eng4', base.DEC)
f.UAStickCommand_taxi_stick = ProtoField.uint8('dli.UAStickCommand.taxi_stick', 'taxi_stick', base.DEC)
-- Fields for 2016 VehicleOperatingModeCommand
f.VehicleOperatingModeCommand_time_stamp = ProtoField.uint64('dli.VehicleOperatingModeCommand.time_stamp', 'time_stamp', base.DEC)
f.VehicleOperatingModeCommand_flight_path_control_mode = ProtoField.uint8('dli.VehicleOperatingModeCommand.flight_path_control_mode', 'flight_path_control_mode', base.DEC)
f.VehicleOperatingModeCommand_altitude_command_type = ProtoField.uint8('dli.VehicleOperatingModeCommand.altitude_command_type', 'altitude_command_type', base.DEC)
f.VehicleOperatingModeCommand_commanded_altitude = ProtoField.uint32('dli.VehicleOperatingModeCommand.commanded_altitude', 'commanded_altitude', base.DEC)
f.VehicleOperatingModeCommand_commanded_vertical_speed = ProtoField.uint16('dli.VehicleOperatingModeCommand.commanded_vertical_speed', 'commanded_vertical_speed', base.DEC)
f.VehicleOperatingModeCommand_heading_command_type = ProtoField.uint8('dli.VehicleOperatingModeCommand.heading_command_type', 'heading_command_type', base.DEC)
f.VehicleOperatingModeCommand_heading_reference = ProtoField.uint8('dli.VehicleOperatingModeCommand.heading_reference', 'heading_reference', base.DEC)
f.VehicleOperatingModeCommand_commanded_heading = ProtoField.uint16('dli.VehicleOperatingModeCommand.commanded_heading', 'commanded_heading', base.DEC)
f.VehicleOperatingModeCommand_commanded_course = ProtoField.uint16('dli.VehicleOperatingModeCommand.commanded_course', 'commanded_course', base.DEC)
f.VehicleOperatingModeCommand_commanded_turn_rate = ProtoField.uint16('dli.VehicleOperatingModeCommand.commanded_turn_rate', 'commanded_turn_rate', base.DEC)
f.VehicleOperatingModeCommand_commanded_roll_rate = ProtoField.uint16('dli.VehicleOperatingModeCommand.commanded_roll_rate', 'commanded_roll_rate', base.DEC)
f.VehicleOperatingModeCommand_commanded_roll = ProtoField.uint16('dli.VehicleOperatingModeCommand.commanded_roll', 'commanded_roll', base.DEC)
f.VehicleOperatingModeCommand_commanded_speed = ProtoField.uint16('dli.VehicleOperatingModeCommand.commanded_speed', 'commanded_speed', base.DEC)
f.VehicleOperatingModeCommand_speed_type = ProtoField.uint8('dli.VehicleOperatingModeCommand.speed_type', 'speed_type', base.DEC)
f.VehicleOperatingModeCommand_commanded_waypoint_number = ProtoField.uint16('dli.VehicleOperatingModeCommand.commanded_waypoint_number', 'commanded_waypoint_number', base.DEC)
f.VehicleOperatingModeCommand_altimeter_setting = ProtoField.uint16('dli.VehicleOperatingModeCommand.altimeter_setting', 'altimeter_setting', base.DEC)
f.VehicleOperatingModeCommand_altitude_type = ProtoField.uint8('dli.VehicleOperatingModeCommand.altitude_type', 'altitude_type', base.DEC)
f.VehicleOperatingModeCommand_loiter_latitude = ProtoField.uint32('dli.VehicleOperatingModeCommand.loiter_latitude', 'loiter_latitude', base.DEC)
f.VehicleOperatingModeCommand_loiter_longitude = ProtoField.uint32('dli.VehicleOperatingModeCommand.loiter_longitude', 'loiter_longitude', base.DEC)
f.VehicleOperatingModeCommand_loiter_altitude_change = ProtoField.uint8('dli.VehicleOperatingModeCommand.loiter_altitude_change', 'loiter_altitude_change', base.DEC)
f.VehicleOperatingModeCommand_thrust_direction = ProtoField.uint16('dli.VehicleOperatingModeCommand.thrust_direction', 'thrust_direction', base.DEC)
f.VehicleOperatingModeCommand_thrust = ProtoField.uint8('dli.VehicleOperatingModeCommand.thrust', 'thrust', base.DEC)
f.VehicleOperatingModeCommand_activity_id = ProtoField.uint32('dli.VehicleOperatingModeCommand.activity_id', 'activity_id', base.DEC)
-- Fields for 2017 LoiterConfiguration
f.LoiterConfiguration_time_stamp = ProtoField.uint64('dli.LoiterConfiguration.time_stamp', 'time_stamp', base.DEC)
f.LoiterConfiguration_loiter_type = ProtoField.uint8('dli.LoiterConfiguration.loiter_type', 'loiter_type', base.DEC)
f.LoiterConfiguration_loiter_radius = ProtoField.uint16('dli.LoiterConfiguration.loiter_radius', 'loiter_radius', base.DEC)
f.LoiterConfiguration_loiter_length = ProtoField.uint16('dli.LoiterConfiguration.loiter_length', 'loiter_length', base.DEC)
f.LoiterConfiguration_loiter_length_units = ProtoField.uint8('dli.LoiterConfiguration.loiter_length_units', 'loiter_length_units', base.DEC)
f.LoiterConfiguration_loiter_bearing = ProtoField.uint16('dli.LoiterConfiguration.loiter_bearing', 'loiter_bearing', base.DEC)
f.LoiterConfiguration_loiter_direction = ProtoField.uint8('dli.LoiterConfiguration.loiter_direction', 'loiter_direction', base.DEC)
f.LoiterConfiguration_flying_behaviour = ProtoField.uint8('dli.LoiterConfiguration.flying_behaviour', 'flying_behaviour', base.DEC)
f.LoiterConfiguration_loiter_duration = ProtoField.uint16('dli.LoiterConfiguration.loiter_duration', 'loiter_duration', base.DEC)
f.LoiterConfiguration_loiter_duration_units = ProtoField.uint8('dli.LoiterConfiguration.loiter_duration_units', 'loiter_duration_units', base.DEC)
f.LoiterConfiguration_activity_id = ProtoField.uint32('dli.LoiterConfiguration.activity_id', 'activity_id', base.DEC)
-- Fields for 3001 VehicleOperatingModeReport
f.VehicleOperatingModeReport_time_stamp = ProtoField.uint64('dli.VehicleOperatingModeReport.time_stamp', 'time_stamp', base.DEC)
f.VehicleOperatingModeReport_flight_path_control_mode = ProtoField.uint8('dli.VehicleOperatingModeReport.flight_path_control_mode', 'flight_path_control_mode', base.DEC)
-- Fields for 3002 VehicleOperatingStates
f.VehicleOperatingStates_time_stamp = ProtoField.uint64('dli.VehicleOperatingStates.time_stamp', 'time_stamp', base.DEC)
f.VehicleOperatingStates_commanded_altitude = ProtoField.uint32('dli.VehicleOperatingStates.commanded_altitude', 'commanded_altitude', base.DEC)
f.VehicleOperatingStates_altitude_type = ProtoField.uint8('dli.VehicleOperatingStates.altitude_type', 'altitude_type', base.DEC)
f.VehicleOperatingStates_commanded_heading = ProtoField.uint16('dli.VehicleOperatingStates.commanded_heading', 'commanded_heading', base.DEC)
f.VehicleOperatingStates_commanded_course = ProtoField.uint16('dli.VehicleOperatingStates.commanded_course', 'commanded_course', base.DEC)
f.VehicleOperatingStates_commanded_turn_rate = ProtoField.uint16('dli.VehicleOperatingStates.commanded_turn_rate', 'commanded_turn_rate', base.DEC)
f.VehicleOperatingStates_commanded_roll_rate = ProtoField.uint16('dli.VehicleOperatingStates.commanded_roll_rate', 'commanded_roll_rate', base.DEC)
f.VehicleOperatingStates_commanded_speed = ProtoField.uint16('dli.VehicleOperatingStates.commanded_speed', 'commanded_speed', base.DEC)
f.VehicleOperatingStates_speed_type = ProtoField.uint8('dli.VehicleOperatingStates.speed_type', 'speed_type', base.DEC)
f.VehicleOperatingStates_power_level = ProtoField.uint8('dli.VehicleOperatingStates.power_level', 'power_level', base.DEC)
f.VehicleOperatingStates_bingo_energy = ProtoField.uint16('dli.VehicleOperatingStates.bingo_energy', 'bingo_energy', base.DEC)
f.VehicleOperatingStates_current_energy_level = ProtoField.uint16('dli.VehicleOperatingStates.current_energy_level', 'current_energy_level', base.DEC)
f.VehicleOperatingStates_current_energy_usage = ProtoField.uint16('dli.VehicleOperatingStates.current_energy_usage', 'current_energy_usage', base.DEC)
f.VehicleOperatingStates_commanded_roll = ProtoField.uint16('dli.VehicleOperatingStates.commanded_roll', 'commanded_roll', base.DEC)
f.VehicleOperatingStates_altitude_command_type = ProtoField.uint8('dli.VehicleOperatingStates.altitude_command_type', 'altitude_command_type', base.DEC)
f.VehicleOperatingStates_heading_command_type = ProtoField.uint8('dli.VehicleOperatingStates.heading_command_type', 'heading_command_type', base.DEC)
f.VehicleOperatingStates_ua_state = ProtoField.uint8('dli.VehicleOperatingStates.ua_state', 'ua_state', base.DEC)
f.VehicleOperatingStates_thrust_direction = ProtoField.uint16('dli.VehicleOperatingStates.thrust_direction', 'thrust_direction', base.DEC)
-- Fields for 3004 LoiterConfigurationReport
f.LoiterConfigurationReport_time_stamp = ProtoField.uint64('dli.LoiterConfigurationReport.time_stamp', 'time_stamp', base.DEC)
f.LoiterConfigurationReport_loiter_type = ProtoField.uint8('dli.LoiterConfigurationReport.loiter_type', 'loiter_type', base.DEC)
f.LoiterConfigurationReport_loiter_radius = ProtoField.uint16('dli.LoiterConfigurationReport.loiter_radius', 'loiter_radius', base.DEC)
f.LoiterConfigurationReport_loiter_length = ProtoField.uint16('dli.LoiterConfigurationReport.loiter_length', 'loiter_length', base.DEC)
f.LoiterConfigurationReport_loiter_length_units = ProtoField.uint8('dli.LoiterConfigurationReport.loiter_length_units', 'loiter_length_units', base.DEC)
f.LoiterConfigurationReport_loiter_bearing = ProtoField.uint16('dli.LoiterConfigurationReport.loiter_bearing', 'loiter_bearing', base.DEC)
f.LoiterConfigurationReport_loiter_direction = ProtoField.uint8('dli.LoiterConfigurationReport.loiter_direction', 'loiter_direction', base.DEC)
f.LoiterConfigurationReport_loiter_altitude = ProtoField.uint32('dli.LoiterConfigurationReport.loiter_altitude', 'loiter_altitude', base.DEC)
f.LoiterConfigurationReport_altitude_type = ProtoField.uint8('dli.LoiterConfigurationReport.altitude_type', 'altitude_type', base.DEC)
f.LoiterConfigurationReport_loiter_speed = ProtoField.uint16('dli.LoiterConfigurationReport.loiter_speed', 'loiter_speed', base.DEC)
-- Fields for 3006 VehicleLightsState
f.VehicleLightsState_time_stamp = ProtoField.uint64('dli.VehicleLightsState.time_stamp', 'time_stamp', base.DEC)
f.VehicleLightsState_lights_state = ProtoField.uint8('dli.VehicleLightsState.lights_state', 'lights_state', base.DEC)
-- Fields for 3011 UAStickStatus
f.UAStickStatus_time_stamp = ProtoField.uint64('dli.UAStickStatus.time_stamp', 'time_stamp', base.DEC)
f.UAStickStatus_lateral_stick = ProtoField.uint8('dli.UAStickStatus.lateral_stick', 'lateral_stick', base.DEC)
f.UAStickStatus_longitudinal_stick = ProtoField.uint8('dli.UAStickStatus.longitudinal_stick', 'longitudinal_stick', base.DEC)
f.UAStickStatus_rotational_stick = ProtoField.uint8('dli.UAStickStatus.rotational_stick', 'rotational_stick', base.DEC)
f.UAStickStatus_throttle_stick_eng1 = ProtoField.uint8('dli.UAStickStatus.throttle_stick_eng1', 'throttle_stick_eng1', base.DEC)
f.UAStickStatus_pitch_stick_eng1 = ProtoField.uint8('dli.UAStickStatus.pitch_stick_eng1', 'pitch_stick_eng1', base.DEC)
f.UAStickStatus_throttle_stick_eng2 = ProtoField.uint8('dli.UAStickStatus.throttle_stick_eng2', 'throttle_stick_eng2', base.DEC)
f.UAStickStatus_pitch_stick_eng2 = ProtoField.uint8('dli.UAStickStatus.pitch_stick_eng2', 'pitch_stick_eng2', base.DEC)
f.UAStickStatus_throttle_stick_eng3 = ProtoField.uint8('dli.UAStickStatus.throttle_stick_eng3', 'throttle_stick_eng3', base.DEC)
f.UAStickStatus_pitch_stick_eng3 = ProtoField.uint8('dli.UAStickStatus.pitch_stick_eng3', 'pitch_stick_eng3', base.DEC)
f.UAStickStatus_throttle_stick_eng4 = ProtoField.uint8('dli.UAStickStatus.throttle_stick_eng4', 'throttle_stick_eng4', base.DEC)
f.UAStickStatus_pitch_stick_eng4 = ProtoField.uint8('dli.UAStickStatus.pitch_stick_eng4', 'pitch_stick_eng4', base.DEC)
f.UAStickStatus_taxi_stick = ProtoField.uint8('dli.UAStickStatus.taxi_stick', 'taxi_stick', base.DEC)
-- Fields for 4000 InertialStates
f.InertialStates_time_stamp = ProtoField.uint64('dli.InertialStates.time_stamp', 'time_stamp', base.DEC)
f.InertialStates_position_latitude = ProtoField.uint32('dli.InertialStates_position.latitude', 'latitude', base.DEC)
f.InertialStates_position_longitude = ProtoField.uint32('dli.InertialStates_position.longitude', 'longitude', base.DEC)
f.InertialStates_position_altitude = ProtoField.uint32('dli.InertialStates_position.altitude', 'altitude', base.DEC)
f.InertialStates_altitude_type = ProtoField.uint8('dli.InertialStates.altitude_type', 'altitude_type', base.DEC)
f.InertialStates_u_speed = ProtoField.uint16('dli.InertialStates.u_speed', 'u_speed', base.DEC)
f.InertialStates_v_speed = ProtoField.uint16('dli.InertialStates.v_speed', 'v_speed', base.DEC)
f.InertialStates_w_speed = ProtoField.uint16('dli.InertialStates.w_speed', 'w_speed', base.DEC)
f.InertialStates_u_accel = ProtoField.uint16('dli.InertialStates.u_accel', 'u_accel', base.DEC)
f.InertialStates_v_accel = ProtoField.uint16('dli.InertialStates.v_accel', 'v_accel', base.DEC)
f.InertialStates_w_accel = ProtoField.uint16('dli.InertialStates.w_accel', 'w_accel', base.DEC)
f.InertialStates_roll = ProtoField.uint16('dli.InertialStates.roll', 'roll', base.DEC)
f.InertialStates_pitch = ProtoField.uint16('dli.InertialStates.pitch', 'pitch', base.DEC)
f.InertialStates_heading = ProtoField.uint16('dli.InertialStates.heading', 'heading', base.DEC)
f.InertialStates_roll_rate = ProtoField.uint16('dli.InertialStates.roll_rate', 'roll_rate', base.DEC)
f.InertialStates_pitch_rate = ProtoField.uint16('dli.InertialStates.pitch_rate', 'pitch_rate', base.DEC)
f.InertialStates_turn_rate = ProtoField.uint16('dli.InertialStates.turn_rate', 'turn_rate', base.DEC)
f.InertialStates_magnetic_variation = ProtoField.uint16('dli.InertialStates.magnetic_variation', 'magnetic_variation', base.DEC)
-- Fields for 4001 FromToNextWaypointStates
f.FromToNextWaypointStates_time_stamp = ProtoField.uint64('dli.FromToNextWaypointStates.time_stamp', 'time_stamp', base.DEC)
f.FromToNextWaypointStates_altitude_type = ProtoField.uint8('dli.FromToNextWaypointStates.altitude_type', 'altitude_type', base.DEC)
f.FromToNextWaypointStates_speed_type = ProtoField.uint8('dli.FromToNextWaypointStates.speed_type', 'speed_type', base.DEC)
f.FromToNextWaypointStates_from_waypoint_latitude = ProtoField.uint32('dli.FromToNextWaypointStates.from_waypoint_latitude', 'from_waypoint_latitude', base.DEC)
f.FromToNextWaypointStates_from_waypoint_longitude = ProtoField.uint32('dli.FromToNextWaypointStates.from_waypoint_longitude', 'from_waypoint_longitude', base.DEC)
f.FromToNextWaypointStates_from_waypoint_altitude = ProtoField.uint32('dli.FromToNextWaypointStates.from_waypoint_altitude', 'from_waypoint_altitude', base.DEC)
f.FromToNextWaypointStates_from_waypoint_time = ProtoField.uint64('dli.FromToNextWaypointStates.from_waypoint_time', 'from_waypoint_time', base.DEC)
f.FromToNextWaypointStates_from_waypoint_number = ProtoField.uint16('dli.FromToNextWaypointStates.from_waypoint_number', 'from_waypoint_number', base.DEC)
f.FromToNextWaypointStates_to_waypoint_latitude = ProtoField.uint32('dli.FromToNextWaypointStates.to_waypoint_latitude', 'to_waypoint_latitude', base.DEC)
f.FromToNextWaypointStates_to_waypoint_longitude = ProtoField.uint32('dli.FromToNextWaypointStates.to_waypoint_longitude', 'to_waypoint_longitude', base.DEC)
f.FromToNextWaypointStates_to_waypoint_altitude = ProtoField.uint32('dli.FromToNextWaypointStates.to_waypoint_altitude', 'to_waypoint_altitude', base.DEC)
f.FromToNextWaypointStates_to_waypoint_speed = ProtoField.uint16('dli.FromToNextWaypointStates.to_waypoint_speed', 'to_waypoint_speed', base.DEC)
f.FromToNextWaypointStates_to_waypoint_time = ProtoField.uint64('dli.FromToNextWaypointStates.to_waypoint_time', 'to_waypoint_time', base.DEC)
f.FromToNextWaypointStates_to_waypoint_number = ProtoField.uint16('dli.FromToNextWaypointStates.to_waypoint_number', 'to_waypoint_number', base.DEC)
f.FromToNextWaypointStates_next_waypoint_latitude = ProtoField.uint32('dli.FromToNextWaypointStates.next_waypoint_latitude', 'next_waypoint_latitude', base.DEC)
f.FromToNextWaypointStates_next_waypoint_longitude = ProtoField.uint32('dli.FromToNextWaypointStates.next_waypoint_longitude', 'next_waypoint_longitude', base.DEC)
f.FromToNextWaypointStates_next_waypoint_altitude = ProtoField.uint32('dli.FromToNextWaypointStates.next_waypoint_altitude', 'next_waypoint_altitude', base.DEC)
f.FromToNextWaypointStates_next_waypoint_speed = ProtoField.uint16('dli.FromToNextWaypointStates.next_waypoint_speed', 'next_waypoint_speed', base.DEC)
f.FromToNextWaypointStates_next_waypoint_time = ProtoField.uint64('dli.FromToNextWaypointStates.next_waypoint_time', 'next_waypoint_time', base.DEC)
f.FromToNextWaypointStates_next_waypoint_number = ProtoField.uint16('dli.FromToNextWaypointStates.next_waypoint_number', 'next_waypoint_number', base.DEC)
f.FromToNextWaypointStates_loiter_valid_for_to_wp = ProtoField.uint8('dli.FromToNextWaypointStates.loiter_valid_for_to_wp', 'loiter_valid_for_to_wp', base.DEC)
-- Fields for 13002 UAPositionWaypoint
f.UAPositionWaypoint_time_stamp = ProtoField.uint64('dli.UAPositionWaypoint.time_stamp', 'time_stamp', base.DEC)
f.UAPositionWaypoint_waypoint_number = ProtoField.uint16('dli.UAPositionWaypoint.waypoint_number', 'waypoint_number', base.DEC)
f.UAPositionWaypoint_waypoint_latitude = ProtoField.uint32('dli.UAPositionWaypoint.waypoint_latitude', 'waypoint_latitude', base.DEC)
f.UAPositionWaypoint_waypoint_longitude = ProtoField.uint32('dli.UAPositionWaypoint.waypoint_longitude', 'waypoint_longitude', base.DEC)
f.UAPositionWaypoint_location_type = ProtoField.uint8('dli.UAPositionWaypoint.location_type', 'location_type', base.DEC)
f.UAPositionWaypoint_waypoint_altitude = ProtoField.uint32('dli.UAPositionWaypoint.waypoint_altitude', 'waypoint_altitude', base.DEC)
f.UAPositionWaypoint_altitude_type = ProtoField.uint8('dli.UAPositionWaypoint.altitude_type', 'altitude_type', base.DEC)
f.UAPositionWaypoint_altitude_change = ProtoField.uint8('dli.UAPositionWaypoint.altitude_change', 'altitude_change', base.DEC)
f.UAPositionWaypoint_waypoint_speed = ProtoField.uint16('dli.UAPositionWaypoint.waypoint_speed', 'waypoint_speed', base.DEC)
f.UAPositionWaypoint_speed_type = ProtoField.uint8('dli.UAPositionWaypoint.speed_type', 'speed_type', base.DEC)
f.UAPositionWaypoint_next_waypoint = ProtoField.uint16('dli.UAPositionWaypoint.next_waypoint', 'next_waypoint', base.DEC)
f.UAPositionWaypoint_turn_type = ProtoField.uint8('dli.UAPositionWaypoint.turn_type', 'turn_type', base.DEC)
f.UAPositionWaypoint_optional_messages = ProtoField.uint8('dli.UAPositionWaypoint.optional_messages', 'optional_messages', base.DEC)
f.UAPositionWaypoint_waypoint_type = ProtoField.uint8('dli.UAPositionWaypoint.waypoint_type', 'waypoint_type', base.DEC)
f.UAPositionWaypoint_limit_type = ProtoField.uint8('dli.UAPositionWaypoint.limit_type', 'limit_type', base.DEC)
f.UAPositionWaypoint_loop_limit = ProtoField.uint16('dli.UAPositionWaypoint.loop_limit', 'loop_limit', base.DEC)
f.UAPositionWaypoint_activity_id = ProtoField.uint32('dli.UAPositionWaypoint.activity_id', 'activity_id', base.DEC)
-- Fields for 16002 Heartbeat
f.Heartbeat_time_stamp = ProtoField.uint64('dli.Heartbeat.time_stamp', 'time_stamp', base.DEC)
-- Fields for 17000 MessageAcknowledgement
f.MessageAcknowledgement_time_stamp = ProtoField.uint64('dli.MessageAcknowledgement.time_stamp', 'time_stamp', base.DEC)
f.MessageAcknowledgement_original_time_stamp = ProtoField.uint64('dli.MessageAcknowledgement.original_time_stamp', 'original_time_stamp', base.DEC)
f.MessageAcknowledgement_original_message_type = ProtoField.uint16('dli.MessageAcknowledgement.original_message_type', 'original_message_type', base.DEC)
f.MessageAcknowledgement_acknowledgement_type = ProtoField.uint8('dli.MessageAcknowledgement.acknowledgement_type', 'acknowledgement_type', base.DEC)

function dli_proto.dissector(buffer, pinfo, tree)
    local length = buffer:len()
    if length < 20 then return end

    pinfo.cols.protocol = 'DLI'
    local subtree = tree:add(dli_proto, buffer(), 'STANAG 4586 DLI Packet')

    subtree:add(f.res1, buffer(0, 2))
    subtree:add(f.len,  buffer(2, 2))
    subtree:add(f.src,  buffer(4, 4))
    subtree:add(f.dst,  buffer(8, 4))
    local msg_type = buffer(12, 2):uint()
    subtree:add(f.type, buffer(12, 2))
    subtree:add(f.prop, buffer(14, 2))
    subtree:add(f.res2, buffer(16, 4))

    local payload_len = buffer(2, 2):uint()
    if payload_len > 0 and length >= 20 + payload_len then
        local pay_tree = subtree:add(dli_proto, buffer(20, payload_len), 'Payload')
        local offset = 20

        if msg_type == 1 then
            pinfo.cols.info = 'CUCSAuthorisationRequest'
            local pv = buffer(offset, 3):uint()
            pay_tree:add(buffer(offset, 3), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 3

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_time_stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_vsm_id, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_data_link_id, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_vehicle_type, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_vehicle_subtype, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_requested_handover_loi, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_requested_handover_access, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_requested_flight_mode, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_controlled_stn_1_16, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_component_number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_sub_component_number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_payload_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_asset_mode, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 13)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_wait_for_transition_coord, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 14)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_cucs_type, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 15)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_cucs_subtype, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 16)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_presence_vector_support, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 17)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_controlled_stn_17_32, buffer(offset, 2))
                offset = offset + 2
            end
        elseif msg_type == 2 then
            pinfo.cols.info = 'VSMAuthorisationResponse'
            local pv = buffer(offset, 3):uint()
            pay_tree:add(buffer(offset, 3), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 3

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_time_stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_vsm_id, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_data_link_id, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_access_authorized, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_access_granted, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_loi_authorized, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_loi_granted, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_flight_modes_granted, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_controlled_stn_1_16, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_component_number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_sub_component_number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_payload_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_access_requested, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 13)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_vehicle_type, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 14)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_vehicle_subtype, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 15)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_cucs_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 16)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_cucs_subtype, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 17)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_presence_vector_support, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 18)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_controlled_stn_17_32, buffer(offset, 2))
                offset = offset + 2
            end
        elseif msg_type == 3 then
            pinfo.cols.info = 'VehicleID'
            local pv = buffer(offset, 2):uint()
            pay_tree:add(buffer(offset, 2), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 2

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.VehicleID_time_stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.VehicleID_vsm_id, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.VehicleID_vehicle_id_update, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.VehicleID_vehicle_type, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.VehicleID_vehicle_subtype, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.VehicleID_owning_id, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.VehicleID_tail_number, buffer(offset, 16))
                offset = offset + 16
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.VehicleID_mission_id, buffer(offset, 20))
                offset = offset + 20
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.VehicleID_atc_call_sign, buffer(offset, 32))
                offset = offset + 32
            end
        elseif msg_type == 4 then
            pinfo.cols.info = 'PositiveHandoverAuthorisationRequest'
            local pv = buffer(offset, 2):uint()
            pay_tree:add(buffer(offset, 2), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 2

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_time_stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_vsm_id, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_data_link_id, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_vehicle_type, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_vehicle_subtype, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_requested_handover_loi, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_flight_mode_offset, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_requested_flight_mode, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_controlled_stn_1_16, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_component_number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_sub_component_number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_requesting_cucs_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_requesting_cucs_subtype, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 13)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_requesting_cucs_id, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 14)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_presence_vector_support, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 15)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_controlled_stn_17_32, buffer(offset, 2))
                offset = offset + 2
            end
        elseif msg_type == 5 then
            pinfo.cols.info = 'PositiveHandoverAuthorisationGranted'
            local pv = buffer(offset, 2):uint()
            pay_tree:add(buffer(offset, 2), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 2

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_time_stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_vsm_id, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_data_link_id, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_loi_authorized, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_flight_mode_offset, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_flight_modes_authorized, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_controlled_stn_1_16, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_component_number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_sub_component_number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_vehicle_type, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_vehicle_subtype, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_cucs_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_cucs_subtype, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 13)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_presence_vector_support, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 14)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_controlled_stn_17_32, buffer(offset, 2))
                offset = offset + 2
            end
        elseif msg_type == 2007 then
            pinfo.cols.info = 'UnmannedAircraftLights'
            local pv = buffer(offset, 1):uint()
            pay_tree:add(buffer(offset, 1), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 1

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.UnmannedAircraftLights_time_stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.UnmannedAircraftLights_ua_lights, buffer(offset, 1))
                offset = offset + 1
            end
        elseif msg_type == 2010 then
            pinfo.cols.info = 'UAStickCommand'
            local pv = buffer(offset, 2):uint()
            pay_tree:add(buffer(offset, 2), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 2

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.UAStickCommand_time_stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.UAStickCommand_lateral_stick, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.UAStickCommand_longitudinal_stick, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.UAStickCommand_rotational_stick, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.UAStickCommand_throttle_stick_eng1, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.UAStickCommand_pitch_stick_eng1, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.UAStickCommand_throttle_stick_eng2, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.UAStickCommand_pitch_stick_eng2, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.UAStickCommand_throttle_stick_eng3, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.UAStickCommand_pitch_stick_eng3, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.UAStickCommand_throttle_stick_eng4, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                pay_tree:add(f.UAStickCommand_pitch_stick_eng4, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.UAStickCommand_taxi_stick, buffer(offset, 1))
                offset = offset + 1
            end
        elseif msg_type == 2016 then
            pinfo.cols.info = 'VehicleOperatingModeCommand'
            local pv = buffer(offset, 3):uint()
            pay_tree:add(buffer(offset, 3), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 3

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_time_stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_flight_path_control_mode, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_altitude_command_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_commanded_altitude, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_commanded_vertical_speed, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_heading_command_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_heading_reference, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                local raw = buffer(offset, 2):uint()
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingModeCommand_commanded_heading, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                local raw = buffer(offset, 2):uint()
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingModeCommand_commanded_course, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_commanded_turn_rate, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_commanded_roll_rate, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                local raw = buffer(offset, 2):uint()
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingModeCommand_commanded_roll, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_commanded_speed, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 13)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_speed_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 14)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_commanded_waypoint_number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 15)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_altimeter_setting, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 16)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_altitude_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 17)) ~= 0 then
                local raw = buffer(offset, 4):uint()
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingModeCommand_loiter_latitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 18)) ~= 0 then
                local raw = buffer(offset, 4):uint()
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingModeCommand_loiter_longitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 19)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_loiter_altitude_change, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 20)) ~= 0 then
                local raw = buffer(offset, 2):uint()
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingModeCommand_thrust_direction, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 21)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_thrust, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 22)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_activity_id, buffer(offset, 4))
                offset = offset + 4
            end
        elseif msg_type == 2017 then
            pinfo.cols.info = 'LoiterConfiguration'
            local pv = buffer(offset, 2):uint()
            pay_tree:add(buffer(offset, 2), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 2

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.LoiterConfiguration_time_stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.LoiterConfiguration_loiter_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.LoiterConfiguration_loiter_radius, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.LoiterConfiguration_loiter_length, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.LoiterConfiguration_loiter_length_units, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                local raw = buffer(offset, 2):uint()
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.LoiterConfiguration_loiter_bearing, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.LoiterConfiguration_loiter_direction, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.LoiterConfiguration_flying_behaviour, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.LoiterConfiguration_loiter_duration, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.LoiterConfiguration_loiter_duration_units, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.LoiterConfiguration_activity_id, buffer(offset, 4))
                offset = offset + 4
            end
        elseif msg_type == 3001 then
            pinfo.cols.info = 'VehicleOperatingModeReport'
            local pv = buffer(offset, 1):uint()
            pay_tree:add(buffer(offset, 1), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 1

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeReport_time_stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeReport_flight_path_control_mode, buffer(offset, 1))
                offset = offset + 1
            end
        elseif msg_type == 3002 then
            pinfo.cols.info = 'VehicleOperatingStates'
            local pv = buffer(offset, 3):uint()
            pay_tree:add(buffer(offset, 3), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 3

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_time_stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_commanded_altitude, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_altitude_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                local raw = buffer(offset, 2):uint()
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingStates_commanded_heading, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                local raw = buffer(offset, 2):uint()
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingStates_commanded_course, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_commanded_turn_rate, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_commanded_roll_rate, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_commanded_speed, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_speed_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_power_level, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_bingo_energy, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_current_energy_level, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_current_energy_usage, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 13)) ~= 0 then
                local raw = buffer(offset, 2):uint()
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingStates_commanded_roll, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 14)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_altitude_command_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 15)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_heading_command_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 16)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_ua_state, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 17)) ~= 0 then
                local raw = buffer(offset, 2):uint()
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingStates_thrust_direction, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
        elseif msg_type == 3004 then
            pinfo.cols.info = 'LoiterConfigurationReport'
            local pv = buffer(offset, 2):uint()
            pay_tree:add(buffer(offset, 2), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 2

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_time_stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_loiter_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_loiter_radius, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_loiter_length, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_loiter_length_units, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                local raw = buffer(offset, 2):uint()
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.LoiterConfigurationReport_loiter_bearing, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_loiter_direction, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_loiter_altitude, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_altitude_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_loiter_speed, buffer(offset, 2))
                offset = offset + 2
            end
        elseif msg_type == 3006 then
            pinfo.cols.info = 'VehicleLightsState'
            local pv = buffer(offset, 1):uint()
            pay_tree:add(buffer(offset, 1), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 1

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.VehicleLightsState_time_stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.VehicleLightsState_lights_state, buffer(offset, 1))
                offset = offset + 1
            end
        elseif msg_type == 3011 then
            pinfo.cols.info = 'UAStickStatus'
            local pv = buffer(offset, 2):uint()
            pay_tree:add(buffer(offset, 2), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 2

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.UAStickStatus_time_stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.UAStickStatus_lateral_stick, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.UAStickStatus_longitudinal_stick, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.UAStickStatus_rotational_stick, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.UAStickStatus_throttle_stick_eng1, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.UAStickStatus_pitch_stick_eng1, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.UAStickStatus_throttle_stick_eng2, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.UAStickStatus_pitch_stick_eng2, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.UAStickStatus_throttle_stick_eng3, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.UAStickStatus_pitch_stick_eng3, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.UAStickStatus_throttle_stick_eng4, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                pay_tree:add(f.UAStickStatus_pitch_stick_eng4, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.UAStickStatus_taxi_stick, buffer(offset, 1))
                offset = offset + 1
            end
        elseif msg_type == 4000 then
            pinfo.cols.info = 'InertialStates'
            local pv = buffer(offset, 3):uint()
            pay_tree:add(buffer(offset, 3), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 3

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.InertialStates_time_stamp, buffer(offset, 5))
                offset = offset + 5
            end
            local raw = buffer(offset, 4):uint()
            local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
            pay_tree:add(f.InertialStates_position_latitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
            offset = offset + 4
            local raw = buffer(offset, 4):uint()
            local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
            pay_tree:add(f.InertialStates_position_longitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
            offset = offset + 4
            local raw = buffer(offset, 4):int()
            local eng = decode_scaled(raw, 0.01, 0.0)
            pay_tree:add(f.InertialStates_position_altitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.3f %s)', eng, 'm'))
            offset = offset + 4
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.InertialStates_altitude_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.InertialStates_u_speed, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.InertialStates_v_speed, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.InertialStates_w_speed, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.InertialStates_u_accel, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.InertialStates_v_accel, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.InertialStates_w_accel, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                local raw = buffer(offset, 2):uint()
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.InertialStates_roll, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                local raw = buffer(offset, 2):uint()
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.InertialStates_pitch, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 13)) ~= 0 then
                local raw = buffer(offset, 2):uint()
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.InertialStates_heading, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 14)) ~= 0 then
                pay_tree:add(f.InertialStates_roll_rate, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 15)) ~= 0 then
                pay_tree:add(f.InertialStates_pitch_rate, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 16)) ~= 0 then
                pay_tree:add(f.InertialStates_turn_rate, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 17)) ~= 0 then
                local raw = buffer(offset, 2):uint()
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.InertialStates_magnetic_variation, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
        elseif msg_type == 4001 then
            pinfo.cols.info = 'FromToNextWaypointStates'
            local pv = buffer(offset, 3):uint()
            pay_tree:add(buffer(offset, 3), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 3

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_time_stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_altitude_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_speed_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                local raw = buffer(offset, 4):uint()
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.FromToNextWaypointStates_from_waypoint_latitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                local raw = buffer(offset, 4):uint()
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.FromToNextWaypointStates_from_waypoint_longitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_from_waypoint_altitude, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_from_waypoint_time, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_from_waypoint_number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                local raw = buffer(offset, 4):uint()
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.FromToNextWaypointStates_to_waypoint_latitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                local raw = buffer(offset, 4):uint()
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.FromToNextWaypointStates_to_waypoint_longitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_to_waypoint_altitude, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_to_waypoint_speed, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_to_waypoint_time, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 13)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_to_waypoint_number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 14)) ~= 0 then
                local raw = buffer(offset, 4):uint()
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.FromToNextWaypointStates_next_waypoint_latitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 15)) ~= 0 then
                local raw = buffer(offset, 4):uint()
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.FromToNextWaypointStates_next_waypoint_longitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 16)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_next_waypoint_altitude, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 17)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_next_waypoint_speed, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 18)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_next_waypoint_time, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 19)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_next_waypoint_number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 20)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_loiter_valid_for_to_wp, buffer(offset, 1))
                offset = offset + 1
            end
        elseif msg_type == 13002 then
            pinfo.cols.info = 'UAPositionWaypoint'
            local pv = buffer(offset, 3):uint()
            pay_tree:add(buffer(offset, 3), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 3

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_time_stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_waypoint_number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                local raw = buffer(offset, 4):uint()
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.UAPositionWaypoint_waypoint_latitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                local raw = buffer(offset, 4):uint()
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.UAPositionWaypoint_waypoint_longitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_location_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_waypoint_altitude, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_altitude_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_altitude_change, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_waypoint_speed, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_speed_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_next_waypoint, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_turn_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_optional_messages, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 13)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_waypoint_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 14)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_limit_type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 15)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_loop_limit, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 16)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_activity_id, buffer(offset, 4))
                offset = offset + 4
            end
        elseif msg_type == 16002 then
            pinfo.cols.info = 'Heartbeat'
            local pv = buffer(offset, 1):uint()
            pay_tree:add(buffer(offset, 1), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 1

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.Heartbeat_time_stamp, buffer(offset, 5))
                offset = offset + 5
            end
        elseif msg_type == 17000 then
            pinfo.cols.info = 'MessageAcknowledgement'
            local pv = buffer(offset, 1):uint()
            pay_tree:add(buffer(offset, 1), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 1

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.MessageAcknowledgement_time_stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.MessageAcknowledgement_original_time_stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.MessageAcknowledgement_original_message_type, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.MessageAcknowledgement_acknowledgement_type, buffer(offset, 1))
                offset = offset + 1
            end
        end
    end
end

local udp_table = DissectorTable.get('udp.port')
udp_table:add(30001, dli_proto)
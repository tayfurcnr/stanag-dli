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

function read_uint_be(buffer, offset, size)
    local value = 0
    for i = 0, size - 1 do
        value = value * 256 + buffer(offset + i, 1):uint()
    end
    return value
end

function read_int_be(buffer, offset, size)
    local value = read_uint_be(buffer, offset, size)
    local sign_bit = math.pow(2, size * 8 - 1)
    if value >= sign_bit then
        value = value - math.pow(2, size * 8)
    end
    return value
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
f.CUCSAuthorisationRequest_Time Stamp = ProtoField.uint64('dli.CUCSAuthorisationRequest.Time Stamp', 'Time Stamp', base.DEC)
f.CUCSAuthorisationRequest_VSM ID = ProtoField.uint32('dli.CUCSAuthorisationRequest.VSM ID', 'VSM ID', base.DEC)
f.CUCSAuthorisationRequest_Data Link ID = ProtoField.uint32('dli.CUCSAuthorisationRequest.Data Link ID', 'Data Link ID', base.DEC)
f.CUCSAuthorisationRequest_Vehicle Type = ProtoField.uint16('dli.CUCSAuthorisationRequest.Vehicle Type', 'Vehicle Type', base.DEC)
f.CUCSAuthorisationRequest_Vehicle Subtype = ProtoField.uint16('dli.CUCSAuthorisationRequest.Vehicle Subtype', 'Vehicle Subtype', base.DEC)
f.CUCSAuthorisationRequest_Requested/Handover LOI = ProtoField.uint8('dli.CUCSAuthorisationRequest.Requested/Handover LOI', 'Requested/Handover LOI', base.DEC)
f.CUCSAuthorisationRequest_Requested/Handover Access = ProtoField.uint8('dli.CUCSAuthorisationRequest.Requested/Handover Access', 'Requested/Handover Access', base.DEC)
f.CUCSAuthorisationRequest_Requested Flight Mode = ProtoField.uint8('dli.CUCSAuthorisationRequest.Requested Flight Mode', 'Requested Flight Mode', base.DEC)
f.CUCSAuthorisationRequest_Controlled Station 1-16 = ProtoField.uint16('dli.CUCSAuthorisationRequest.Controlled Station 1-16', 'Controlled Station 1-16', base.DEC)
f.CUCSAuthorisationRequest_Component Number = ProtoField.uint16('dli.CUCSAuthorisationRequest.Component Number', 'Component Number', base.DEC)
f.CUCSAuthorisationRequest_Sub-Component Number = ProtoField.uint16('dli.CUCSAuthorisationRequest.Sub-Component Number', 'Sub-Component Number', base.DEC)
f.CUCSAuthorisationRequest_Payload Type = ProtoField.uint8('dli.CUCSAuthorisationRequest.Payload Type', 'Payload Type', base.DEC)
f.CUCSAuthorisationRequest_Asset Mode = ProtoField.uint8('dli.CUCSAuthorisationRequest.Asset Mode', 'Asset Mode', base.DEC)
f.CUCSAuthorisationRequest_Wait for Vehicle Data Link Transition Coordination Message = ProtoField.uint8('dli.CUCSAuthorisationRequest.Wait for Vehicle Data Link Transition Coordination Message', 'Wait for Vehicle Data Link Transition Coordination Message', base.DEC)
f.CUCSAuthorisationRequest_CUCS Type = ProtoField.uint8('dli.CUCSAuthorisationRequest.CUCS Type', 'CUCS Type', base.DEC)
f.CUCSAuthorisationRequest_CUCS Subtype = ProtoField.uint16('dli.CUCSAuthorisationRequest.CUCS Subtype', 'CUCS Subtype', base.DEC)
f.CUCSAuthorisationRequest_Presence Vector Support = ProtoField.uint8('dli.CUCSAuthorisationRequest.Presence Vector Support', 'Presence Vector Support', base.DEC)
f.CUCSAuthorisationRequest_Controlled Station 17-32 = ProtoField.uint16('dli.CUCSAuthorisationRequest.Controlled Station 17-32', 'Controlled Station 17-32', base.DEC)
-- Fields for 2 VSMAuthorisationResponse
f.VSMAuthorisationResponse_Time Stamp = ProtoField.uint64('dli.VSMAuthorisationResponse.Time Stamp', 'Time Stamp', base.DEC)
f.VSMAuthorisationResponse_VSM ID = ProtoField.uint32('dli.VSMAuthorisationResponse.VSM ID', 'VSM ID', base.DEC)
f.VSMAuthorisationResponse_Data Link ID = ProtoField.uint32('dli.VSMAuthorisationResponse.Data Link ID', 'Data Link ID', base.DEC)
f.VSMAuthorisationResponse_Access Authorized = ProtoField.uint8('dli.VSMAuthorisationResponse.Access Authorized', 'Access Authorized', base.DEC)
f.VSMAuthorisationResponse_Access Granted = ProtoField.uint8('dli.VSMAuthorisationResponse.Access Granted', 'Access Granted', base.DEC)
f.VSMAuthorisationResponse_LOI Authorized = ProtoField.uint8('dli.VSMAuthorisationResponse.LOI Authorized', 'LOI Authorized', base.DEC)
f.VSMAuthorisationResponse_LOI Granted = ProtoField.uint8('dli.VSMAuthorisationResponse.LOI Granted', 'LOI Granted', base.DEC)
f.VSMAuthorisationResponse_Flight Modes Granted = ProtoField.uint8('dli.VSMAuthorisationResponse.Flight Modes Granted', 'Flight Modes Granted', base.DEC)
f.VSMAuthorisationResponse_Controlled Station 1-16 = ProtoField.uint16('dli.VSMAuthorisationResponse.Controlled Station 1-16', 'Controlled Station 1-16', base.DEC)
f.VSMAuthorisationResponse_Component Number = ProtoField.uint16('dli.VSMAuthorisationResponse.Component Number', 'Component Number', base.DEC)
f.VSMAuthorisationResponse_Sub-Component Number = ProtoField.uint16('dli.VSMAuthorisationResponse.Sub-Component Number', 'Sub-Component Number', base.DEC)
f.VSMAuthorisationResponse_Payload Type = ProtoField.uint8('dli.VSMAuthorisationResponse.Payload Type', 'Payload Type', base.DEC)
f.VSMAuthorisationResponse_Access Requested = ProtoField.uint8('dli.VSMAuthorisationResponse.Access Requested', 'Access Requested', base.DEC)
f.VSMAuthorisationResponse_Vehicle Type = ProtoField.uint16('dli.VSMAuthorisationResponse.Vehicle Type', 'Vehicle Type', base.DEC)
f.VSMAuthorisationResponse_Vehicle Subtype = ProtoField.uint16('dli.VSMAuthorisationResponse.Vehicle Subtype', 'Vehicle Subtype', base.DEC)
f.VSMAuthorisationResponse_CUCS Type = ProtoField.uint8('dli.VSMAuthorisationResponse.CUCS Type', 'CUCS Type', base.DEC)
f.VSMAuthorisationResponse_CUCS Subtype = ProtoField.uint16('dli.VSMAuthorisationResponse.CUCS Subtype', 'CUCS Subtype', base.DEC)
f.VSMAuthorisationResponse_Presence Vector Support = ProtoField.uint8('dli.VSMAuthorisationResponse.Presence Vector Support', 'Presence Vector Support', base.DEC)
f.VSMAuthorisationResponse_Controlled Station 17-32 = ProtoField.uint16('dli.VSMAuthorisationResponse.Controlled Station 17-32', 'Controlled Station 17-32', base.DEC)
-- Fields for 3 VehicleID
f.VehicleID_Time Stamp = ProtoField.uint64('dli.VehicleID.Time Stamp', 'Time Stamp', base.DEC)
f.VehicleID_VSM ID = ProtoField.uint32('dli.VehicleID.VSM ID', 'VSM ID', base.DEC)
f.VehicleID_Vehicle ID Update = ProtoField.uint32('dli.VehicleID.Vehicle ID Update', 'Vehicle ID Update', base.DEC)
f.VehicleID_Vehicle Type = ProtoField.uint16('dli.VehicleID.Vehicle Type', 'Vehicle Type', base.DEC)
f.VehicleID_Vehicle Subtype = ProtoField.uint16('dli.VehicleID.Vehicle Subtype', 'Vehicle Subtype', base.DEC)
f.VehicleID_Owning ID = ProtoField.uint8('dli.VehicleID.Owning ID', 'Owning ID', base.DEC)
f.VehicleID_Tail Number = ProtoField.string('dli.VehicleID.Tail Number', 'Tail Number', base.ASCII)
f.VehicleID_Mission ID = ProtoField.string('dli.VehicleID.Mission ID', 'Mission ID', base.ASCII)
f.VehicleID_ATC Call Sign = ProtoField.string('dli.VehicleID.ATC Call Sign', 'ATC Call Sign', base.ASCII)
f.VehicleID_Configuration Checksum = ProtoField.uint16('dli.VehicleID.Configuration Checksum', 'Configuration Checksum', base.DEC)
-- Fields for 4 PositiveHandoverAuthorisationRequest
f.PositiveHandoverAuthorisationRequest_Time Stamp = ProtoField.uint64('dli.PositiveHandoverAuthorisationRequest.Time Stamp', 'Time Stamp', base.DEC)
f.PositiveHandoverAuthorisationRequest_VSM ID = ProtoField.uint32('dli.PositiveHandoverAuthorisationRequest.VSM ID', 'VSM ID', base.DEC)
f.PositiveHandoverAuthorisationRequest_Data Link ID = ProtoField.uint32('dli.PositiveHandoverAuthorisationRequest.Data Link ID', 'Data Link ID', base.DEC)
f.PositiveHandoverAuthorisationRequest_Vehicle Type = ProtoField.uint16('dli.PositiveHandoverAuthorisationRequest.Vehicle Type', 'Vehicle Type', base.DEC)
f.PositiveHandoverAuthorisationRequest_Vehicle Subtype = ProtoField.uint16('dli.PositiveHandoverAuthorisationRequest.Vehicle Subtype', 'Vehicle Subtype', base.DEC)
f.PositiveHandoverAuthorisationRequest_Requested/Handover LOI = ProtoField.uint8('dli.PositiveHandoverAuthorisationRequest.Requested/Handover LOI', 'Requested/Handover LOI', base.DEC)
f.PositiveHandoverAuthorisationRequest_Flight Mode Offset = ProtoField.uint8('dli.PositiveHandoverAuthorisationRequest.Flight Mode Offset', 'Flight Mode Offset', base.DEC)
f.PositiveHandoverAuthorisationRequest_Requested Flight Mode = ProtoField.uint32('dli.PositiveHandoverAuthorisationRequest.Requested Flight Mode', 'Requested Flight Mode', base.DEC)
f.PositiveHandoverAuthorisationRequest_Controlled Station 1-16 = ProtoField.uint16('dli.PositiveHandoverAuthorisationRequest.Controlled Station 1-16', 'Controlled Station 1-16', base.DEC)
f.PositiveHandoverAuthorisationRequest_Component Number = ProtoField.uint16('dli.PositiveHandoverAuthorisationRequest.Component Number', 'Component Number', base.DEC)
f.PositiveHandoverAuthorisationRequest_Sub-Component Number = ProtoField.uint16('dli.PositiveHandoverAuthorisationRequest.Sub-Component Number', 'Sub-Component Number', base.DEC)
f.PositiveHandoverAuthorisationRequest_Requesting CUCS Type = ProtoField.uint8('dli.PositiveHandoverAuthorisationRequest.Requesting CUCS Type', 'Requesting CUCS Type', base.DEC)
f.PositiveHandoverAuthorisationRequest_Requesting CUCS Subtype = ProtoField.uint16('dli.PositiveHandoverAuthorisationRequest.Requesting CUCS Subtype', 'Requesting CUCS Subtype', base.DEC)
f.PositiveHandoverAuthorisationRequest_Requesting CUCS ID = ProtoField.uint32('dli.PositiveHandoverAuthorisationRequest.Requesting CUCS ID', 'Requesting CUCS ID', base.DEC)
f.PositiveHandoverAuthorisationRequest_Presence Vector Support = ProtoField.uint8('dli.PositiveHandoverAuthorisationRequest.Presence Vector Support', 'Presence Vector Support', base.DEC)
f.PositiveHandoverAuthorisationRequest_Controlled Station 17-32 = ProtoField.uint16('dli.PositiveHandoverAuthorisationRequest.Controlled Station 17-32', 'Controlled Station 17-32', base.DEC)
-- Fields for 5 PositiveHandoverAuthorisationGranted
f.PositiveHandoverAuthorisationGranted_Time Stamp = ProtoField.uint64('dli.PositiveHandoverAuthorisationGranted.Time Stamp', 'Time Stamp', base.DEC)
f.PositiveHandoverAuthorisationGranted_VSM ID = ProtoField.uint32('dli.PositiveHandoverAuthorisationGranted.VSM ID', 'VSM ID', base.DEC)
f.PositiveHandoverAuthorisationGranted_Data Link ID = ProtoField.uint32('dli.PositiveHandoverAuthorisationGranted.Data Link ID', 'Data Link ID', base.DEC)
f.PositiveHandoverAuthorisationGranted_LOI Authorized = ProtoField.uint8('dli.PositiveHandoverAuthorisationGranted.LOI Authorized', 'LOI Authorized', base.DEC)
f.PositiveHandoverAuthorisationGranted_Flight Mode Offset = ProtoField.uint8('dli.PositiveHandoverAuthorisationGranted.Flight Mode Offset', 'Flight Mode Offset', base.DEC)
f.PositiveHandoverAuthorisationGranted_Flight Modes Authorized = ProtoField.uint32('dli.PositiveHandoverAuthorisationGranted.Flight Modes Authorized', 'Flight Modes Authorized', base.DEC)
f.PositiveHandoverAuthorisationGranted_Controlled Station 1 16 Authorized = ProtoField.uint16('dli.PositiveHandoverAuthorisationGranted.Controlled Station 1 16 Authorized', 'Controlled Station 1 16 Authorized', base.DEC)
f.PositiveHandoverAuthorisationGranted_Component Number Authorized = ProtoField.uint16('dli.PositiveHandoverAuthorisationGranted.Component Number Authorized', 'Component Number Authorized', base.DEC)
f.PositiveHandoverAuthorisationGranted_Sub-Component Number Authorized = ProtoField.uint16('dli.PositiveHandoverAuthorisationGranted.Sub-Component Number Authorized', 'Sub-Component Number Authorized', base.DEC)
f.PositiveHandoverAuthorisationGranted_Vehicle Type = ProtoField.uint16('dli.PositiveHandoverAuthorisationGranted.Vehicle Type', 'Vehicle Type', base.DEC)
f.PositiveHandoverAuthorisationGranted_Vehicle Subtype = ProtoField.uint16('dli.PositiveHandoverAuthorisationGranted.Vehicle Subtype', 'Vehicle Subtype', base.DEC)
f.PositiveHandoverAuthorisationGranted_Requesting CUCS Type = ProtoField.uint8('dli.PositiveHandoverAuthorisationGranted.Requesting CUCS Type', 'Requesting CUCS Type', base.DEC)
f.PositiveHandoverAuthorisationGranted_Requesting CUCS Subtype = ProtoField.uint16('dli.PositiveHandoverAuthorisationGranted.Requesting CUCS Subtype', 'Requesting CUCS Subtype', base.DEC)
f.PositiveHandoverAuthorisationGranted_Requesting CUCS ID = ProtoField.uint32('dli.PositiveHandoverAuthorisationGranted.Requesting CUCS ID', 'Requesting CUCS ID', base.DEC)
f.PositiveHandoverAuthorisationGranted_Presence Vector Support = ProtoField.uint8('dli.PositiveHandoverAuthorisationGranted.Presence Vector Support', 'Presence Vector Support', base.DEC)
f.PositiveHandoverAuthorisationGranted_Controlled Station 17-32 Authorized = ProtoField.uint16('dli.PositiveHandoverAuthorisationGranted.Controlled Station 17-32 Authorized', 'Controlled Station 17-32 Authorized', base.DEC)
-- Fields for 2000 VehicleConfigurationCommand
f.VehicleConfigurationCommand_Time Stamp = ProtoField.uint64('dli.VehicleConfigurationCommand.Time Stamp', 'Time Stamp', base.DEC)
f.VehicleConfigurationCommand_Energy Storage Unit = ProtoField.uint8('dli.VehicleConfigurationCommand.Energy Storage Unit', 'Energy Storage Unit', base.DEC)
f.VehicleConfigurationCommand_Initial Propulsion Energy = ProtoField.uint16('dli.VehicleConfigurationCommand.Initial Propulsion Energy', 'Initial Propulsion Energy', base.DEC)
-- Fields for 2007 UnmannedAircraftLights
f.UnmannedAircraftLights_Time Stamp = ProtoField.uint64('dli.UnmannedAircraftLights.Time Stamp', 'Time Stamp', base.DEC)
f.UnmannedAircraftLights_Set Lights = ProtoField.uint16('dli.UnmannedAircraftLights.Set Lights', 'Set Lights', base.DEC)
f.UnmannedAircraftLights_Activity ID = ProtoField.uint32('dli.UnmannedAircraftLights.Activity ID', 'Activity ID', base.DEC)
-- Fields for 2008 EngineCommand
f.EngineCommand_Time Stamp = ProtoField.uint64('dli.EngineCommand.Time Stamp', 'Time Stamp', base.DEC)
f.EngineCommand_Engine Number = ProtoField.uint8('dli.EngineCommand.Engine Number', 'Engine Number', base.DEC)
f.EngineCommand_Engine Command = ProtoField.uint8('dli.EngineCommand.Engine Command', 'Engine Command', base.DEC)
f.EngineCommand_Reverse Thrust Power = ProtoField.uint8('dli.EngineCommand.Reverse Thrust Power', 'Reverse Thrust Power', base.DEC)
f.EngineCommand_Reverse Thrust = ProtoField.uint8('dli.EngineCommand.Reverse Thrust', 'Reverse Thrust', base.DEC)
f.EngineCommand_Ignition Switch Power = ProtoField.uint8('dli.EngineCommand.Ignition Switch Power', 'Ignition Switch Power', base.DEC)
f.EngineCommand_Ignition Switch Activation = ProtoField.uint8('dli.EngineCommand.Ignition Switch Activation', 'Ignition Switch Activation', base.DEC)
f.EngineCommand_Activity ID = ProtoField.uint32('dli.EngineCommand.Activity ID', 'Activity ID', base.DEC)
-- Fields for 2010 UAStickCommand
f.UAStickCommand_Time Stamp = ProtoField.uint64('dli.UAStickCommand.Time Stamp', 'Time Stamp', base.DEC)
f.UAStickCommand_Lateral Stick = ProtoField.int8('dli.UAStickCommand.Lateral Stick', 'Lateral Stick', base.DEC)
f.UAStickCommand_Longitudinal Stick = ProtoField.int8('dli.UAStickCommand.Longitudinal Stick', 'Longitudinal Stick', base.DEC)
f.UAStickCommand_Rotational Stick (Rudder) = ProtoField.int8('dli.UAStickCommand.Rotational Stick (Rudder)', 'Rotational Stick (Rudder)', base.DEC)
f.UAStickCommand_Throttle Stick - Engine 1 = ProtoField.uint8('dli.UAStickCommand.Throttle Stick - Engine 1', 'Throttle Stick - Engine 1', base.DEC)
f.UAStickCommand_Pitch Stick - Engine 1 = ProtoField.int8('dli.UAStickCommand.Pitch Stick - Engine 1', 'Pitch Stick - Engine 1', base.DEC)
f.UAStickCommand_Throttle Stick - Engine 2 = ProtoField.uint8('dli.UAStickCommand.Throttle Stick - Engine 2', 'Throttle Stick - Engine 2', base.DEC)
f.UAStickCommand_Pitch Stick - Engine 2 = ProtoField.int8('dli.UAStickCommand.Pitch Stick - Engine 2', 'Pitch Stick - Engine 2', base.DEC)
f.UAStickCommand_Throttle Stick - Engine 3 = ProtoField.uint8('dli.UAStickCommand.Throttle Stick - Engine 3', 'Throttle Stick - Engine 3', base.DEC)
f.UAStickCommand_Pitch Stick - Engine 3 = ProtoField.int8('dli.UAStickCommand.Pitch Stick - Engine 3', 'Pitch Stick - Engine 3', base.DEC)
f.UAStickCommand_Throttle Stick - Engine 4 = ProtoField.uint8('dli.UAStickCommand.Throttle Stick - Engine 4', 'Throttle Stick - Engine 4', base.DEC)
f.UAStickCommand_Pitch Stick - Engine 4 = ProtoField.int8('dli.UAStickCommand.Pitch Stick - Engine 4', 'Pitch Stick - Engine 4', base.DEC)
f.UAStickCommand_Taxi Stick = ProtoField.int8('dli.UAStickCommand.Taxi Stick', 'Taxi Stick', base.DEC)
-- Fields for 2016 VehicleOperatingModeCommand
f.VehicleOperatingModeCommand_Time Stamp = ProtoField.uint64('dli.VehicleOperatingModeCommand.Time Stamp', 'Time Stamp', base.DEC)
f.VehicleOperatingModeCommand_Select Flight Path Control Mode = ProtoField.uint8('dli.VehicleOperatingModeCommand.Select Flight Path Control Mode', 'Select Flight Path Control Mode', base.DEC)
f.VehicleOperatingModeCommand_Altitude Command Type = ProtoField.uint8('dli.VehicleOperatingModeCommand.Altitude Command Type', 'Altitude Command Type', base.DEC)
f.VehicleOperatingModeCommand_Commanded Altitude = ProtoField.int32('dli.VehicleOperatingModeCommand.Commanded Altitude', 'Commanded Altitude', base.DEC)
f.VehicleOperatingModeCommand_Commanded Vertical Speed = ProtoField.int16('dli.VehicleOperatingModeCommand.Commanded Vertical Speed', 'Commanded Vertical Speed', base.DEC)
f.VehicleOperatingModeCommand_Heading Command Type = ProtoField.uint8('dli.VehicleOperatingModeCommand.Heading Command Type', 'Heading Command Type', base.DEC)
f.VehicleOperatingModeCommand_Heading Reference = ProtoField.uint8('dli.VehicleOperatingModeCommand.Heading Reference', 'Heading Reference', base.DEC)
f.VehicleOperatingModeCommand_Commanded Heading = ProtoField.uint16('dli.VehicleOperatingModeCommand.Commanded Heading', 'Commanded Heading', base.DEC)
f.VehicleOperatingModeCommand_Commanded Course = ProtoField.uint16('dli.VehicleOperatingModeCommand.Commanded Course', 'Commanded Course', base.DEC)
f.VehicleOperatingModeCommand_Commanded Turn Rate = ProtoField.int16('dli.VehicleOperatingModeCommand.Commanded Turn Rate', 'Commanded Turn Rate', base.DEC)
f.VehicleOperatingModeCommand_Commanded Roll Rate = ProtoField.int16('dli.VehicleOperatingModeCommand.Commanded Roll Rate', 'Commanded Roll Rate', base.DEC)
f.VehicleOperatingModeCommand_Commanded Roll = ProtoField.uint16('dli.VehicleOperatingModeCommand.Commanded Roll', 'Commanded Roll', base.DEC)
f.VehicleOperatingModeCommand_Commanded Speed = ProtoField.uint16('dli.VehicleOperatingModeCommand.Commanded Speed', 'Commanded Speed', base.DEC)
f.VehicleOperatingModeCommand_Speed Type = ProtoField.uint8('dli.VehicleOperatingModeCommand.Speed Type', 'Speed Type', base.DEC)
f.VehicleOperatingModeCommand_Commanded Waypoint Number = ProtoField.uint16('dli.VehicleOperatingModeCommand.Commanded Waypoint Number', 'Commanded Waypoint Number', base.DEC)
f.VehicleOperatingModeCommand_Altimeter Setting = ProtoField.uint16('dli.VehicleOperatingModeCommand.Altimeter Setting', 'Altimeter Setting', base.DEC)
f.VehicleOperatingModeCommand_Altitude Type = ProtoField.uint8('dli.VehicleOperatingModeCommand.Altitude Type', 'Altitude Type', base.DEC)
f.VehicleOperatingModeCommand_Loiter Position Latitude = ProtoField.uint32('dli.VehicleOperatingModeCommand.Loiter Position Latitude', 'Loiter Position Latitude', base.DEC)
f.VehicleOperatingModeCommand_Loiter Position Longitude = ProtoField.uint32('dli.VehicleOperatingModeCommand.Loiter Position Longitude', 'Loiter Position Longitude', base.DEC)
f.VehicleOperatingModeCommand_Loiter Altitude Change Behaviour = ProtoField.uint8('dli.VehicleOperatingModeCommand.Loiter Altitude Change Behaviour', 'Loiter Altitude Change Behaviour', base.DEC)
f.VehicleOperatingModeCommand_Thrust Direction = ProtoField.uint16('dli.VehicleOperatingModeCommand.Thrust Direction', 'Thrust Direction', base.DEC)
f.VehicleOperatingModeCommand_Thrust = ProtoField.uint8('dli.VehicleOperatingModeCommand.Thrust', 'Thrust', base.DEC)
f.VehicleOperatingModeCommand_Activity ID = ProtoField.uint32('dli.VehicleOperatingModeCommand.Activity ID', 'Activity ID', base.DEC)
-- Fields for 2017 LoiterConfiguration
f.LoiterConfiguration_Time Stamp = ProtoField.uint64('dli.LoiterConfiguration.Time Stamp', 'Time Stamp', base.DEC)
f.LoiterConfiguration_Loiter Type = ProtoField.uint8('dli.LoiterConfiguration.Loiter Type', 'Loiter Type', base.DEC)
f.LoiterConfiguration_Loiter Radius = ProtoField.uint16('dli.LoiterConfiguration.Loiter Radius', 'Loiter Radius', base.DEC)
f.LoiterConfiguration_Loiter Length = ProtoField.uint16('dli.LoiterConfiguration.Loiter Length', 'Loiter Length', base.DEC)
f.LoiterConfiguration_Loiter Length Units = ProtoField.uint8('dli.LoiterConfiguration.Loiter Length Units', 'Loiter Length Units', base.DEC)
f.LoiterConfiguration_Loiter Bearing = ProtoField.uint16('dli.LoiterConfiguration.Loiter Bearing', 'Loiter Bearing', base.DEC)
f.LoiterConfiguration_Loiter Direction = ProtoField.uint8('dli.LoiterConfiguration.Loiter Direction', 'Loiter Direction', base.DEC)
f.LoiterConfiguration_Flying Behaviour = ProtoField.uint8('dli.LoiterConfiguration.Flying Behaviour', 'Flying Behaviour', base.DEC)
f.LoiterConfiguration_Loiter Duration = ProtoField.uint16('dli.LoiterConfiguration.Loiter Duration', 'Loiter Duration', base.DEC)
f.LoiterConfiguration_Loiter Duration Units = ProtoField.uint8('dli.LoiterConfiguration.Loiter Duration Units', 'Loiter Duration Units', base.DEC)
f.LoiterConfiguration_Activity ID = ProtoField.uint32('dli.LoiterConfiguration.Activity ID', 'Activity ID', base.DEC)
-- Fields for 3001 VehicleOperatingModeReport
f.VehicleOperatingModeReport_Time Stamp = ProtoField.uint64('dli.VehicleOperatingModeReport.Time Stamp', 'Time Stamp', base.DEC)
f.VehicleOperatingModeReport_Select Flight Path Control Mode = ProtoField.uint8('dli.VehicleOperatingModeReport.Select Flight Path Control Mode', 'Select Flight Path Control Mode', base.DEC)
-- Fields for 3002 VehicleOperatingStates
f.VehicleOperatingStates_Time Stamp = ProtoField.uint64('dli.VehicleOperatingStates.Time Stamp', 'Time Stamp', base.DEC)
f.VehicleOperatingStates_Commanded Altitude = ProtoField.int32('dli.VehicleOperatingStates.Commanded Altitude', 'Commanded Altitude', base.DEC)
f.VehicleOperatingStates_Altitude Type = ProtoField.uint8('dli.VehicleOperatingStates.Altitude Type', 'Altitude Type', base.DEC)
f.VehicleOperatingStates_Commanded Heading = ProtoField.uint16('dli.VehicleOperatingStates.Commanded Heading', 'Commanded Heading', base.DEC)
f.VehicleOperatingStates_Commanded Course = ProtoField.uint16('dli.VehicleOperatingStates.Commanded Course', 'Commanded Course', base.DEC)
f.VehicleOperatingStates_Commanded Turn Rate = ProtoField.int16('dli.VehicleOperatingStates.Commanded Turn Rate', 'Commanded Turn Rate', base.DEC)
f.VehicleOperatingStates_Commanded Roll Rate = ProtoField.int16('dli.VehicleOperatingStates.Commanded Roll Rate', 'Commanded Roll Rate', base.DEC)
f.VehicleOperatingStates_Commanded Speed = ProtoField.uint16('dli.VehicleOperatingStates.Commanded Speed', 'Commanded Speed', base.DEC)
f.VehicleOperatingStates_Speed Type = ProtoField.uint8('dli.VehicleOperatingStates.Speed Type', 'Speed Type', base.DEC)
f.VehicleOperatingStates_Power Level = ProtoField.int8('dli.VehicleOperatingStates.Power Level', 'Power Level', base.DEC)
f.VehicleOperatingStates_Bingo Energy = ProtoField.uint16('dli.VehicleOperatingStates.Bingo Energy', 'Bingo Energy', base.DEC)
f.VehicleOperatingStates_Current Propulsion Energy Level = ProtoField.uint16('dli.VehicleOperatingStates.Current Propulsion Energy Level', 'Current Propulsion Energy Level', base.DEC)
f.VehicleOperatingStates_Current Propulsion Energy Usage Rate = ProtoField.uint16('dli.VehicleOperatingStates.Current Propulsion Energy Usage Rate', 'Current Propulsion Energy Usage Rate', base.DEC)
f.VehicleOperatingStates_Commanded Roll = ProtoField.uint16('dli.VehicleOperatingStates.Commanded Roll', 'Commanded Roll', base.DEC)
f.VehicleOperatingStates_Altitude Command Type = ProtoField.uint8('dli.VehicleOperatingStates.Altitude Command Type', 'Altitude Command Type', base.DEC)
f.VehicleOperatingStates_Heading Command Type = ProtoField.uint8('dli.VehicleOperatingStates.Heading Command Type', 'Heading Command Type', base.DEC)
f.VehicleOperatingStates_UA State = ProtoField.uint8('dli.VehicleOperatingStates.UA State', 'UA State', base.DEC)
f.VehicleOperatingStates_Thrust Direction = ProtoField.uint16('dli.VehicleOperatingStates.Thrust Direction', 'Thrust Direction', base.DEC)
f.VehicleOperatingStates_Thrust = ProtoField.uint8('dli.VehicleOperatingStates.Thrust', 'Thrust', base.DEC)
f.VehicleOperatingStates_Loiter & Waypoint Validity = ProtoField.uint8('dli.VehicleOperatingStates.Loiter & Waypoint Validity', 'Loiter & Waypoint Validity', base.DEC)
f.VehicleOperatingStates_Commanded Loiter Position Latitude = ProtoField.uint32('dli.VehicleOperatingStates.Commanded Loiter Position Latitude', 'Commanded Loiter Position Latitude', base.DEC)
f.VehicleOperatingStates_Commanded Loiter Position Longitude = ProtoField.uint32('dli.VehicleOperatingStates.Commanded Loiter Position Longitude', 'Commanded Loiter Position Longitude', base.DEC)
f.VehicleOperatingStates_Altitude Change Behaviour = ProtoField.uint8('dli.VehicleOperatingStates.Altitude Change Behaviour', 'Altitude Change Behaviour', base.DEC)
f.VehicleOperatingStates_Commanded Waypoint Number = ProtoField.uint16('dli.VehicleOperatingStates.Commanded Waypoint Number', 'Commanded Waypoint Number', base.DEC)
-- Fields for 3004 LoiterConfigurationReport
f.LoiterConfigurationReport_Time Stamp = ProtoField.uint64('dli.LoiterConfigurationReport.Time Stamp', 'Time Stamp', base.DEC)
f.LoiterConfigurationReport_Loiter Type = ProtoField.uint8('dli.LoiterConfigurationReport.Loiter Type', 'Loiter Type', base.DEC)
f.LoiterConfigurationReport_Loiter Radius = ProtoField.uint16('dli.LoiterConfigurationReport.Loiter Radius', 'Loiter Radius', base.DEC)
f.LoiterConfigurationReport_Loiter Length = ProtoField.uint16('dli.LoiterConfigurationReport.Loiter Length', 'Loiter Length', base.DEC)
f.LoiterConfigurationReport_Loiter Length Units = ProtoField.uint8('dli.LoiterConfigurationReport.Loiter Length Units', 'Loiter Length Units', base.DEC)
f.LoiterConfigurationReport_Loiter Bearing = ProtoField.uint16('dli.LoiterConfigurationReport.Loiter Bearing', 'Loiter Bearing', base.DEC)
f.LoiterConfigurationReport_Loiter Direction = ProtoField.uint8('dli.LoiterConfigurationReport.Loiter Direction', 'Loiter Direction', base.DEC)
f.LoiterConfigurationReport_Loiter Altitude = ProtoField.int32('dli.LoiterConfigurationReport.Loiter Altitude', 'Loiter Altitude', base.DEC)
f.LoiterConfigurationReport_Altitude Type = ProtoField.uint8('dli.LoiterConfigurationReport.Altitude Type', 'Altitude Type', base.DEC)
f.LoiterConfigurationReport_Loiter Speed = ProtoField.uint16('dli.LoiterConfigurationReport.Loiter Speed', 'Loiter Speed', base.DEC)
f.LoiterConfigurationReport_Speed Type = ProtoField.uint8('dli.LoiterConfigurationReport.Speed Type', 'Speed Type', base.DEC)
f.LoiterConfigurationReport_Flying Behaviour = ProtoField.uint8('dli.LoiterConfigurationReport.Flying Behaviour', 'Flying Behaviour', base.DEC)
f.LoiterConfigurationReport_Loiter Duration = ProtoField.uint16('dli.LoiterConfigurationReport.Loiter Duration', 'Loiter Duration', base.DEC)
f.LoiterConfigurationReport_Loiter Duration Units = ProtoField.uint8('dli.LoiterConfigurationReport.Loiter Duration Units', 'Loiter Duration Units', base.DEC)
-- Fields for 3006 VehicleLightsState
f.VehicleLightsState_Time Stamp = ProtoField.uint64('dli.VehicleLightsState.Time Stamp', 'Time Stamp', base.DEC)
f.VehicleLightsState_Navigation Lights State = ProtoField.uint16('dli.VehicleLightsState.Navigation Lights State', 'Navigation Lights State', base.DEC)
-- Fields for 3007 EngineOperatingStates
f.EngineOperatingStates_Time Stamp = ProtoField.uint64('dli.EngineOperatingStates.Time Stamp', 'Time Stamp', base.DEC)
f.EngineOperatingStates_Engine Number = ProtoField.uint16('dli.EngineOperatingStates.Engine Number', 'Engine Number', base.DEC)
f.EngineOperatingStates_Engine Status = ProtoField.uint8('dli.EngineOperatingStates.Engine Status', 'Engine Status', base.DEC)
f.EngineOperatingStates_Reported Engine Command = ProtoField.uint8('dli.EngineOperatingStates.Reported Engine Command', 'Reported Engine Command', base.DEC)
f.EngineOperatingStates_Reverse Thrust Power Status = ProtoField.uint8('dli.EngineOperatingStates.Reverse Thrust Power Status', 'Reverse Thrust Power Status', base.DEC)
f.EngineOperatingStates_Reported Reverse Thrust = ProtoField.uint8('dli.EngineOperatingStates.Reported Reverse Thrust', 'Reported Reverse Thrust', base.DEC)
f.EngineOperatingStates_Ignition Switch Power Status = ProtoField.uint8('dli.EngineOperatingStates.Ignition Switch Power Status', 'Ignition Switch Power Status', base.DEC)
f.EngineOperatingStates_Ignition Switch Activation = ProtoField.uint8('dli.EngineOperatingStates.Ignition Switch Activation', 'Ignition Switch Activation', base.DEC)
f.EngineOperatingStates_Engine Power Setting = ProtoField.uint16('dli.EngineOperatingStates.Engine Power Setting', 'Engine Power Setting', base.DEC)
f.EngineOperatingStates_Engine Speed 1 Type = ProtoField.uint8('dli.EngineOperatingStates.Engine Speed 1 Type', 'Engine Speed 1 Type', base.DEC)
f.EngineOperatingStates_Engine Speed 1 = ProtoField.uint16('dli.EngineOperatingStates.Engine Speed 1', 'Engine Speed 1', base.DEC)
f.EngineOperatingStates_Engine Speed 2 Type = ProtoField.uint8('dli.EngineOperatingStates.Engine Speed 2 Type', 'Engine Speed 2 Type', base.DEC)
f.EngineOperatingStates_Engine Speed 2 = ProtoField.uint16('dli.EngineOperatingStates.Engine Speed 2', 'Engine Speed 2', base.DEC)
f.EngineOperatingStates_Engine Speed 3 Type = ProtoField.uint8('dli.EngineOperatingStates.Engine Speed 3 Type', 'Engine Speed 3 Type', base.DEC)
f.EngineOperatingStates_Engine Speed 3 = ProtoField.uint16('dli.EngineOperatingStates.Engine Speed 3', 'Engine Speed 3', base.DEC)
f.EngineOperatingStates_Propeller Pitch Angle = ProtoField.int8('dli.EngineOperatingStates.Propeller Pitch Angle', 'Propeller Pitch Angle', base.DEC)
f.EngineOperatingStates_Output Power (Shaft Torque) Status = ProtoField.uint8('dli.EngineOperatingStates.Output Power (Shaft Torque) Status', 'Output Power (Shaft Torque) Status', base.DEC)
f.EngineOperatingStates_Engine Temperature 1 Type = ProtoField.uint8('dli.EngineOperatingStates.Engine Temperature 1 Type', 'Engine Temperature 1 Type', base.DEC)
f.EngineOperatingStates_Engine Temperature 1 = ProtoField.uint16('dli.EngineOperatingStates.Engine Temperature 1', 'Engine Temperature 1', base.DEC)
f.EngineOperatingStates_Engine Temperature 2 Type = ProtoField.uint8('dli.EngineOperatingStates.Engine Temperature 2 Type', 'Engine Temperature 2 Type', base.DEC)
f.EngineOperatingStates_Engine Temperature 2 = ProtoField.uint16('dli.EngineOperatingStates.Engine Temperature 2', 'Engine Temperature 2', base.DEC)
f.EngineOperatingStates_Engine Temperature 3 Type = ProtoField.uint8('dli.EngineOperatingStates.Engine Temperature 3 Type', 'Engine Temperature 3 Type', base.DEC)
f.EngineOperatingStates_Engine Temperature 3 = ProtoField.uint16('dli.EngineOperatingStates.Engine Temperature 3', 'Engine Temperature 3', base.DEC)
f.EngineOperatingStates_Engine Temperature 4 Type = ProtoField.uint8('dli.EngineOperatingStates.Engine Temperature 4 Type', 'Engine Temperature 4 Type', base.DEC)
f.EngineOperatingStates_Engine Temperature 4 = ProtoField.uint16('dli.EngineOperatingStates.Engine Temperature 4', 'Engine Temperature 4', base.DEC)
f.EngineOperatingStates_Engine Pressure 1 Type = ProtoField.uint8('dli.EngineOperatingStates.Engine Pressure 1 Type', 'Engine Pressure 1 Type', base.DEC)
f.EngineOperatingStates_Engine Pressure 1 = ProtoField.uint16('dli.EngineOperatingStates.Engine Pressure 1', 'Engine Pressure 1', base.DEC)
f.EngineOperatingStates_Engine Pressure 1 Status = ProtoField.uint8('dli.EngineOperatingStates.Engine Pressure 1 Status', 'Engine Pressure 1 Status', base.DEC)
f.EngineOperatingStates_Engine Pressure 2 Type = ProtoField.uint8('dli.EngineOperatingStates.Engine Pressure 2 Type', 'Engine Pressure 2 Type', base.DEC)
f.EngineOperatingStates_Engine Pressure 2 = ProtoField.uint16('dli.EngineOperatingStates.Engine Pressure 2', 'Engine Pressure 2', base.DEC)
f.EngineOperatingStates_Engine Pressure 2 Status = ProtoField.uint8('dli.EngineOperatingStates.Engine Pressure 2 Status', 'Engine Pressure 2 Status', base.DEC)
f.EngineOperatingStates_Fire Detection Sensor Status = ProtoField.uint8('dli.EngineOperatingStates.Fire Detection Sensor Status', 'Fire Detection Sensor Status', base.DEC)
f.EngineOperatingStates_Engine Energy Flow = ProtoField.uint32('dli.EngineOperatingStates.Engine Energy Flow', 'Engine Energy Flow', base.DEC)
f.EngineOperatingStates_Engine Body Temperature Status = ProtoField.uint8('dli.EngineOperatingStates.Engine Body Temperature Status', 'Engine Body Temperature Status', base.DEC)
f.EngineOperatingStates_Exhaust Gas Temperature Status = ProtoField.uint8('dli.EngineOperatingStates.Exhaust Gas Temperature Status', 'Exhaust Gas Temperature Status', base.DEC)
f.EngineOperatingStates_Coolant Temperature Status = ProtoField.uint8('dli.EngineOperatingStates.Coolant Temperature Status', 'Coolant Temperature Status', base.DEC)
f.EngineOperatingStates_Lubricant Temperature Status = ProtoField.uint8('dli.EngineOperatingStates.Lubricant Temperature Status', 'Lubricant Temperature Status', base.DEC)
-- Fields for 3011 UAStickStatus
f.UAStickStatus_Time Stamp = ProtoField.uint64('dli.UAStickStatus.Time Stamp', 'Time Stamp', base.DEC)
f.UAStickStatus_Lateral Stick = ProtoField.int8('dli.UAStickStatus.Lateral Stick', 'Lateral Stick', base.DEC)
f.UAStickStatus_Longitudinal Stick = ProtoField.int8('dli.UAStickStatus.Longitudinal Stick', 'Longitudinal Stick', base.DEC)
f.UAStickStatus_Rotational Stick (Rudder) = ProtoField.int8('dli.UAStickStatus.Rotational Stick (Rudder)', 'Rotational Stick (Rudder)', base.DEC)
f.UAStickStatus_Throttle Stick - Engine 1 = ProtoField.uint8('dli.UAStickStatus.Throttle Stick - Engine 1', 'Throttle Stick - Engine 1', base.DEC)
f.UAStickStatus_Pitch Stick - Engine 1 = ProtoField.int8('dli.UAStickStatus.Pitch Stick - Engine 1', 'Pitch Stick - Engine 1', base.DEC)
f.UAStickStatus_Throttle Stick - Engine 2 = ProtoField.uint8('dli.UAStickStatus.Throttle Stick - Engine 2', 'Throttle Stick - Engine 2', base.DEC)
f.UAStickStatus_Pitch Stick - Engine 2 = ProtoField.int8('dli.UAStickStatus.Pitch Stick - Engine 2', 'Pitch Stick - Engine 2', base.DEC)
f.UAStickStatus_Throttle Stick - Engine 3 = ProtoField.uint8('dli.UAStickStatus.Throttle Stick - Engine 3', 'Throttle Stick - Engine 3', base.DEC)
f.UAStickStatus_Pitch Stick - Engine 3 = ProtoField.int8('dli.UAStickStatus.Pitch Stick - Engine 3', 'Pitch Stick - Engine 3', base.DEC)
f.UAStickStatus_Throttle Stick - Engine 4 = ProtoField.uint8('dli.UAStickStatus.Throttle Stick - Engine 4', 'Throttle Stick - Engine 4', base.DEC)
f.UAStickStatus_Pitch Stick - Engine 4 = ProtoField.int8('dli.UAStickStatus.Pitch Stick - Engine 4', 'Pitch Stick - Engine 4', base.DEC)
f.UAStickStatus_Taxi Stick = ProtoField.int8('dli.UAStickStatus.Taxi Stick', 'Taxi Stick', base.DEC)
-- Fields for 4000 InertialStates
f.InertialStates_Time Stamp = ProtoField.uint64('dli.InertialStates.Time Stamp', 'Time Stamp', base.DEC)
f.InertialStates_Latitude = ProtoField.uint32('dli.InertialStates.Latitude', 'Latitude', base.DEC)
f.InertialStates_Longitude = ProtoField.uint32('dli.InertialStates.Longitude', 'Longitude', base.DEC)
f.InertialStates_Altitude = ProtoField.int32('dli.InertialStates.Altitude', 'Altitude', base.DEC)
f.InertialStates_Altitude Type = ProtoField.uint8('dli.InertialStates.Altitude Type', 'Altitude Type', base.DEC)
f.InertialStates_U_Speed = ProtoField.int16('dli.InertialStates.U_Speed', 'U_Speed', base.DEC)
f.InertialStates_V_Speed = ProtoField.int16('dli.InertialStates.V_Speed', 'V_Speed', base.DEC)
f.InertialStates_W_Speed = ProtoField.int16('dli.InertialStates.W_Speed', 'W_Speed', base.DEC)
f.InertialStates_U_Accel = ProtoField.int16('dli.InertialStates.U_Accel', 'U_Accel', base.DEC)
f.InertialStates_V_Accel = ProtoField.int16('dli.InertialStates.V_Accel', 'V_Accel', base.DEC)
f.InertialStates_W_Accel = ProtoField.int16('dli.InertialStates.W_Accel', 'W_Accel', base.DEC)
f.InertialStates_Roll = ProtoField.uint16('dli.InertialStates.Roll', 'Roll', base.DEC)
f.InertialStates_Pitch = ProtoField.uint16('dli.InertialStates.Pitch', 'Pitch', base.DEC)
f.InertialStates_Heading = ProtoField.uint16('dli.InertialStates.Heading', 'Heading', base.DEC)
f.InertialStates_Roll Rate = ProtoField.int16('dli.InertialStates.Roll Rate', 'Roll Rate', base.DEC)
f.InertialStates_Pitch Rate = ProtoField.int16('dli.InertialStates.Pitch Rate', 'Pitch Rate', base.DEC)
f.InertialStates_Turn Rate = ProtoField.int16('dli.InertialStates.Turn Rate', 'Turn Rate', base.DEC)
f.InertialStates_Magnetic Variation = ProtoField.uint16('dli.InertialStates.Magnetic Variation', 'Magnetic Variation', base.DEC)
-- Fields for 4001 FromToNextWaypointStates
f.FromToNextWaypointStates_Time Stamp = ProtoField.uint64('dli.FromToNextWaypointStates.Time Stamp', 'Time Stamp', base.DEC)
f.FromToNextWaypointStates_Altitude Type = ProtoField.uint8('dli.FromToNextWaypointStates.Altitude Type', 'Altitude Type', base.DEC)
f.FromToNextWaypointStates_Speed Type = ProtoField.uint8('dli.FromToNextWaypointStates.Speed Type', 'Speed Type', base.DEC)
f.FromToNextWaypointStates_From Waypoint – Latitude = ProtoField.uint32('dli.FromToNextWaypointStates.From Waypoint – Latitude', 'From Waypoint – Latitude', base.DEC)
f.FromToNextWaypointStates_From Waypoint – Longitude = ProtoField.uint32('dli.FromToNextWaypointStates.From Waypoint – Longitude', 'From Waypoint – Longitude', base.DEC)
f.FromToNextWaypointStates_From Waypoint Altitude = ProtoField.int32('dli.FromToNextWaypointStates.From Waypoint Altitude', 'From Waypoint Altitude', base.DEC)
f.FromToNextWaypointStates_From Waypoint Time = ProtoField.uint64('dli.FromToNextWaypointStates.From Waypoint Time', 'From Waypoint Time', base.DEC)
f.FromToNextWaypointStates_From Waypoint Number = ProtoField.uint16('dli.FromToNextWaypointStates.From Waypoint Number', 'From Waypoint Number', base.DEC)
f.FromToNextWaypointStates_To Waypoint – Latitude = ProtoField.uint32('dli.FromToNextWaypointStates.To Waypoint – Latitude', 'To Waypoint – Latitude', base.DEC)
f.FromToNextWaypointStates_To Waypoint – Longitude = ProtoField.uint32('dli.FromToNextWaypointStates.To Waypoint – Longitude', 'To Waypoint – Longitude', base.DEC)
f.FromToNextWaypointStates_To Waypoint Altitude = ProtoField.int32('dli.FromToNextWaypointStates.To Waypoint Altitude', 'To Waypoint Altitude', base.DEC)
f.FromToNextWaypointStates_To Waypoint Speed = ProtoField.uint16('dli.FromToNextWaypointStates.To Waypoint Speed', 'To Waypoint Speed', base.DEC)
f.FromToNextWaypointStates_To Waypoint Time = ProtoField.uint64('dli.FromToNextWaypointStates.To Waypoint Time', 'To Waypoint Time', base.DEC)
f.FromToNextWaypointStates_To Waypoint Number = ProtoField.uint16('dli.FromToNextWaypointStates.To Waypoint Number', 'To Waypoint Number', base.DEC)
f.FromToNextWaypointStates_Next Waypoint – Latitude = ProtoField.uint32('dli.FromToNextWaypointStates.Next Waypoint – Latitude', 'Next Waypoint – Latitude', base.DEC)
f.FromToNextWaypointStates_Next Waypoint – Longitude = ProtoField.uint32('dli.FromToNextWaypointStates.Next Waypoint – Longitude', 'Next Waypoint – Longitude', base.DEC)
f.FromToNextWaypointStates_Next Waypoint Altitude = ProtoField.int32('dli.FromToNextWaypointStates.Next Waypoint Altitude', 'Next Waypoint Altitude', base.DEC)
f.FromToNextWaypointStates_Next Waypoint Speed = ProtoField.uint16('dli.FromToNextWaypointStates.Next Waypoint Speed', 'Next Waypoint Speed', base.DEC)
f.FromToNextWaypointStates_Next Waypoint Time = ProtoField.uint64('dli.FromToNextWaypointStates.Next Waypoint Time', 'Next Waypoint Time', base.DEC)
f.FromToNextWaypointStates_Next Waypoint Number = ProtoField.uint16('dli.FromToNextWaypointStates.Next Waypoint Number', 'Next Waypoint Number', base.DEC)
f.FromToNextWaypointStates_Loiter Configuration Report Validity for “To Waypoint” = ProtoField.uint8('dli.FromToNextWaypointStates.Loiter Configuration Report Validity for “To Waypoint”', 'Loiter Configuration Report Validity for “To Waypoint”', base.DEC)
-- Fields for 13002 UAPositionWaypoint
f.UAPositionWaypoint_Time Stamp = ProtoField.uint64('dli.UAPositionWaypoint.Time Stamp', 'Time Stamp', base.DEC)
f.UAPositionWaypoint_Waypoint Number = ProtoField.uint16('dli.UAPositionWaypoint.Waypoint Number', 'Waypoint Number', base.DEC)
f.UAPositionWaypoint_Waypoint to Latitude or Relative Y = ProtoField.uint32('dli.UAPositionWaypoint.Waypoint to Latitude or Relative Y', 'Waypoint to Latitude or Relative Y', base.DEC)
f.UAPositionWaypoint_Waypoint to Longitude or Relative X = ProtoField.uint32('dli.UAPositionWaypoint.Waypoint to Longitude or Relative X', 'Waypoint to Longitude or Relative X', base.DEC)
f.UAPositionWaypoint_Location Type = ProtoField.uint8('dli.UAPositionWaypoint.Location Type', 'Location Type', base.DEC)
f.UAPositionWaypoint_Waypoint to Altitude = ProtoField.int32('dli.UAPositionWaypoint.Waypoint to Altitude', 'Waypoint to Altitude', base.DEC)
f.UAPositionWaypoint_Waypoint Altitude Type = ProtoField.uint8('dli.UAPositionWaypoint.Waypoint Altitude Type', 'Waypoint Altitude Type', base.DEC)
f.UAPositionWaypoint_Altitude Change Behaviour = ProtoField.uint8('dli.UAPositionWaypoint.Altitude Change Behaviour', 'Altitude Change Behaviour', base.DEC)
f.UAPositionWaypoint_Waypoint to Speed = ProtoField.uint16('dli.UAPositionWaypoint.Waypoint to Speed', 'Waypoint to Speed', base.DEC)
f.UAPositionWaypoint_Waypoint Speed Type = ProtoField.uint8('dli.UAPositionWaypoint.Waypoint Speed Type', 'Waypoint Speed Type', base.DEC)
f.UAPositionWaypoint_Next Waypoint = ProtoField.uint16('dli.UAPositionWaypoint.Next Waypoint', 'Next Waypoint', base.DEC)
f.UAPositionWaypoint_Turn Type = ProtoField.uint8('dli.UAPositionWaypoint.Turn Type', 'Turn Type', base.DEC)
f.UAPositionWaypoint_Optional Messages for Waypoint = ProtoField.uint8('dli.UAPositionWaypoint.Optional Messages for Waypoint', 'Optional Messages for Waypoint', base.DEC)
f.UAPositionWaypoint_Waypoint Type = ProtoField.uint8('dli.UAPositionWaypoint.Waypoint Type', 'Waypoint Type', base.DEC)
f.UAPositionWaypoint_Limit Type = ProtoField.uint8('dli.UAPositionWaypoint.Limit Type', 'Limit Type', base.DEC)
f.UAPositionWaypoint_Loop Limit = ProtoField.uint16('dli.UAPositionWaypoint.Loop Limit', 'Loop Limit', base.DEC)
f.UAPositionWaypoint_Arrival Time = ProtoField.uint64('dli.UAPositionWaypoint.Arrival Time', 'Arrival Time', base.DEC)
f.UAPositionWaypoint_Activity ID = ProtoField.uint32('dli.UAPositionWaypoint.Activity ID', 'Activity ID', base.DEC)
-- Fields for 16002 Heartbeat
f.Heartbeat_Time Stamp = ProtoField.uint64('dli.Heartbeat.Time Stamp', 'Time Stamp', base.DEC)
-- Fields for 17000 MessageAcknowledgement
f.MessageAcknowledgement_Time Stamp = ProtoField.uint64('dli.MessageAcknowledgement.Time Stamp', 'Time Stamp', base.DEC)
f.MessageAcknowledgement_Original Message Time Stamp = ProtoField.uint64('dli.MessageAcknowledgement.Original Message Time Stamp', 'Original Message Time Stamp', base.DEC)
f.MessageAcknowledgement_Original Message Type = ProtoField.uint16('dli.MessageAcknowledgement.Original Message Type', 'Original Message Type', base.DEC)
f.MessageAcknowledgement_Acknowledgement Type = ProtoField.uint8('dli.MessageAcknowledgement.Acknowledgement Type', 'Acknowledgement Type', base.DEC)

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
            local pv = read_uint_be(buffer, offset, 3)
            pay_tree:add(buffer(offset, 3), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 3

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_VSM ID, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_Data Link ID, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_Vehicle Type, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_Vehicle Subtype, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_Requested/Handover LOI, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_Requested/Handover Access, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_Requested Flight Mode, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_Controlled Station 1-16, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_Component Number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_Sub-Component Number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_Payload Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_Asset Mode, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 13)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_Wait for Vehicle Data Link Transition Coordination Message, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 14)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_CUCS Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 15)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_CUCS Subtype, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 16)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_Presence Vector Support, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 17)) ~= 0 then
                pay_tree:add(f.CUCSAuthorisationRequest_Controlled Station 17-32, buffer(offset, 2))
                offset = offset + 2
            end
        elseif msg_type == 2 then
            pinfo.cols.info = 'VSMAuthorisationResponse'
            local pv = read_uint_be(buffer, offset, 3)
            pay_tree:add(buffer(offset, 3), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 3

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_VSM ID, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_Data Link ID, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_Access Authorized, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_Access Granted, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_LOI Authorized, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_LOI Granted, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_Flight Modes Granted, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_Controlled Station 1-16, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_Component Number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_Sub-Component Number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_Payload Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_Access Requested, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 13)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_Vehicle Type, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 14)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_Vehicle Subtype, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 15)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_CUCS Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 16)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_CUCS Subtype, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 17)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_Presence Vector Support, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 18)) ~= 0 then
                pay_tree:add(f.VSMAuthorisationResponse_Controlled Station 17-32, buffer(offset, 2))
                offset = offset + 2
            end
        elseif msg_type == 3 then
            pinfo.cols.info = 'VehicleID'
            local pv = read_uint_be(buffer, offset, 2)
            pay_tree:add(buffer(offset, 2), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 2

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.VehicleID_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.VehicleID_VSM ID, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.VehicleID_Vehicle ID Update, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.VehicleID_Vehicle Type, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.VehicleID_Vehicle Subtype, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.VehicleID_Owning ID, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.VehicleID_Tail Number, buffer(offset, 16))
                offset = offset + 16
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.VehicleID_Mission ID, buffer(offset, 20))
                offset = offset + 20
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.VehicleID_ATC Call Sign, buffer(offset, 32))
                offset = offset + 32
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.VehicleID_Configuration Checksum, buffer(offset, 2))
                offset = offset + 2
            end
        elseif msg_type == 4 then
            pinfo.cols.info = 'PositiveHandoverAuthorisationRequest'
            local pv = read_uint_be(buffer, offset, 2)
            pay_tree:add(buffer(offset, 2), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 2

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_VSM ID, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_Data Link ID, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_Vehicle Type, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_Vehicle Subtype, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_Requested/Handover LOI, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_Flight Mode Offset, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_Requested Flight Mode, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_Controlled Station 1-16, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_Component Number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_Sub-Component Number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_Requesting CUCS Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_Requesting CUCS Subtype, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 13)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_Requesting CUCS ID, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 14)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_Presence Vector Support, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 15)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationRequest_Controlled Station 17-32, buffer(offset, 2))
                offset = offset + 2
            end
        elseif msg_type == 5 then
            pinfo.cols.info = 'PositiveHandoverAuthorisationGranted'
            local pv = read_uint_be(buffer, offset, 3)
            pay_tree:add(buffer(offset, 3), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 3

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_VSM ID, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_Data Link ID, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_LOI Authorized, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_Flight Mode Offset, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_Flight Modes Authorized, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_Controlled Station 1 16 Authorized, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_Component Number Authorized, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_Sub-Component Number Authorized, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_Vehicle Type, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_Vehicle Subtype, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_Requesting CUCS Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_Requesting CUCS Subtype, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 13)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_Requesting CUCS ID, buffer(offset, 4))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 14)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_Presence Vector Support, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 15)) ~= 0 then
                pay_tree:add(f.PositiveHandoverAuthorisationGranted_Controlled Station 17-32 Authorized, buffer(offset, 2))
                offset = offset + 2
            end
        elseif msg_type == 2000 then
            pinfo.cols.info = 'VehicleConfigurationCommand'
            local pv = read_uint_be(buffer, offset, 1)
            pay_tree:add(buffer(offset, 1), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 1

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.VehicleConfigurationCommand_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.VehicleConfigurationCommand_Energy Storage Unit, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.VehicleConfigurationCommand_Initial Propulsion Energy, buffer(offset, 2))
                offset = offset + 2
            end
        elseif msg_type == 2007 then
            pinfo.cols.info = 'UnmannedAircraftLights'
            local pv = read_uint_be(buffer, offset, 1)
            pay_tree:add(buffer(offset, 1), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 1

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.UnmannedAircraftLights_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.UnmannedAircraftLights_Set Lights, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.UnmannedAircraftLights_Activity ID, buffer(offset, 3))
                offset = offset + 3
            end
        elseif msg_type == 2008 then
            pinfo.cols.info = 'EngineCommand'
            local pv = read_uint_be(buffer, offset, 1)
            pay_tree:add(buffer(offset, 1), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 1

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.EngineCommand_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.EngineCommand_Engine Number, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.EngineCommand_Engine Command, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.EngineCommand_Reverse Thrust Power, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.EngineCommand_Reverse Thrust, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.EngineCommand_Ignition Switch Power, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.EngineCommand_Ignition Switch Activation, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.EngineCommand_Activity ID, buffer(offset, 3))
                offset = offset + 3
            end
        elseif msg_type == 2010 then
            pinfo.cols.info = 'UAStickCommand'
            local pv = read_uint_be(buffer, offset, 2)
            pay_tree:add(buffer(offset, 2), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 2

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.UAStickCommand_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.UAStickCommand_Lateral Stick, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.UAStickCommand_Longitudinal Stick, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.UAStickCommand_Rotational Stick (Rudder), buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.UAStickCommand_Throttle Stick - Engine 1, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.UAStickCommand_Pitch Stick - Engine 1, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.UAStickCommand_Throttle Stick - Engine 2, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.UAStickCommand_Pitch Stick - Engine 2, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.UAStickCommand_Throttle Stick - Engine 3, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.UAStickCommand_Pitch Stick - Engine 3, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.UAStickCommand_Throttle Stick - Engine 4, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                pay_tree:add(f.UAStickCommand_Pitch Stick - Engine 4, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.UAStickCommand_Taxi Stick, buffer(offset, 1))
                offset = offset + 1
            end
        elseif msg_type == 2016 then
            pinfo.cols.info = 'VehicleOperatingModeCommand'
            local pv = read_uint_be(buffer, offset, 3)
            pay_tree:add(buffer(offset, 3), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 3

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_Select Flight Path Control Mode, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_Altitude Command Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_Commanded Altitude, buffer(offset, 3))
                offset = offset + 3
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_Commanded Vertical Speed, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_Heading Command Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_Heading Reference, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 2)
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingModeCommand_Commanded Heading, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 2)
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingModeCommand_Commanded Course, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_Commanded Turn Rate, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_Commanded Roll Rate, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 2)
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingModeCommand_Commanded Roll, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_Commanded Speed, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 13)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_Speed Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 14)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_Commanded Waypoint Number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 15)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_Altimeter Setting, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 16)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_Altitude Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 17)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 4)
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingModeCommand_Loiter Position Latitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 18)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 4)
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingModeCommand_Loiter Position Longitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 19)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_Loiter Altitude Change Behaviour, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 20)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 2)
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingModeCommand_Thrust Direction, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 21)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_Thrust, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 22)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeCommand_Activity ID, buffer(offset, 3))
                offset = offset + 3
            end
        elseif msg_type == 2017 then
            pinfo.cols.info = 'LoiterConfiguration'
            local pv = read_uint_be(buffer, offset, 2)
            pay_tree:add(buffer(offset, 2), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 2

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.LoiterConfiguration_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.LoiterConfiguration_Loiter Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.LoiterConfiguration_Loiter Radius, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.LoiterConfiguration_Loiter Length, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.LoiterConfiguration_Loiter Length Units, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 2)
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.LoiterConfiguration_Loiter Bearing, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.LoiterConfiguration_Loiter Direction, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.LoiterConfiguration_Flying Behaviour, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.LoiterConfiguration_Loiter Duration, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.LoiterConfiguration_Loiter Duration Units, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.LoiterConfiguration_Activity ID, buffer(offset, 3))
                offset = offset + 3
            end
        elseif msg_type == 3001 then
            pinfo.cols.info = 'VehicleOperatingModeReport'
            local pv = read_uint_be(buffer, offset, 1)
            pay_tree:add(buffer(offset, 1), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 1

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeReport_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.VehicleOperatingModeReport_Select Flight Path Control Mode, buffer(offset, 1))
                offset = offset + 1
            end
        elseif msg_type == 3002 then
            pinfo.cols.info = 'VehicleOperatingStates'
            local pv = read_uint_be(buffer, offset, 3)
            pay_tree:add(buffer(offset, 3), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 3

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_Commanded Altitude, buffer(offset, 3))
                offset = offset + 3
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_Altitude Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 2)
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingStates_Commanded Heading, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 2)
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingStates_Commanded Course, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_Commanded Turn Rate, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_Commanded Roll Rate, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_Commanded Speed, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_Speed Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_Power Level, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_Bingo Energy, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_Current Propulsion Energy Level, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_Current Propulsion Energy Usage Rate, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 13)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 2)
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingStates_Commanded Roll, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 14)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_Altitude Command Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 15)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_Heading Command Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 16)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_UA State, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 17)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 2)
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingStates_Thrust Direction, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 18)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_Thrust, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 19)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_Loiter & Waypoint Validity, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 20)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 4)
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingStates_Commanded Loiter Position Latitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 21)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 4)
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.VehicleOperatingStates_Commanded Loiter Position Longitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 22)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_Altitude Change Behaviour, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 23)) ~= 0 then
                pay_tree:add(f.VehicleOperatingStates_Commanded Waypoint Number, buffer(offset, 2))
                offset = offset + 2
            end
        elseif msg_type == 3004 then
            pinfo.cols.info = 'LoiterConfigurationReport'
            local pv = read_uint_be(buffer, offset, 2)
            pay_tree:add(buffer(offset, 2), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 2

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_Loiter Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_Loiter Radius, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_Loiter Length, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_Loiter Length Units, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 2)
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.LoiterConfigurationReport_Loiter Bearing, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_Loiter Direction, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_Loiter Altitude, buffer(offset, 3))
                offset = offset + 3
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_Altitude Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_Loiter Speed, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_Speed Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_Flying Behaviour, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_Loiter Duration, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 13)) ~= 0 then
                pay_tree:add(f.LoiterConfigurationReport_Loiter Duration Units, buffer(offset, 1))
                offset = offset + 1
            end
        elseif msg_type == 3006 then
            pinfo.cols.info = 'VehicleLightsState'
            local pv = read_uint_be(buffer, offset, 1)
            pay_tree:add(buffer(offset, 1), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 1

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.VehicleLightsState_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.VehicleLightsState_Navigation Lights State, buffer(offset, 2))
                offset = offset + 2
            end
        elseif msg_type == 3007 then
            pinfo.cols.info = 'EngineOperatingStates'
            local pv = read_uint_be(buffer, offset, 5)
            pay_tree:add(buffer(offset, 5), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 5

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Status, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Reported Engine Command, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Reverse Thrust Power Status, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Reported Reverse Thrust, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Ignition Switch Power Status, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Ignition Switch Activation, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Power Setting, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Speed 1 Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Speed 1, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Speed 2 Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Speed 2, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 13)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Speed 3 Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 14)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Speed 3, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 15)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Propeller Pitch Angle, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 16)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Output Power (Shaft Torque) Status, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 17)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Temperature 1 Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 18)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Temperature 1, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 19)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Temperature 2 Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 20)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Temperature 2, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 21)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Temperature 3 Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 22)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Temperature 3, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 23)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Temperature 4 Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 24)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Temperature 4, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 25)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Pressure 1 Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 26)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Pressure 1, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 27)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Pressure 1 Status, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 28)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Pressure 2 Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 29)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Pressure 2, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 30)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Pressure 2 Status, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 31)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Fire Detection Sensor Status, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 32)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Energy Flow, buffer(offset, 3))
                offset = offset + 3
            end
            if bit.band(pv, bit.lshift(1, 33)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Engine Body Temperature Status, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 34)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Exhaust Gas Temperature Status, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 35)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Coolant Temperature Status, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 36)) ~= 0 then
                pay_tree:add(f.EngineOperatingStates_Lubricant Temperature Status, buffer(offset, 1))
                offset = offset + 1
            end
        elseif msg_type == 3011 then
            pinfo.cols.info = 'UAStickStatus'
            local pv = read_uint_be(buffer, offset, 2)
            pay_tree:add(buffer(offset, 2), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 2

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.UAStickStatus_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.UAStickStatus_Lateral Stick, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.UAStickStatus_Longitudinal Stick, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.UAStickStatus_Rotational Stick (Rudder), buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.UAStickStatus_Throttle Stick - Engine 1, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.UAStickStatus_Pitch Stick - Engine 1, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.UAStickStatus_Throttle Stick - Engine 2, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.UAStickStatus_Pitch Stick - Engine 2, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.UAStickStatus_Throttle Stick - Engine 3, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.UAStickStatus_Pitch Stick - Engine 3, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.UAStickStatus_Throttle Stick - Engine 4, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                pay_tree:add(f.UAStickStatus_Pitch Stick - Engine 4, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.UAStickStatus_Taxi Stick, buffer(offset, 1))
                offset = offset + 1
            end
        elseif msg_type == 4000 then
            pinfo.cols.info = 'InertialStates'
            local pv = read_uint_be(buffer, offset, 3)
            pay_tree:add(buffer(offset, 3), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 3

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.InertialStates_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 4)
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.InertialStates_Latitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 4)
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.InertialStates_Longitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.InertialStates_Altitude, buffer(offset, 3))
                offset = offset + 3
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.InertialStates_Altitude Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.InertialStates_U_Speed, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.InertialStates_V_Speed, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.InertialStates_W_Speed, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.InertialStates_U_Accel, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.InertialStates_V_Accel, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.InertialStates_W_Accel, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 2)
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.InertialStates_Roll, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 2)
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.InertialStates_Pitch, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 13)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 2)
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.InertialStates_Heading, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 14)) ~= 0 then
                pay_tree:add(f.InertialStates_Roll Rate, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 15)) ~= 0 then
                pay_tree:add(f.InertialStates_Pitch Rate, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 16)) ~= 0 then
                pay_tree:add(f.InertialStates_Turn Rate, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 17)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 2)
                local eng = decode_bam(raw, 16, -3.1415926535, 3.1415926535)
                pay_tree:add(f.InertialStates_Magnetic Variation, buffer(offset, 2)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 2
            end
        elseif msg_type == 4001 then
            pinfo.cols.info = 'FromToNextWaypointStates'
            local pv = read_uint_be(buffer, offset, 3)
            pay_tree:add(buffer(offset, 3), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 3

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_Altitude Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_Speed Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 4)
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.FromToNextWaypointStates_From Waypoint – Latitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 4)
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.FromToNextWaypointStates_From Waypoint – Longitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_From Waypoint Altitude, buffer(offset, 3))
                offset = offset + 3
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_From Waypoint Time, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_From Waypoint Number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 4)
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.FromToNextWaypointStates_To Waypoint – Latitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 4)
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.FromToNextWaypointStates_To Waypoint – Longitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_To Waypoint Altitude, buffer(offset, 3))
                offset = offset + 3
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_To Waypoint Speed, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_To Waypoint Time, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 13)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_To Waypoint Number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 14)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 4)
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.FromToNextWaypointStates_Next Waypoint – Latitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 15)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 4)
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.FromToNextWaypointStates_Next Waypoint – Longitude, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 16)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_Next Waypoint Altitude, buffer(offset, 3))
                offset = offset + 3
            end
            if bit.band(pv, bit.lshift(1, 17)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_Next Waypoint Speed, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 18)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_Next Waypoint Time, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 19)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_Next Waypoint Number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 20)) ~= 0 then
                pay_tree:add(f.FromToNextWaypointStates_Loiter Configuration Report Validity for “To Waypoint”, buffer(offset, 1))
                offset = offset + 1
            end
        elseif msg_type == 13002 then
            pinfo.cols.info = 'UAPositionWaypoint'
            local pv = read_uint_be(buffer, offset, 3)
            pay_tree:add(buffer(offset, 3), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 3

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_Waypoint Number, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 4)
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.UAPositionWaypoint_Waypoint to Latitude or Relative Y, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                local raw = read_uint_be(buffer, offset, 4)
                local eng = decode_bam(raw, 32, -3.1415926535, 3.1415926535)
                pay_tree:add(f.UAPositionWaypoint_Waypoint to Longitude or Relative X, buffer(offset, 4)):append_text(string.format(' (Eng: %.6f)', eng))
                offset = offset + 4
            end
            if bit.band(pv, bit.lshift(1, 4)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_Location Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 5)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_Waypoint to Altitude, buffer(offset, 3))
                offset = offset + 3
            end
            if bit.band(pv, bit.lshift(1, 6)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_Waypoint Altitude Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 7)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_Altitude Change Behaviour, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 8)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_Waypoint to Speed, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 9)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_Waypoint Speed Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 10)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_Next Waypoint, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 11)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_Turn Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 12)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_Optional Messages for Waypoint, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 13)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_Waypoint Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 14)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_Limit Type, buffer(offset, 1))
                offset = offset + 1
            end
            if bit.band(pv, bit.lshift(1, 15)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_Loop Limit, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 16)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_Arrival Time, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 17)) ~= 0 then
                pay_tree:add(f.UAPositionWaypoint_Activity ID, buffer(offset, 3))
                offset = offset + 3
            end
        elseif msg_type == 16002 then
            pinfo.cols.info = 'Heartbeat'
            local pv = read_uint_be(buffer, offset, 1)
            pay_tree:add(buffer(offset, 1), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 1

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.Heartbeat_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
        elseif msg_type == 17000 then
            pinfo.cols.info = 'MessageAcknowledgement'
            local pv = read_uint_be(buffer, offset, 1)
            pay_tree:add(buffer(offset, 1), 'Presence Vector: ' .. string.format('0x%X', pv))
            offset = offset + 1

            if bit.band(pv, bit.lshift(1, 0)) ~= 0 then
                pay_tree:add(f.MessageAcknowledgement_Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 1)) ~= 0 then
                pay_tree:add(f.MessageAcknowledgement_Original Message Time Stamp, buffer(offset, 5))
                offset = offset + 5
            end
            if bit.band(pv, bit.lshift(1, 2)) ~= 0 then
                pay_tree:add(f.MessageAcknowledgement_Original Message Type, buffer(offset, 2))
                offset = offset + 2
            end
            if bit.band(pv, bit.lshift(1, 3)) ~= 0 then
                pay_tree:add(f.MessageAcknowledgement_Acknowledgement Type, buffer(offset, 1))
                offset = offset + 1
            end
        end
    end
end

local udp_table = DissectorTable.get('udp.port')
udp_table:add(30001, dli_proto)
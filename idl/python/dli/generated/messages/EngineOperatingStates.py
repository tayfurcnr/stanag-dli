from dli.core.bit_cursor import BitCursor
from dli.utils import BAM, Scaled
import math

class EngineOperatingStates:
    def __init__(self):
        # Presence Vector
        self.pv = 0
        
        self.time_stamp = 0
        self.has_time_stamp = False
        
        self.engine_number = 0
        self.has_engine_number = False
        
        self.engine_status = 0
        self.has_engine_status = False
        
        self.reported_engine_command = 0
        self.has_reported_engine_command = False
        
        self.reverse_thrust_power_status = 0
        self.has_reverse_thrust_power_status = False
        
        self.reported_reverse_thrust = 0
        self.has_reported_reverse_thrust = False
        
        self.ignition_switch_power_status = 0
        self.has_ignition_switch_power_status = False
        
        self.ignition_switch_activation = 0
        self.has_ignition_switch_activation = False
        
        self.engine_power_setting = 0.0
        self.has_engine_power_setting = False
        
        self.engine_speed_1_type = 0
        self.has_engine_speed_1_type = False
        
        self.engine_speed_1 = 0.0
        self.has_engine_speed_1 = False
        
        self.engine_speed_2_type = 0
        self.has_engine_speed_2_type = False
        
        self.engine_speed_2 = 0.0
        self.has_engine_speed_2 = False
        
        self.engine_speed_3_type = 0
        self.has_engine_speed_3_type = False
        
        self.engine_speed_3 = 0.0
        self.has_engine_speed_3 = False
        
        self.propeller_pitch_angle = 0.0
        self.has_propeller_pitch_angle = False
        
        self.output_power_shaft_torque_status = 0
        self.has_output_power_shaft_torque_status = False
        
        self.engine_temperature_1_type = 0
        self.has_engine_temperature_1_type = False
        
        self.engine_temperature_1 = 0.0
        self.has_engine_temperature_1 = False
        
        self.engine_temperature_2_type = 0
        self.has_engine_temperature_2_type = False
        
        self.engine_temperature_2 = 0.0
        self.has_engine_temperature_2 = False
        
        self.engine_temperature_3_type = 0
        self.has_engine_temperature_3_type = False
        
        self.engine_temperature_3 = 0.0
        self.has_engine_temperature_3 = False
        
        self.engine_temperature_4_type = 0
        self.has_engine_temperature_4_type = False
        
        self.engine_temperature_4 = 0.0
        self.has_engine_temperature_4 = False
        
        self.engine_pressure_1_type = 0
        self.has_engine_pressure_1_type = False
        
        self.engine_pressure_1 = 0.0
        self.has_engine_pressure_1 = False
        
        self.engine_pressure_1_status = 0
        self.has_engine_pressure_1_status = False
        
        self.engine_pressure_2_type = 0
        self.has_engine_pressure_2_type = False
        
        self.engine_pressure_2 = 0.0
        self.has_engine_pressure_2 = False
        
        self.engine_pressure_2_status = 0
        self.has_engine_pressure_2_status = False
        
        self.fire_detection_sensor_status = 0
        self.has_fire_detection_sensor_status = False
        
        self.engine_energy_flow = 0.0
        self.has_engine_energy_flow = False
        
        self.engine_body_temperature_status = 0
        self.has_engine_body_temperature_status = False
        
        self.exhaust_gas_temperature_status = 0
        self.has_exhaust_gas_temperature_status = False
        
        self.coolant_temperature_status = 0
        self.has_coolant_temperature_status = False
        
        self.lubricant_temperature_status = 0
        self.has_lubricant_temperature_status = False
        

    def serialize(self, cursor: BitCursor):
        # 1. Prepare PV
        self.pv = 0
        
        if self.has_time_stamp:
            self.pv |= (1 << 0)
        
        if self.has_engine_number:
            self.pv |= (1 << 1)
        
        if self.has_engine_status:
            self.pv |= (1 << 2)
        
        if self.has_reported_engine_command:
            self.pv |= (1 << 3)
        
        if self.has_reverse_thrust_power_status:
            self.pv |= (1 << 4)
        
        if self.has_reported_reverse_thrust:
            self.pv |= (1 << 5)
        
        if self.has_ignition_switch_power_status:
            self.pv |= (1 << 6)
        
        if self.has_ignition_switch_activation:
            self.pv |= (1 << 7)
        
        if self.has_engine_power_setting:
            self.pv |= (1 << 8)
        
        if self.has_engine_speed_1_type:
            self.pv |= (1 << 9)
        
        if self.has_engine_speed_1:
            self.pv |= (1 << 10)
        
        if self.has_engine_speed_2_type:
            self.pv |= (1 << 11)
        
        if self.has_engine_speed_2:
            self.pv |= (1 << 12)
        
        if self.has_engine_speed_3_type:
            self.pv |= (1 << 13)
        
        if self.has_engine_speed_3:
            self.pv |= (1 << 14)
        
        if self.has_propeller_pitch_angle:
            self.pv |= (1 << 15)
        
        if self.has_output_power_shaft_torque_status:
            self.pv |= (1 << 16)
        
        if self.has_engine_temperature_1_type:
            self.pv |= (1 << 17)
        
        if self.has_engine_temperature_1:
            self.pv |= (1 << 18)
        
        if self.has_engine_temperature_2_type:
            self.pv |= (1 << 19)
        
        if self.has_engine_temperature_2:
            self.pv |= (1 << 20)
        
        if self.has_engine_temperature_3_type:
            self.pv |= (1 << 21)
        
        if self.has_engine_temperature_3:
            self.pv |= (1 << 22)
        
        if self.has_engine_temperature_4_type:
            self.pv |= (1 << 23)
        
        if self.has_engine_temperature_4:
            self.pv |= (1 << 24)
        
        if self.has_engine_pressure_1_type:
            self.pv |= (1 << 25)
        
        if self.has_engine_pressure_1:
            self.pv |= (1 << 26)
        
        if self.has_engine_pressure_1_status:
            self.pv |= (1 << 27)
        
        if self.has_engine_pressure_2_type:
            self.pv |= (1 << 28)
        
        if self.has_engine_pressure_2:
            self.pv |= (1 << 29)
        
        if self.has_engine_pressure_2_status:
            self.pv |= (1 << 30)
        
        if self.has_fire_detection_sensor_status:
            self.pv |= (1 << 31)
        
        if self.has_engine_energy_flow:
            self.pv |= (1 << 32)
        
        if self.has_engine_body_temperature_status:
            self.pv |= (1 << 33)
        
        if self.has_exhaust_gas_temperature_status:
            self.pv |= (1 << 34)
        
        if self.has_coolant_temperature_status:
            self.pv |= (1 << 35)
        
        if self.has_lubricant_temperature_status:
            self.pv |= (1 << 36)
        

        # 2. Write PV
        
        
        
        
        
        cursor.write_uint40(self.pv)
        

        # 3. Write Fields
        
        if self.has_time_stamp:
            cursor.write_uint40(self.time_stamp)
        
        if self.has_engine_number:
            cursor.write_uint16(self.engine_number)
        
        if self.has_engine_status:
            cursor.write_uint8(self.engine_status)
        
        if self.has_reported_engine_command:
            cursor.write_uint8(self.reported_engine_command)
        
        if self.has_reverse_thrust_power_status:
            cursor.write_uint8(self.reverse_thrust_power_status)
        
        if self.has_reported_reverse_thrust:
            cursor.write_uint8(self.reported_reverse_thrust)
        
        if self.has_ignition_switch_power_status:
            cursor.write_uint8(self.ignition_switch_power_status)
        
        if self.has_ignition_switch_activation:
            cursor.write_uint8(self.ignition_switch_activation)
        
        if self.has_engine_power_setting:
            cursor.write_uint16(Scaled.to_scaled(self.engine_power_setting, 0.0, 0.0017))
        
        if self.has_engine_speed_1_type:
            cursor.write_uint8(self.engine_speed_1_type)
        
        if self.has_engine_speed_1:
            cursor.write_uint16(Scaled.to_scaled(self.engine_speed_1, 0.0, 0.5))
        
        if self.has_engine_speed_2_type:
            cursor.write_uint8(self.engine_speed_2_type)
        
        if self.has_engine_speed_2:
            cursor.write_uint16(Scaled.to_scaled(self.engine_speed_2, 0.0, 0.5))
        
        if self.has_engine_speed_3_type:
            cursor.write_uint8(self.engine_speed_3_type)
        
        if self.has_engine_speed_3:
            cursor.write_uint16(Scaled.to_scaled(self.engine_speed_3, 0.0, 0.5))
        
        if self.has_propeller_pitch_angle:
            cursor.write_int8(Scaled.to_scaled(self.propeller_pitch_angle, 0.0, 0.02))
        
        if self.has_output_power_shaft_torque_status:
            cursor.write_uint8(self.output_power_shaft_torque_status)
        
        if self.has_engine_temperature_1_type:
            cursor.write_uint8(self.engine_temperature_1_type)
        
        if self.has_engine_temperature_1:
            cursor.write_uint16(Scaled.to_scaled(self.engine_temperature_1, 0.0, 0.5))
        
        if self.has_engine_temperature_2_type:
            cursor.write_uint8(self.engine_temperature_2_type)
        
        if self.has_engine_temperature_2:
            cursor.write_uint16(Scaled.to_scaled(self.engine_temperature_2, 0.0, 0.5))
        
        if self.has_engine_temperature_3_type:
            cursor.write_uint8(self.engine_temperature_3_type)
        
        if self.has_engine_temperature_3:
            cursor.write_uint16(Scaled.to_scaled(self.engine_temperature_3, 0.0, 0.5))
        
        if self.has_engine_temperature_4_type:
            cursor.write_uint8(self.engine_temperature_4_type)
        
        if self.has_engine_temperature_4:
            cursor.write_uint16(Scaled.to_scaled(self.engine_temperature_4, 0.0, 0.5))
        
        if self.has_engine_pressure_1_type:
            cursor.write_uint8(self.engine_pressure_1_type)
        
        if self.has_engine_pressure_1:
            cursor.write_uint16(Scaled.to_scaled(self.engine_pressure_1, 0.0, 10.0))
        
        if self.has_engine_pressure_1_status:
            cursor.write_uint8(self.engine_pressure_1_status)
        
        if self.has_engine_pressure_2_type:
            cursor.write_uint8(self.engine_pressure_2_type)
        
        if self.has_engine_pressure_2:
            cursor.write_uint16(Scaled.to_scaled(self.engine_pressure_2, 0.0, 10.0))
        
        if self.has_engine_pressure_2_status:
            cursor.write_uint8(self.engine_pressure_2_status)
        
        if self.has_fire_detection_sensor_status:
            cursor.write_uint8(self.fire_detection_sensor_status)
        
        if self.has_engine_energy_flow:
            cursor.write_uint24(Scaled.to_scaled(self.engine_energy_flow, 0.0, 0.0017))
        
        if self.has_engine_body_temperature_status:
            cursor.write_uint8(self.engine_body_temperature_status)
        
        if self.has_exhaust_gas_temperature_status:
            cursor.write_uint8(self.exhaust_gas_temperature_status)
        
        if self.has_coolant_temperature_status:
            cursor.write_uint8(self.coolant_temperature_status)
        
        if self.has_lubricant_temperature_status:
            cursor.write_uint8(self.lubricant_temperature_status)
        

    def deserialize(self, cursor: BitCursor):
        # 1. Read PV
        
        
        
        
        
        self.pv = cursor.read_uint40()
        

        # 2. Read Fields
        
        if self.pv & (1 << 0):
            self.has_time_stamp = True
            self.time_stamp = cursor.read_uint40()
        else:
            self.has_time_stamp = False
        
        if self.pv & (1 << 1):
            self.has_engine_number = True
            self.engine_number = cursor.read_uint16()
        else:
            self.has_engine_number = False
        
        if self.pv & (1 << 2):
            self.has_engine_status = True
            self.engine_status = cursor.read_uint8()
        else:
            self.has_engine_status = False
        
        if self.pv & (1 << 3):
            self.has_reported_engine_command = True
            self.reported_engine_command = cursor.read_uint8()
        else:
            self.has_reported_engine_command = False
        
        if self.pv & (1 << 4):
            self.has_reverse_thrust_power_status = True
            self.reverse_thrust_power_status = cursor.read_uint8()
        else:
            self.has_reverse_thrust_power_status = False
        
        if self.pv & (1 << 5):
            self.has_reported_reverse_thrust = True
            self.reported_reverse_thrust = cursor.read_uint8()
        else:
            self.has_reported_reverse_thrust = False
        
        if self.pv & (1 << 6):
            self.has_ignition_switch_power_status = True
            self.ignition_switch_power_status = cursor.read_uint8()
        else:
            self.has_ignition_switch_power_status = False
        
        if self.pv & (1 << 7):
            self.has_ignition_switch_activation = True
            self.ignition_switch_activation = cursor.read_uint8()
        else:
            self.has_ignition_switch_activation = False
        
        if self.pv & (1 << 8):
            self.has_engine_power_setting = True
            self.engine_power_setting = Scaled.from_scaled(cursor.read_uint16(), 0.0, 0.0017)
        else:
            self.has_engine_power_setting = False
        
        if self.pv & (1 << 9):
            self.has_engine_speed_1_type = True
            self.engine_speed_1_type = cursor.read_uint8()
        else:
            self.has_engine_speed_1_type = False
        
        if self.pv & (1 << 10):
            self.has_engine_speed_1 = True
            self.engine_speed_1 = Scaled.from_scaled(cursor.read_uint16(), 0.0, 0.5)
        else:
            self.has_engine_speed_1 = False
        
        if self.pv & (1 << 11):
            self.has_engine_speed_2_type = True
            self.engine_speed_2_type = cursor.read_uint8()
        else:
            self.has_engine_speed_2_type = False
        
        if self.pv & (1 << 12):
            self.has_engine_speed_2 = True
            self.engine_speed_2 = Scaled.from_scaled(cursor.read_uint16(), 0.0, 0.5)
        else:
            self.has_engine_speed_2 = False
        
        if self.pv & (1 << 13):
            self.has_engine_speed_3_type = True
            self.engine_speed_3_type = cursor.read_uint8()
        else:
            self.has_engine_speed_3_type = False
        
        if self.pv & (1 << 14):
            self.has_engine_speed_3 = True
            self.engine_speed_3 = Scaled.from_scaled(cursor.read_uint16(), 0.0, 0.5)
        else:
            self.has_engine_speed_3 = False
        
        if self.pv & (1 << 15):
            self.has_propeller_pitch_angle = True
            self.propeller_pitch_angle = Scaled.from_scaled(cursor.read_int8(), 0.0, 0.02)
        else:
            self.has_propeller_pitch_angle = False
        
        if self.pv & (1 << 16):
            self.has_output_power_shaft_torque_status = True
            self.output_power_shaft_torque_status = cursor.read_uint8()
        else:
            self.has_output_power_shaft_torque_status = False
        
        if self.pv & (1 << 17):
            self.has_engine_temperature_1_type = True
            self.engine_temperature_1_type = cursor.read_uint8()
        else:
            self.has_engine_temperature_1_type = False
        
        if self.pv & (1 << 18):
            self.has_engine_temperature_1 = True
            self.engine_temperature_1 = Scaled.from_scaled(cursor.read_uint16(), 0.0, 0.5)
        else:
            self.has_engine_temperature_1 = False
        
        if self.pv & (1 << 19):
            self.has_engine_temperature_2_type = True
            self.engine_temperature_2_type = cursor.read_uint8()
        else:
            self.has_engine_temperature_2_type = False
        
        if self.pv & (1 << 20):
            self.has_engine_temperature_2 = True
            self.engine_temperature_2 = Scaled.from_scaled(cursor.read_uint16(), 0.0, 0.5)
        else:
            self.has_engine_temperature_2 = False
        
        if self.pv & (1 << 21):
            self.has_engine_temperature_3_type = True
            self.engine_temperature_3_type = cursor.read_uint8()
        else:
            self.has_engine_temperature_3_type = False
        
        if self.pv & (1 << 22):
            self.has_engine_temperature_3 = True
            self.engine_temperature_3 = Scaled.from_scaled(cursor.read_uint16(), 0.0, 0.5)
        else:
            self.has_engine_temperature_3 = False
        
        if self.pv & (1 << 23):
            self.has_engine_temperature_4_type = True
            self.engine_temperature_4_type = cursor.read_uint8()
        else:
            self.has_engine_temperature_4_type = False
        
        if self.pv & (1 << 24):
            self.has_engine_temperature_4 = True
            self.engine_temperature_4 = Scaled.from_scaled(cursor.read_uint16(), 0.0, 0.5)
        else:
            self.has_engine_temperature_4 = False
        
        if self.pv & (1 << 25):
            self.has_engine_pressure_1_type = True
            self.engine_pressure_1_type = cursor.read_uint8()
        else:
            self.has_engine_pressure_1_type = False
        
        if self.pv & (1 << 26):
            self.has_engine_pressure_1 = True
            self.engine_pressure_1 = Scaled.from_scaled(cursor.read_uint16(), 0.0, 10.0)
        else:
            self.has_engine_pressure_1 = False
        
        if self.pv & (1 << 27):
            self.has_engine_pressure_1_status = True
            self.engine_pressure_1_status = cursor.read_uint8()
        else:
            self.has_engine_pressure_1_status = False
        
        if self.pv & (1 << 28):
            self.has_engine_pressure_2_type = True
            self.engine_pressure_2_type = cursor.read_uint8()
        else:
            self.has_engine_pressure_2_type = False
        
        if self.pv & (1 << 29):
            self.has_engine_pressure_2 = True
            self.engine_pressure_2 = Scaled.from_scaled(cursor.read_uint16(), 0.0, 10.0)
        else:
            self.has_engine_pressure_2 = False
        
        if self.pv & (1 << 30):
            self.has_engine_pressure_2_status = True
            self.engine_pressure_2_status = cursor.read_uint8()
        else:
            self.has_engine_pressure_2_status = False
        
        if self.pv & (1 << 31):
            self.has_fire_detection_sensor_status = True
            self.fire_detection_sensor_status = cursor.read_uint8()
        else:
            self.has_fire_detection_sensor_status = False
        
        if self.pv & (1 << 32):
            self.has_engine_energy_flow = True
            self.engine_energy_flow = Scaled.from_scaled(cursor.read_uint24(), 0.0, 0.0017)
        else:
            self.has_engine_energy_flow = False
        
        if self.pv & (1 << 33):
            self.has_engine_body_temperature_status = True
            self.engine_body_temperature_status = cursor.read_uint8()
        else:
            self.has_engine_body_temperature_status = False
        
        if self.pv & (1 << 34):
            self.has_exhaust_gas_temperature_status = True
            self.exhaust_gas_temperature_status = cursor.read_uint8()
        else:
            self.has_exhaust_gas_temperature_status = False
        
        if self.pv & (1 << 35):
            self.has_coolant_temperature_status = True
            self.coolant_temperature_status = cursor.read_uint8()
        else:
            self.has_coolant_temperature_status = False
        
        if self.pv & (1 << 36):
            self.has_lubricant_temperature_status = True
            self.lubricant_temperature_status = cursor.read_uint8()
        else:
            self.has_lubricant_temperature_status = False
        

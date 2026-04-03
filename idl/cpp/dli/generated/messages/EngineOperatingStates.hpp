#pragma once

#include <dli/core/BitCursor.hpp>
#include <dli/core/Bam.hpp>
#include <dli/core/Scaled.hpp>
#include <array>
#include <cstdint>

namespace dli {
namespace generated {

/**
 * @brief Auto-generated class for Message #3007: EngineOperatingStates
 */
class EngineOperatingStates {
public:
    // Fields

    uint64_t time_stamp; // [ms]

    uint16_t engine_number;

    uint8_t engine_status; // [enum]

    uint8_t reported_engine_command; // [enum]

    uint8_t reverse_thrust_power_status; // [enum]

    uint8_t reported_reverse_thrust; // [enum]

    uint8_t ignition_switch_power_status; // [enum]

    uint8_t ignition_switch_activation; // [enum]

    double engine_power_setting; // [%]

    uint8_t engine_speed_1_type; // [enum]

    double engine_speed_1; // [rad/s]

    uint8_t engine_speed_2_type; // [enum]

    double engine_speed_2; // [rad/s]

    uint8_t engine_speed_3_type; // [enum]

    double engine_speed_3; // [rad/s]

    double propeller_pitch_angle; // [rad]

    uint8_t output_power_shaft_torque_status; // [enum]

    uint8_t engine_temperature_1_type; // [enum]

    double engine_temperature_1; // [K]

    uint8_t engine_temperature_2_type; // [enum]

    double engine_temperature_2; // [K]

    uint8_t engine_temperature_3_type; // [enum]

    double engine_temperature_3; // [K]

    uint8_t engine_temperature_4_type; // [enum]

    double engine_temperature_4; // [K]

    uint8_t engine_pressure_1_type; // [enum]

    double engine_pressure_1; // [Pa]

    uint8_t engine_pressure_1_status; // [enum]

    uint8_t engine_pressure_2_type; // [enum]

    double engine_pressure_2; // [Pa]

    uint8_t engine_pressure_2_status; // [enum]

    uint8_t fire_detection_sensor_status; // [enum]

    double engine_energy_flow; // [%/s]

    uint8_t engine_body_temperature_status; // [enum]

    uint8_t exhaust_gas_temperature_status; // [enum]

    uint8_t coolant_temperature_status; // [enum]

    uint8_t lubricant_temperature_status; // [enum]


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint64_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (uint64_t{1} << 0);



        if (has_engine_number) pv |= (uint64_t{1} << 1);



        if (has_engine_status) pv |= (uint64_t{1} << 2);



        if (has_reported_engine_command) pv |= (uint64_t{1} << 3);



        if (has_reverse_thrust_power_status) pv |= (uint64_t{1} << 4);



        if (has_reported_reverse_thrust) pv |= (uint64_t{1} << 5);



        if (has_ignition_switch_power_status) pv |= (uint64_t{1} << 6);



        if (has_ignition_switch_activation) pv |= (uint64_t{1} << 7);



        if (has_engine_power_setting) pv |= (uint64_t{1} << 8);



        if (has_engine_speed_1_type) pv |= (uint64_t{1} << 9);



        if (has_engine_speed_1) pv |= (uint64_t{1} << 10);



        if (has_engine_speed_2_type) pv |= (uint64_t{1} << 11);



        if (has_engine_speed_2) pv |= (uint64_t{1} << 12);



        if (has_engine_speed_3_type) pv |= (uint64_t{1} << 13);



        if (has_engine_speed_3) pv |= (uint64_t{1} << 14);



        if (has_propeller_pitch_angle) pv |= (uint64_t{1} << 15);



        if (has_output_power_shaft_torque_status) pv |= (uint64_t{1} << 16);



        if (has_engine_temperature_1_type) pv |= (uint64_t{1} << 17);



        if (has_engine_temperature_1) pv |= (uint64_t{1} << 18);



        if (has_engine_temperature_2_type) pv |= (uint64_t{1} << 19);



        if (has_engine_temperature_2) pv |= (uint64_t{1} << 20);



        if (has_engine_temperature_3_type) pv |= (uint64_t{1} << 21);



        if (has_engine_temperature_3) pv |= (uint64_t{1} << 22);



        if (has_engine_temperature_4_type) pv |= (uint64_t{1} << 23);



        if (has_engine_temperature_4) pv |= (uint64_t{1} << 24);



        if (has_engine_pressure_1_type) pv |= (uint64_t{1} << 25);



        if (has_engine_pressure_1) pv |= (uint64_t{1} << 26);



        if (has_engine_pressure_1_status) pv |= (uint64_t{1} << 27);



        if (has_engine_pressure_2_type) pv |= (uint64_t{1} << 28);



        if (has_engine_pressure_2) pv |= (uint64_t{1} << 29);



        if (has_engine_pressure_2_status) pv |= (uint64_t{1} << 30);



        if (has_fire_detection_sensor_status) pv |= (uint64_t{1} << 31);



        if (has_engine_energy_flow) pv |= (uint64_t{1} << 32);



        if (has_engine_body_temperature_status) pv |= (uint64_t{1} << 33);



        if (has_exhaust_gas_temperature_status) pv |= (uint64_t{1} << 34);



        if (has_coolant_temperature_status) pv |= (uint64_t{1} << 35);



        if (has_lubricant_temperature_status) pv |= (uint64_t{1} << 36);


        
        cursor.write_int(pv, 5);

        // Write Fields


        if (pv & (uint64_t{1} << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (uint64_t{1} << 1)) {

            cursor.write(engine_number);

        }



        if (pv & (uint64_t{1} << 2)) {

            cursor.write(engine_status);

        }



        if (pv & (uint64_t{1} << 3)) {

            cursor.write(reported_engine_command);

        }



        if (pv & (uint64_t{1} << 4)) {

            cursor.write(reverse_thrust_power_status);

        }



        if (pv & (uint64_t{1} << 5)) {

            cursor.write(reported_reverse_thrust);

        }



        if (pv & (uint64_t{1} << 6)) {

            cursor.write(ignition_switch_power_status);

        }



        if (pv & (uint64_t{1} << 7)) {

            cursor.write(ignition_switch_activation);

        }



        if (pv & (uint64_t{1} << 8)) {

            cursor.write(scaled::to_scaled<uint16_t>(engine_power_setting, 0.0, 0.0017));

        }



        if (pv & (uint64_t{1} << 9)) {

            cursor.write(engine_speed_1_type);

        }



        if (pv & (uint64_t{1} << 10)) {

            cursor.write(scaled::to_scaled<uint16_t>(engine_speed_1, 0.0, 0.5));

        }



        if (pv & (uint64_t{1} << 11)) {

            cursor.write(engine_speed_2_type);

        }



        if (pv & (uint64_t{1} << 12)) {

            cursor.write(scaled::to_scaled<uint16_t>(engine_speed_2, 0.0, 0.5));

        }



        if (pv & (uint64_t{1} << 13)) {

            cursor.write(engine_speed_3_type);

        }



        if (pv & (uint64_t{1} << 14)) {

            cursor.write(scaled::to_scaled<uint16_t>(engine_speed_3, 0.0, 0.5));

        }



        if (pv & (uint64_t{1} << 15)) {

            cursor.write(scaled::to_scaled<int8_t>(propeller_pitch_angle, 0.0, 0.02));

        }



        if (pv & (uint64_t{1} << 16)) {

            cursor.write(output_power_shaft_torque_status);

        }



        if (pv & (uint64_t{1} << 17)) {

            cursor.write(engine_temperature_1_type);

        }



        if (pv & (uint64_t{1} << 18)) {

            cursor.write(scaled::to_scaled<uint16_t>(engine_temperature_1, 0.0, 0.5));

        }



        if (pv & (uint64_t{1} << 19)) {

            cursor.write(engine_temperature_2_type);

        }



        if (pv & (uint64_t{1} << 20)) {

            cursor.write(scaled::to_scaled<uint16_t>(engine_temperature_2, 0.0, 0.5));

        }



        if (pv & (uint64_t{1} << 21)) {

            cursor.write(engine_temperature_3_type);

        }



        if (pv & (uint64_t{1} << 22)) {

            cursor.write(scaled::to_scaled<uint16_t>(engine_temperature_3, 0.0, 0.5));

        }



        if (pv & (uint64_t{1} << 23)) {

            cursor.write(engine_temperature_4_type);

        }



        if (pv & (uint64_t{1} << 24)) {

            cursor.write(scaled::to_scaled<uint16_t>(engine_temperature_4, 0.0, 0.5));

        }



        if (pv & (uint64_t{1} << 25)) {

            cursor.write(engine_pressure_1_type);

        }



        if (pv & (uint64_t{1} << 26)) {

            cursor.write(scaled::to_scaled<uint16_t>(engine_pressure_1, 0.0, 10.0));

        }



        if (pv & (uint64_t{1} << 27)) {

            cursor.write(engine_pressure_1_status);

        }



        if (pv & (uint64_t{1} << 28)) {

            cursor.write(engine_pressure_2_type);

        }



        if (pv & (uint64_t{1} << 29)) {

            cursor.write(scaled::to_scaled<uint16_t>(engine_pressure_2, 0.0, 10.0));

        }



        if (pv & (uint64_t{1} << 30)) {

            cursor.write(engine_pressure_2_status);

        }



        if (pv & (uint64_t{1} << 31)) {

            cursor.write(fire_detection_sensor_status);

        }



        if (pv & (uint64_t{1} << 32)) {

            cursor.write_int(scaled::to_scaled<uint32_t>(engine_energy_flow, 0.0, 0.0017), 3);

        }



        if (pv & (uint64_t{1} << 33)) {

            cursor.write(engine_body_temperature_status);

        }



        if (pv & (uint64_t{1} << 34)) {

            cursor.write(exhaust_gas_temperature_status);

        }



        if (pv & (uint64_t{1} << 35)) {

            cursor.write(coolant_temperature_status);

        }



        if (pv & (uint64_t{1} << 36)) {

            cursor.write(lubricant_temperature_status);

        }


    }

    void deserialize(BitCursor& cursor) {
        uint64_t pv = 0;
        cursor.read_int(pv, 5);

        // Read Fields


        if (pv & (uint64_t{1} << 0)) {
            has_time_stamp = true;
            cursor.read_int(time_stamp, 5);
        }



        if (pv & (uint64_t{1} << 1)) {
            has_engine_number = true;
            cursor.read(engine_number);
        }



        if (pv & (uint64_t{1} << 2)) {
            has_engine_status = true;
            cursor.read(engine_status);
        }



        if (pv & (uint64_t{1} << 3)) {
            has_reported_engine_command = true;
            cursor.read(reported_engine_command);
        }



        if (pv & (uint64_t{1} << 4)) {
            has_reverse_thrust_power_status = true;
            cursor.read(reverse_thrust_power_status);
        }



        if (pv & (uint64_t{1} << 5)) {
            has_reported_reverse_thrust = true;
            cursor.read(reported_reverse_thrust);
        }



        if (pv & (uint64_t{1} << 6)) {
            has_ignition_switch_power_status = true;
            cursor.read(ignition_switch_power_status);
        }



        if (pv & (uint64_t{1} << 7)) {
            has_ignition_switch_activation = true;
            cursor.read(ignition_switch_activation);
        }



        if (pv & (uint64_t{1} << 8)) {
            has_engine_power_setting = true;
            uint16_t tmp_engine_power_setting; cursor.read(tmp_engine_power_setting); engine_power_setting = scaled::from_scaled<uint16_t, double>(tmp_engine_power_setting, 0.0, 0.0017);
        }



        if (pv & (uint64_t{1} << 9)) {
            has_engine_speed_1_type = true;
            cursor.read(engine_speed_1_type);
        }



        if (pv & (uint64_t{1} << 10)) {
            has_engine_speed_1 = true;
            uint16_t tmp_engine_speed_1; cursor.read(tmp_engine_speed_1); engine_speed_1 = scaled::from_scaled<uint16_t, double>(tmp_engine_speed_1, 0.0, 0.5);
        }



        if (pv & (uint64_t{1} << 11)) {
            has_engine_speed_2_type = true;
            cursor.read(engine_speed_2_type);
        }



        if (pv & (uint64_t{1} << 12)) {
            has_engine_speed_2 = true;
            uint16_t tmp_engine_speed_2; cursor.read(tmp_engine_speed_2); engine_speed_2 = scaled::from_scaled<uint16_t, double>(tmp_engine_speed_2, 0.0, 0.5);
        }



        if (pv & (uint64_t{1} << 13)) {
            has_engine_speed_3_type = true;
            cursor.read(engine_speed_3_type);
        }



        if (pv & (uint64_t{1} << 14)) {
            has_engine_speed_3 = true;
            uint16_t tmp_engine_speed_3; cursor.read(tmp_engine_speed_3); engine_speed_3 = scaled::from_scaled<uint16_t, double>(tmp_engine_speed_3, 0.0, 0.5);
        }



        if (pv & (uint64_t{1} << 15)) {
            has_propeller_pitch_angle = true;
            int8_t tmp_propeller_pitch_angle; cursor.read(tmp_propeller_pitch_angle); propeller_pitch_angle = scaled::from_scaled<int8_t, double>(tmp_propeller_pitch_angle, 0.0, 0.02);
        }



        if (pv & (uint64_t{1} << 16)) {
            has_output_power_shaft_torque_status = true;
            cursor.read(output_power_shaft_torque_status);
        }



        if (pv & (uint64_t{1} << 17)) {
            has_engine_temperature_1_type = true;
            cursor.read(engine_temperature_1_type);
        }



        if (pv & (uint64_t{1} << 18)) {
            has_engine_temperature_1 = true;
            uint16_t tmp_engine_temperature_1; cursor.read(tmp_engine_temperature_1); engine_temperature_1 = scaled::from_scaled<uint16_t, double>(tmp_engine_temperature_1, 0.0, 0.5);
        }



        if (pv & (uint64_t{1} << 19)) {
            has_engine_temperature_2_type = true;
            cursor.read(engine_temperature_2_type);
        }



        if (pv & (uint64_t{1} << 20)) {
            has_engine_temperature_2 = true;
            uint16_t tmp_engine_temperature_2; cursor.read(tmp_engine_temperature_2); engine_temperature_2 = scaled::from_scaled<uint16_t, double>(tmp_engine_temperature_2, 0.0, 0.5);
        }



        if (pv & (uint64_t{1} << 21)) {
            has_engine_temperature_3_type = true;
            cursor.read(engine_temperature_3_type);
        }



        if (pv & (uint64_t{1} << 22)) {
            has_engine_temperature_3 = true;
            uint16_t tmp_engine_temperature_3; cursor.read(tmp_engine_temperature_3); engine_temperature_3 = scaled::from_scaled<uint16_t, double>(tmp_engine_temperature_3, 0.0, 0.5);
        }



        if (pv & (uint64_t{1} << 23)) {
            has_engine_temperature_4_type = true;
            cursor.read(engine_temperature_4_type);
        }



        if (pv & (uint64_t{1} << 24)) {
            has_engine_temperature_4 = true;
            uint16_t tmp_engine_temperature_4; cursor.read(tmp_engine_temperature_4); engine_temperature_4 = scaled::from_scaled<uint16_t, double>(tmp_engine_temperature_4, 0.0, 0.5);
        }



        if (pv & (uint64_t{1} << 25)) {
            has_engine_pressure_1_type = true;
            cursor.read(engine_pressure_1_type);
        }



        if (pv & (uint64_t{1} << 26)) {
            has_engine_pressure_1 = true;
            uint16_t tmp_engine_pressure_1; cursor.read(tmp_engine_pressure_1); engine_pressure_1 = scaled::from_scaled<uint16_t, double>(tmp_engine_pressure_1, 0.0, 10.0);
        }



        if (pv & (uint64_t{1} << 27)) {
            has_engine_pressure_1_status = true;
            cursor.read(engine_pressure_1_status);
        }



        if (pv & (uint64_t{1} << 28)) {
            has_engine_pressure_2_type = true;
            cursor.read(engine_pressure_2_type);
        }



        if (pv & (uint64_t{1} << 29)) {
            has_engine_pressure_2 = true;
            uint16_t tmp_engine_pressure_2; cursor.read(tmp_engine_pressure_2); engine_pressure_2 = scaled::from_scaled<uint16_t, double>(tmp_engine_pressure_2, 0.0, 10.0);
        }



        if (pv & (uint64_t{1} << 30)) {
            has_engine_pressure_2_status = true;
            cursor.read(engine_pressure_2_status);
        }



        if (pv & (uint64_t{1} << 31)) {
            has_fire_detection_sensor_status = true;
            cursor.read(fire_detection_sensor_status);
        }



        if (pv & (uint64_t{1} << 32)) {
            has_engine_energy_flow = true;
            uint32_t tmp_engine_energy_flow; cursor.read_int(tmp_engine_energy_flow, 3); engine_energy_flow = scaled::from_scaled<uint32_t, double>(tmp_engine_energy_flow, 0.0, 0.0017);
        }



        if (pv & (uint64_t{1} << 33)) {
            has_engine_body_temperature_status = true;
            cursor.read(engine_body_temperature_status);
        }



        if (pv & (uint64_t{1} << 34)) {
            has_exhaust_gas_temperature_status = true;
            cursor.read(exhaust_gas_temperature_status);
        }



        if (pv & (uint64_t{1} << 35)) {
            has_coolant_temperature_status = true;
            cursor.read(coolant_temperature_status);
        }



        if (pv & (uint64_t{1} << 36)) {
            has_lubricant_temperature_status = true;
            cursor.read(lubricant_temperature_status);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_engine_number = false;



    bool has_engine_status = false;



    bool has_reported_engine_command = false;



    bool has_reverse_thrust_power_status = false;



    bool has_reported_reverse_thrust = false;



    bool has_ignition_switch_power_status = false;



    bool has_ignition_switch_activation = false;



    bool has_engine_power_setting = false;



    bool has_engine_speed_1_type = false;



    bool has_engine_speed_1 = false;



    bool has_engine_speed_2_type = false;



    bool has_engine_speed_2 = false;



    bool has_engine_speed_3_type = false;



    bool has_engine_speed_3 = false;



    bool has_propeller_pitch_angle = false;



    bool has_output_power_shaft_torque_status = false;



    bool has_engine_temperature_1_type = false;



    bool has_engine_temperature_1 = false;



    bool has_engine_temperature_2_type = false;



    bool has_engine_temperature_2 = false;



    bool has_engine_temperature_3_type = false;



    bool has_engine_temperature_3 = false;



    bool has_engine_temperature_4_type = false;



    bool has_engine_temperature_4 = false;



    bool has_engine_pressure_1_type = false;



    bool has_engine_pressure_1 = false;



    bool has_engine_pressure_1_status = false;



    bool has_engine_pressure_2_type = false;



    bool has_engine_pressure_2 = false;



    bool has_engine_pressure_2_status = false;



    bool has_fire_detection_sensor_status = false;



    bool has_engine_energy_flow = false;



    bool has_engine_body_temperature_status = false;



    bool has_exhaust_gas_temperature_status = false;



    bool has_coolant_temperature_status = false;



    bool has_lubricant_temperature_status = false;


};

} // namespace generated
} // namespace dli

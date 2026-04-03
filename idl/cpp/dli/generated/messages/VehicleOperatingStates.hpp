#pragma once

#include <dli/core/BitCursor.hpp>
#include <dli/core/Bam.hpp>
#include <dli/core/Scaled.hpp>
#include <array>
#include <cstdint>

namespace dli {
namespace generated {

/**
 * @brief Auto-generated class for Message #3002: VehicleOperatingStates
 */
class VehicleOperatingStates {
public:
    // Fields

    uint64_t time_stamp; // [ms]

    double commanded_altitude; // [m]

    uint8_t altitude_type; // [enum]

    double commanded_heading; // [rad]

    double commanded_course; // [rad]

    double commanded_turn_rate; // [rad/s]

    double commanded_roll_rate; // [rad/s]

    double commanded_speed; // [m/s]

    uint8_t speed_type; // [enum]

    int8_t power_level; // [%]

    double bingo_energy; // [%]

    double current_propulsion_energy_level; // [%]

    double current_propulsion_energy_usage_rate; // [%/s]

    double commanded_roll; // [rad]

    uint8_t altitude_command_type; // [enum]

    uint8_t heading_command_type; // [enum]

    uint8_t ua_state; // [enum]

    double thrust_direction; // [rad]

    uint8_t thrust; // [%]

    uint8_t loiter_and_waypoint_validity; // [bitmapped]

    double commanded_loiter_position_latitude; // [rad]

    double commanded_loiter_position_longitude; // [rad]

    uint8_t altitude_change_behaviour; // [enum]

    uint16_t commanded_waypoint_number;


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint64_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (uint64_t{1} << 0);



        if (has_commanded_altitude) pv |= (uint64_t{1} << 1);



        if (has_altitude_type) pv |= (uint64_t{1} << 2);



        if (has_commanded_heading) pv |= (uint64_t{1} << 3);



        if (has_commanded_course) pv |= (uint64_t{1} << 4);



        if (has_commanded_turn_rate) pv |= (uint64_t{1} << 5);



        if (has_commanded_roll_rate) pv |= (uint64_t{1} << 6);



        if (has_commanded_speed) pv |= (uint64_t{1} << 7);



        if (has_speed_type) pv |= (uint64_t{1} << 8);



        if (has_power_level) pv |= (uint64_t{1} << 9);



        if (has_bingo_energy) pv |= (uint64_t{1} << 10);



        if (has_current_propulsion_energy_level) pv |= (uint64_t{1} << 11);



        if (has_current_propulsion_energy_usage_rate) pv |= (uint64_t{1} << 12);



        if (has_commanded_roll) pv |= (uint64_t{1} << 13);



        if (has_altitude_command_type) pv |= (uint64_t{1} << 14);



        if (has_heading_command_type) pv |= (uint64_t{1} << 15);



        if (has_ua_state) pv |= (uint64_t{1} << 16);



        if (has_thrust_direction) pv |= (uint64_t{1} << 17);



        if (has_thrust) pv |= (uint64_t{1} << 18);



        if (has_loiter_and_waypoint_validity) pv |= (uint64_t{1} << 19);



        if (has_commanded_loiter_position_latitude) pv |= (uint64_t{1} << 20);



        if (has_commanded_loiter_position_longitude) pv |= (uint64_t{1} << 21);



        if (has_altitude_change_behaviour) pv |= (uint64_t{1} << 22);



        if (has_commanded_waypoint_number) pv |= (uint64_t{1} << 23);


        
        cursor.write_int(pv, 3);

        // Write Fields


        if (pv & (uint64_t{1} << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (uint64_t{1} << 1)) {

            cursor.write_int(scaled::to_scaled<int32_t>(commanded_altitude, 0.0, 0.02), 3);

        }



        if (pv & (uint64_t{1} << 2)) {

            cursor.write(altitude_type);

        }



        if (pv & (uint64_t{1} << 3)) {

            cursor.write(bam::to_bam16(commanded_heading));

        }



        if (pv & (uint64_t{1} << 4)) {

            cursor.write(bam::to_bam16(commanded_course));

        }



        if (pv & (uint64_t{1} << 5)) {

            cursor.write(scaled::to_scaled<int16_t>(commanded_turn_rate, 0.0, 0.005));

        }



        if (pv & (uint64_t{1} << 6)) {

            cursor.write(scaled::to_scaled<int16_t>(commanded_roll_rate, 0.0, 0.005));

        }



        if (pv & (uint64_t{1} << 7)) {

            cursor.write(scaled::to_scaled<uint16_t>(commanded_speed, 0.0, 0.5));

        }



        if (pv & (uint64_t{1} << 8)) {

            cursor.write(speed_type);

        }



        if (pv & (uint64_t{1} << 9)) {

            cursor.write(power_level);

        }



        if (pv & (uint64_t{1} << 10)) {

            cursor.write(scaled::to_scaled<uint16_t>(bingo_energy, 0.0, 0.0016));

        }



        if (pv & (uint64_t{1} << 11)) {

            cursor.write(scaled::to_scaled<uint16_t>(current_propulsion_energy_level, 0.0, 0.0016));

        }



        if (pv & (uint64_t{1} << 12)) {

            cursor.write(scaled::to_scaled<uint16_t>(current_propulsion_energy_usage_rate, 0.0, 0.0002));

        }



        if (pv & (uint64_t{1} << 13)) {

            cursor.write(bam::to_bam16(commanded_roll));

        }



        if (pv & (uint64_t{1} << 14)) {

            cursor.write(altitude_command_type);

        }



        if (pv & (uint64_t{1} << 15)) {

            cursor.write(heading_command_type);

        }



        if (pv & (uint64_t{1} << 16)) {

            cursor.write(ua_state);

        }



        if (pv & (uint64_t{1} << 17)) {

            cursor.write(bam::to_bam16(thrust_direction));

        }



        if (pv & (uint64_t{1} << 18)) {

            cursor.write(thrust);

        }



        if (pv & (uint64_t{1} << 19)) {

            cursor.write(loiter_and_waypoint_validity);

        }



        if (pv & (uint64_t{1} << 20)) {

            cursor.write(bam::to_bam32(commanded_loiter_position_latitude));

        }



        if (pv & (uint64_t{1} << 21)) {

            cursor.write(bam::to_bam32(commanded_loiter_position_longitude));

        }



        if (pv & (uint64_t{1} << 22)) {

            cursor.write(altitude_change_behaviour);

        }



        if (pv & (uint64_t{1} << 23)) {

            cursor.write(commanded_waypoint_number);

        }


    }

    void deserialize(BitCursor& cursor) {
        uint64_t pv = 0;
        cursor.read_int(pv, 3);

        // Read Fields


        if (pv & (uint64_t{1} << 0)) {
            has_time_stamp = true;
            cursor.read_int(time_stamp, 5);
        }



        if (pv & (uint64_t{1} << 1)) {
            has_commanded_altitude = true;
            int32_t tmp_commanded_altitude; cursor.read_int(tmp_commanded_altitude, 3); commanded_altitude = scaled::from_scaled<int32_t, double>(tmp_commanded_altitude, 0.0, 0.02);
        }



        if (pv & (uint64_t{1} << 2)) {
            has_altitude_type = true;
            cursor.read(altitude_type);
        }



        if (pv & (uint64_t{1} << 3)) {
            has_commanded_heading = true;
            uint16_t tmp_commanded_heading; cursor.read(tmp_commanded_heading); commanded_heading = bam::from_bam16(tmp_commanded_heading);
        }



        if (pv & (uint64_t{1} << 4)) {
            has_commanded_course = true;
            uint16_t tmp_commanded_course; cursor.read(tmp_commanded_course); commanded_course = bam::from_bam16(tmp_commanded_course);
        }



        if (pv & (uint64_t{1} << 5)) {
            has_commanded_turn_rate = true;
            int16_t tmp_commanded_turn_rate; cursor.read(tmp_commanded_turn_rate); commanded_turn_rate = scaled::from_scaled<int16_t, double>(tmp_commanded_turn_rate, 0.0, 0.005);
        }



        if (pv & (uint64_t{1} << 6)) {
            has_commanded_roll_rate = true;
            int16_t tmp_commanded_roll_rate; cursor.read(tmp_commanded_roll_rate); commanded_roll_rate = scaled::from_scaled<int16_t, double>(tmp_commanded_roll_rate, 0.0, 0.005);
        }



        if (pv & (uint64_t{1} << 7)) {
            has_commanded_speed = true;
            uint16_t tmp_commanded_speed; cursor.read(tmp_commanded_speed); commanded_speed = scaled::from_scaled<uint16_t, double>(tmp_commanded_speed, 0.0, 0.5);
        }



        if (pv & (uint64_t{1} << 8)) {
            has_speed_type = true;
            cursor.read(speed_type);
        }



        if (pv & (uint64_t{1} << 9)) {
            has_power_level = true;
            cursor.read(power_level);
        }



        if (pv & (uint64_t{1} << 10)) {
            has_bingo_energy = true;
            uint16_t tmp_bingo_energy; cursor.read(tmp_bingo_energy); bingo_energy = scaled::from_scaled<uint16_t, double>(tmp_bingo_energy, 0.0, 0.0016);
        }



        if (pv & (uint64_t{1} << 11)) {
            has_current_propulsion_energy_level = true;
            uint16_t tmp_current_propulsion_energy_level; cursor.read(tmp_current_propulsion_energy_level); current_propulsion_energy_level = scaled::from_scaled<uint16_t, double>(tmp_current_propulsion_energy_level, 0.0, 0.0016);
        }



        if (pv & (uint64_t{1} << 12)) {
            has_current_propulsion_energy_usage_rate = true;
            uint16_t tmp_current_propulsion_energy_usage_rate; cursor.read(tmp_current_propulsion_energy_usage_rate); current_propulsion_energy_usage_rate = scaled::from_scaled<uint16_t, double>(tmp_current_propulsion_energy_usage_rate, 0.0, 0.0002);
        }



        if (pv & (uint64_t{1} << 13)) {
            has_commanded_roll = true;
            uint16_t tmp_commanded_roll; cursor.read(tmp_commanded_roll); commanded_roll = bam::from_bam16(tmp_commanded_roll);
        }



        if (pv & (uint64_t{1} << 14)) {
            has_altitude_command_type = true;
            cursor.read(altitude_command_type);
        }



        if (pv & (uint64_t{1} << 15)) {
            has_heading_command_type = true;
            cursor.read(heading_command_type);
        }



        if (pv & (uint64_t{1} << 16)) {
            has_ua_state = true;
            cursor.read(ua_state);
        }



        if (pv & (uint64_t{1} << 17)) {
            has_thrust_direction = true;
            uint16_t tmp_thrust_direction; cursor.read(tmp_thrust_direction); thrust_direction = bam::from_bam16(tmp_thrust_direction);
        }



        if (pv & (uint64_t{1} << 18)) {
            has_thrust = true;
            cursor.read(thrust);
        }



        if (pv & (uint64_t{1} << 19)) {
            has_loiter_and_waypoint_validity = true;
            cursor.read(loiter_and_waypoint_validity);
        }



        if (pv & (uint64_t{1} << 20)) {
            has_commanded_loiter_position_latitude = true;
            uint32_t tmp_commanded_loiter_position_latitude; cursor.read(tmp_commanded_loiter_position_latitude); commanded_loiter_position_latitude = bam::from_bam32(tmp_commanded_loiter_position_latitude);
        }



        if (pv & (uint64_t{1} << 21)) {
            has_commanded_loiter_position_longitude = true;
            uint32_t tmp_commanded_loiter_position_longitude; cursor.read(tmp_commanded_loiter_position_longitude); commanded_loiter_position_longitude = bam::from_bam32(tmp_commanded_loiter_position_longitude);
        }



        if (pv & (uint64_t{1} << 22)) {
            has_altitude_change_behaviour = true;
            cursor.read(altitude_change_behaviour);
        }



        if (pv & (uint64_t{1} << 23)) {
            has_commanded_waypoint_number = true;
            cursor.read(commanded_waypoint_number);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_commanded_altitude = false;



    bool has_altitude_type = false;



    bool has_commanded_heading = false;



    bool has_commanded_course = false;



    bool has_commanded_turn_rate = false;



    bool has_commanded_roll_rate = false;



    bool has_commanded_speed = false;



    bool has_speed_type = false;



    bool has_power_level = false;



    bool has_bingo_energy = false;



    bool has_current_propulsion_energy_level = false;



    bool has_current_propulsion_energy_usage_rate = false;



    bool has_commanded_roll = false;



    bool has_altitude_command_type = false;



    bool has_heading_command_type = false;



    bool has_ua_state = false;



    bool has_thrust_direction = false;



    bool has_thrust = false;



    bool has_loiter_and_waypoint_validity = false;



    bool has_commanded_loiter_position_latitude = false;



    bool has_commanded_loiter_position_longitude = false;



    bool has_altitude_change_behaviour = false;



    bool has_commanded_waypoint_number = false;


};

} // namespace generated
} // namespace dli

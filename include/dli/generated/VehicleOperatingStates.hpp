#pragma once

#include <dli/core/BitCursor.hpp>
#include <dli/core/Bam.hpp>
#include <dli/core/Scaled.hpp>
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

    uint32_t commanded_altitude; // [m]

    uint32_t altitude_type; // [enum]

    double commanded_heading; // [rad]

    double commanded_course; // [rad]

    uint32_t commanded_turn_rate; // [rad/s]

    uint32_t commanded_roll_rate; // [rad/s]

    uint32_t commanded_speed; // [m/s]

    uint32_t speed_type; // [enum]

    uint32_t power_level; // [%]

    uint32_t bingo_energy; // [%]

    uint32_t current_energy_level; // [%]

    uint32_t current_energy_usage; // [%/s]

    double commanded_roll; // [rad]

    uint32_t altitude_command_type; // [enum]

    uint32_t heading_command_type; // [enum]

    uint32_t ua_state; // [enum]

    double thrust_direction; // [rad]


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint32_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (1 << 0);



        if (has_commanded_altitude) pv |= (1 << 1);



        if (has_altitude_type) pv |= (1 << 2);



        if (has_commanded_heading) pv |= (1 << 3);



        if (has_commanded_course) pv |= (1 << 4);



        if (has_commanded_turn_rate) pv |= (1 << 5);



        if (has_commanded_roll_rate) pv |= (1 << 6);



        if (has_commanded_speed) pv |= (1 << 7);



        if (has_speed_type) pv |= (1 << 8);



        if (has_power_level) pv |= (1 << 9);



        if (has_bingo_energy) pv |= (1 << 10);



        if (has_current_energy_level) pv |= (1 << 11);



        if (has_current_energy_usage) pv |= (1 << 12);



        if (has_commanded_roll) pv |= (1 << 13);



        if (has_altitude_command_type) pv |= (1 << 14);



        if (has_heading_command_type) pv |= (1 << 15);



        if (has_ua_state) pv |= (1 << 16);



        if (has_thrust_direction) pv |= (1 << 17);


        
        cursor.write_int(pv, 3);

        // Write Fields


        if (pv & (1 << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (1 << 1)) {

            cursor.write(commanded_altitude);

        }



        if (pv & (1 << 2)) {

            cursor.write(altitude_type);

        }



        if (pv & (1 << 3)) {

            cursor.write(bam::to_bam16(commanded_heading));

        }



        if (pv & (1 << 4)) {

            cursor.write(bam::to_bam16(commanded_course));

        }



        if (pv & (1 << 5)) {

            cursor.write(commanded_turn_rate);

        }



        if (pv & (1 << 6)) {

            cursor.write(commanded_roll_rate);

        }



        if (pv & (1 << 7)) {

            cursor.write(commanded_speed);

        }



        if (pv & (1 << 8)) {

            cursor.write(speed_type);

        }



        if (pv & (1 << 9)) {

            cursor.write(power_level);

        }



        if (pv & (1 << 10)) {

            cursor.write(bingo_energy);

        }



        if (pv & (1 << 11)) {

            cursor.write(current_energy_level);

        }



        if (pv & (1 << 12)) {

            cursor.write(current_energy_usage);

        }



        if (pv & (1 << 13)) {

            cursor.write(bam::to_bam16(commanded_roll));

        }



        if (pv & (1 << 14)) {

            cursor.write(altitude_command_type);

        }



        if (pv & (1 << 15)) {

            cursor.write(heading_command_type);

        }



        if (pv & (1 << 16)) {

            cursor.write(ua_state);

        }



        if (pv & (1 << 17)) {

            cursor.write(bam::to_bam16(thrust_direction));

        }


    }

    void deserialize(BitCursor& cursor) {
        uint32_t pv = 0;
        cursor.read_int(pv, 3);

        // Read Fields


        if (pv & (1 << 0)) {
            has_time_stamp = true;
            cursor.read_int(time_stamp, 5);
        }



        if (pv & (1 << 1)) {
            has_commanded_altitude = true;
            cursor.read(commanded_altitude);
        }



        if (pv & (1 << 2)) {
            has_altitude_type = true;
            cursor.read(altitude_type);
        }



        if (pv & (1 << 3)) {
            has_commanded_heading = true;
            uint16_t tmp_commanded_heading; cursor.read(tmp_commanded_heading); commanded_heading = bam::from_bam16(tmp_commanded_heading);
        }



        if (pv & (1 << 4)) {
            has_commanded_course = true;
            uint16_t tmp_commanded_course; cursor.read(tmp_commanded_course); commanded_course = bam::from_bam16(tmp_commanded_course);
        }



        if (pv & (1 << 5)) {
            has_commanded_turn_rate = true;
            cursor.read(commanded_turn_rate);
        }



        if (pv & (1 << 6)) {
            has_commanded_roll_rate = true;
            cursor.read(commanded_roll_rate);
        }



        if (pv & (1 << 7)) {
            has_commanded_speed = true;
            cursor.read(commanded_speed);
        }



        if (pv & (1 << 8)) {
            has_speed_type = true;
            cursor.read(speed_type);
        }



        if (pv & (1 << 9)) {
            has_power_level = true;
            cursor.read(power_level);
        }



        if (pv & (1 << 10)) {
            has_bingo_energy = true;
            cursor.read(bingo_energy);
        }



        if (pv & (1 << 11)) {
            has_current_energy_level = true;
            cursor.read(current_energy_level);
        }



        if (pv & (1 << 12)) {
            has_current_energy_usage = true;
            cursor.read(current_energy_usage);
        }



        if (pv & (1 << 13)) {
            has_commanded_roll = true;
            uint16_t tmp_commanded_roll; cursor.read(tmp_commanded_roll); commanded_roll = bam::from_bam16(tmp_commanded_roll);
        }



        if (pv & (1 << 14)) {
            has_altitude_command_type = true;
            cursor.read(altitude_command_type);
        }



        if (pv & (1 << 15)) {
            has_heading_command_type = true;
            cursor.read(heading_command_type);
        }



        if (pv & (1 << 16)) {
            has_ua_state = true;
            cursor.read(ua_state);
        }



        if (pv & (1 << 17)) {
            has_thrust_direction = true;
            uint16_t tmp_thrust_direction; cursor.read(tmp_thrust_direction); thrust_direction = bam::from_bam16(tmp_thrust_direction);
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



    bool has_current_energy_level = false;



    bool has_current_energy_usage = false;



    bool has_commanded_roll = false;



    bool has_altitude_command_type = false;



    bool has_heading_command_type = false;



    bool has_ua_state = false;



    bool has_thrust_direction = false;


};

} // namespace generated
} // namespace dli

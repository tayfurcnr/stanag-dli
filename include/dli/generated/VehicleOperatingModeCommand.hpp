#pragma once

#include <dli/core/BitCursor.hpp>
#include <dli/core/Bam.hpp>
#include <dli/core/Scaled.hpp>
#include <cstdint>

namespace dli {
namespace generated {

/**
 * @brief Auto-generated class for Message #2016: VehicleOperatingModeCommand
 */
class VehicleOperatingModeCommand {
public:
    // Fields

    uint64_t time_stamp; // [ms]

    uint32_t flight_path_control_mode; // [enum]

    uint32_t altitude_command_type; // [enum]

    uint32_t commanded_altitude; // [m]

    uint32_t commanded_vertical_speed; // [m/s]

    uint32_t heading_command_type; // [enum]

    uint32_t heading_reference; // [enum]

    double commanded_heading; // [rad]

    double commanded_course; // [rad]

    uint32_t commanded_turn_rate; // [rad/s]

    uint32_t commanded_roll_rate; // [rad/s]

    double commanded_roll; // [rad]

    uint32_t commanded_speed; // [m/s]

    uint32_t speed_type; // [enum]

    uint32_t commanded_waypoint_number;

    uint32_t altimeter_setting; // [Pa]

    uint32_t altitude_type; // [enum]

    double loiter_latitude; // [rad]

    double loiter_longitude; // [rad]

    uint32_t loiter_altitude_change; // [enum]

    double thrust_direction; // [rad]

    uint32_t thrust; // [%]

    uint32_t activity_id;


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint32_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (1 << 0);



        if (has_flight_path_control_mode) pv |= (1 << 1);



        if (has_altitude_command_type) pv |= (1 << 2);



        if (has_commanded_altitude) pv |= (1 << 3);



        if (has_commanded_vertical_speed) pv |= (1 << 4);



        if (has_heading_command_type) pv |= (1 << 5);



        if (has_heading_reference) pv |= (1 << 6);



        if (has_commanded_heading) pv |= (1 << 7);



        if (has_commanded_course) pv |= (1 << 8);



        if (has_commanded_turn_rate) pv |= (1 << 9);



        if (has_commanded_roll_rate) pv |= (1 << 10);



        if (has_commanded_roll) pv |= (1 << 11);



        if (has_commanded_speed) pv |= (1 << 12);



        if (has_speed_type) pv |= (1 << 13);



        if (has_commanded_waypoint_number) pv |= (1 << 14);



        if (has_altimeter_setting) pv |= (1 << 15);



        if (has_altitude_type) pv |= (1 << 16);



        if (has_loiter_latitude) pv |= (1 << 17);



        if (has_loiter_longitude) pv |= (1 << 18);



        if (has_loiter_altitude_change) pv |= (1 << 19);



        if (has_thrust_direction) pv |= (1 << 20);



        if (has_thrust) pv |= (1 << 21);



        if (has_activity_id) pv |= (1 << 22);


        
        cursor.write_int(pv, 3);

        // Write Fields


        if (pv & (1 << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (1 << 1)) {

            cursor.write(flight_path_control_mode);

        }



        if (pv & (1 << 2)) {

            cursor.write(altitude_command_type);

        }



        if (pv & (1 << 3)) {

            cursor.write(commanded_altitude);

        }



        if (pv & (1 << 4)) {

            cursor.write(commanded_vertical_speed);

        }



        if (pv & (1 << 5)) {

            cursor.write(heading_command_type);

        }



        if (pv & (1 << 6)) {

            cursor.write(heading_reference);

        }



        if (pv & (1 << 7)) {

            cursor.write(bam::to_bam16(commanded_heading));

        }



        if (pv & (1 << 8)) {

            cursor.write(bam::to_bam16(commanded_course));

        }



        if (pv & (1 << 9)) {

            cursor.write(commanded_turn_rate);

        }



        if (pv & (1 << 10)) {

            cursor.write(commanded_roll_rate);

        }



        if (pv & (1 << 11)) {

            cursor.write(bam::to_bam16(commanded_roll));

        }



        if (pv & (1 << 12)) {

            cursor.write(commanded_speed);

        }



        if (pv & (1 << 13)) {

            cursor.write(speed_type);

        }



        if (pv & (1 << 14)) {

            cursor.write(commanded_waypoint_number);

        }



        if (pv & (1 << 15)) {

            cursor.write(altimeter_setting);

        }



        if (pv & (1 << 16)) {

            cursor.write(altitude_type);

        }



        if (pv & (1 << 17)) {

            cursor.write(bam::to_bam32(loiter_latitude));

        }



        if (pv & (1 << 18)) {

            cursor.write(bam::to_bam32(loiter_longitude));

        }



        if (pv & (1 << 19)) {

            cursor.write(loiter_altitude_change);

        }



        if (pv & (1 << 20)) {

            cursor.write(bam::to_bam16(thrust_direction));

        }



        if (pv & (1 << 21)) {

            cursor.write(thrust);

        }



        if (pv & (1 << 22)) {

            cursor.write(activity_id);

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
            has_flight_path_control_mode = true;
            cursor.read(flight_path_control_mode);
        }



        if (pv & (1 << 2)) {
            has_altitude_command_type = true;
            cursor.read(altitude_command_type);
        }



        if (pv & (1 << 3)) {
            has_commanded_altitude = true;
            cursor.read(commanded_altitude);
        }



        if (pv & (1 << 4)) {
            has_commanded_vertical_speed = true;
            cursor.read(commanded_vertical_speed);
        }



        if (pv & (1 << 5)) {
            has_heading_command_type = true;
            cursor.read(heading_command_type);
        }



        if (pv & (1 << 6)) {
            has_heading_reference = true;
            cursor.read(heading_reference);
        }



        if (pv & (1 << 7)) {
            has_commanded_heading = true;
            uint16_t tmp_commanded_heading; cursor.read(tmp_commanded_heading); commanded_heading = bam::from_bam16(tmp_commanded_heading);
        }



        if (pv & (1 << 8)) {
            has_commanded_course = true;
            uint16_t tmp_commanded_course; cursor.read(tmp_commanded_course); commanded_course = bam::from_bam16(tmp_commanded_course);
        }



        if (pv & (1 << 9)) {
            has_commanded_turn_rate = true;
            cursor.read(commanded_turn_rate);
        }



        if (pv & (1 << 10)) {
            has_commanded_roll_rate = true;
            cursor.read(commanded_roll_rate);
        }



        if (pv & (1 << 11)) {
            has_commanded_roll = true;
            uint16_t tmp_commanded_roll; cursor.read(tmp_commanded_roll); commanded_roll = bam::from_bam16(tmp_commanded_roll);
        }



        if (pv & (1 << 12)) {
            has_commanded_speed = true;
            cursor.read(commanded_speed);
        }



        if (pv & (1 << 13)) {
            has_speed_type = true;
            cursor.read(speed_type);
        }



        if (pv & (1 << 14)) {
            has_commanded_waypoint_number = true;
            cursor.read(commanded_waypoint_number);
        }



        if (pv & (1 << 15)) {
            has_altimeter_setting = true;
            cursor.read(altimeter_setting);
        }



        if (pv & (1 << 16)) {
            has_altitude_type = true;
            cursor.read(altitude_type);
        }



        if (pv & (1 << 17)) {
            has_loiter_latitude = true;
            uint32_t tmp_loiter_latitude; cursor.read(tmp_loiter_latitude); loiter_latitude = bam::from_bam32(tmp_loiter_latitude);
        }



        if (pv & (1 << 18)) {
            has_loiter_longitude = true;
            uint32_t tmp_loiter_longitude; cursor.read(tmp_loiter_longitude); loiter_longitude = bam::from_bam32(tmp_loiter_longitude);
        }



        if (pv & (1 << 19)) {
            has_loiter_altitude_change = true;
            cursor.read(loiter_altitude_change);
        }



        if (pv & (1 << 20)) {
            has_thrust_direction = true;
            uint16_t tmp_thrust_direction; cursor.read(tmp_thrust_direction); thrust_direction = bam::from_bam16(tmp_thrust_direction);
        }



        if (pv & (1 << 21)) {
            has_thrust = true;
            cursor.read(thrust);
        }



        if (pv & (1 << 22)) {
            has_activity_id = true;
            cursor.read(activity_id);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_flight_path_control_mode = false;



    bool has_altitude_command_type = false;



    bool has_commanded_altitude = false;



    bool has_commanded_vertical_speed = false;



    bool has_heading_command_type = false;



    bool has_heading_reference = false;



    bool has_commanded_heading = false;



    bool has_commanded_course = false;



    bool has_commanded_turn_rate = false;



    bool has_commanded_roll_rate = false;



    bool has_commanded_roll = false;



    bool has_commanded_speed = false;



    bool has_speed_type = false;



    bool has_commanded_waypoint_number = false;



    bool has_altimeter_setting = false;



    bool has_altitude_type = false;



    bool has_loiter_latitude = false;



    bool has_loiter_longitude = false;



    bool has_loiter_altitude_change = false;



    bool has_thrust_direction = false;



    bool has_thrust = false;



    bool has_activity_id = false;


};

} // namespace generated
} // namespace dli

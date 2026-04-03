#pragma once

#include <dli/core/BitCursor.hpp>
#include <dli/core/Bam.hpp>
#include <dli/core/Scaled.hpp>
#include <array>
#include <cstdint>

namespace dli {
namespace generated {

/**
 * @brief Auto-generated class for Message #13002: UAPositionWaypoint
 */
class UAPositionWaypoint {
public:
    // Fields

    uint64_t time_stamp; // [ms]

    uint16_t waypoint_number;

    double waypoint_to_latitude_or_relative_y; // [rad]

    double waypoint_to_longitude_or_relative_x; // [rad]

    uint8_t location_type; // [enum]

    double waypoint_to_altitude; // [m]

    uint8_t waypoint_altitude_type; // [enum]

    uint8_t altitude_change_behaviour; // [enum]

    double waypoint_to_speed; // [m/s]

    uint8_t waypoint_speed_type; // [enum]

    uint16_t next_waypoint;

    uint8_t turn_type; // [enum]

    uint8_t optional_messages_for_waypoint; // [Bitmapped]

    uint8_t waypoint_type; // [enum]

    uint8_t limit_type; // [enum]

    uint16_t loop_limit;

    uint64_t arrival_time; // [ms]

    uint32_t activity_id;


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint64_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (uint64_t{1} << 0);



        if (has_waypoint_number) pv |= (uint64_t{1} << 1);



        if (has_waypoint_to_latitude_or_relative_y) pv |= (uint64_t{1} << 2);



        if (has_waypoint_to_longitude_or_relative_x) pv |= (uint64_t{1} << 3);



        if (has_location_type) pv |= (uint64_t{1} << 4);



        if (has_waypoint_to_altitude) pv |= (uint64_t{1} << 5);



        if (has_waypoint_altitude_type) pv |= (uint64_t{1} << 6);



        if (has_altitude_change_behaviour) pv |= (uint64_t{1} << 7);



        if (has_waypoint_to_speed) pv |= (uint64_t{1} << 8);



        if (has_waypoint_speed_type) pv |= (uint64_t{1} << 9);



        if (has_next_waypoint) pv |= (uint64_t{1} << 10);



        if (has_turn_type) pv |= (uint64_t{1} << 11);



        if (has_optional_messages_for_waypoint) pv |= (uint64_t{1} << 12);



        if (has_waypoint_type) pv |= (uint64_t{1} << 13);



        if (has_limit_type) pv |= (uint64_t{1} << 14);



        if (has_loop_limit) pv |= (uint64_t{1} << 15);



        if (has_arrival_time) pv |= (uint64_t{1} << 16);



        if (has_activity_id) pv |= (uint64_t{1} << 17);


        
        cursor.write_int(pv, 3);

        // Write Fields


        if (pv & (uint64_t{1} << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (uint64_t{1} << 1)) {

            cursor.write(waypoint_number);

        }



        if (pv & (uint64_t{1} << 2)) {

            cursor.write(bam::to_bam32(waypoint_to_latitude_or_relative_y));

        }



        if (pv & (uint64_t{1} << 3)) {

            cursor.write(bam::to_bam32(waypoint_to_longitude_or_relative_x));

        }



        if (pv & (uint64_t{1} << 4)) {

            cursor.write(location_type);

        }



        if (pv & (uint64_t{1} << 5)) {

            cursor.write_int(scaled::to_scaled<int32_t>(waypoint_to_altitude, 0.0, 0.02), 3);

        }



        if (pv & (uint64_t{1} << 6)) {

            cursor.write(waypoint_altitude_type);

        }



        if (pv & (uint64_t{1} << 7)) {

            cursor.write(altitude_change_behaviour);

        }



        if (pv & (uint64_t{1} << 8)) {

            cursor.write(scaled::to_scaled<uint16_t>(waypoint_to_speed, 0.0, 0.5));

        }



        if (pv & (uint64_t{1} << 9)) {

            cursor.write(waypoint_speed_type);

        }



        if (pv & (uint64_t{1} << 10)) {

            cursor.write(next_waypoint);

        }



        if (pv & (uint64_t{1} << 11)) {

            cursor.write(turn_type);

        }



        if (pv & (uint64_t{1} << 12)) {

            cursor.write(optional_messages_for_waypoint);

        }



        if (pv & (uint64_t{1} << 13)) {

            cursor.write(waypoint_type);

        }



        if (pv & (uint64_t{1} << 14)) {

            cursor.write(limit_type);

        }



        if (pv & (uint64_t{1} << 15)) {

            cursor.write(loop_limit);

        }



        if (pv & (uint64_t{1} << 16)) {

            cursor.write_int(arrival_time, 5);

        }



        if (pv & (uint64_t{1} << 17)) {

            cursor.write_int(activity_id, 3);

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
            has_waypoint_number = true;
            cursor.read(waypoint_number);
        }



        if (pv & (uint64_t{1} << 2)) {
            has_waypoint_to_latitude_or_relative_y = true;
            uint32_t tmp_waypoint_to_latitude_or_relative_y; cursor.read(tmp_waypoint_to_latitude_or_relative_y); waypoint_to_latitude_or_relative_y = bam::from_bam32(tmp_waypoint_to_latitude_or_relative_y);
        }



        if (pv & (uint64_t{1} << 3)) {
            has_waypoint_to_longitude_or_relative_x = true;
            uint32_t tmp_waypoint_to_longitude_or_relative_x; cursor.read(tmp_waypoint_to_longitude_or_relative_x); waypoint_to_longitude_or_relative_x = bam::from_bam32(tmp_waypoint_to_longitude_or_relative_x);
        }



        if (pv & (uint64_t{1} << 4)) {
            has_location_type = true;
            cursor.read(location_type);
        }



        if (pv & (uint64_t{1} << 5)) {
            has_waypoint_to_altitude = true;
            int32_t tmp_waypoint_to_altitude; cursor.read_int(tmp_waypoint_to_altitude, 3); waypoint_to_altitude = scaled::from_scaled<int32_t, double>(tmp_waypoint_to_altitude, 0.0, 0.02);
        }



        if (pv & (uint64_t{1} << 6)) {
            has_waypoint_altitude_type = true;
            cursor.read(waypoint_altitude_type);
        }



        if (pv & (uint64_t{1} << 7)) {
            has_altitude_change_behaviour = true;
            cursor.read(altitude_change_behaviour);
        }



        if (pv & (uint64_t{1} << 8)) {
            has_waypoint_to_speed = true;
            uint16_t tmp_waypoint_to_speed; cursor.read(tmp_waypoint_to_speed); waypoint_to_speed = scaled::from_scaled<uint16_t, double>(tmp_waypoint_to_speed, 0.0, 0.5);
        }



        if (pv & (uint64_t{1} << 9)) {
            has_waypoint_speed_type = true;
            cursor.read(waypoint_speed_type);
        }



        if (pv & (uint64_t{1} << 10)) {
            has_next_waypoint = true;
            cursor.read(next_waypoint);
        }



        if (pv & (uint64_t{1} << 11)) {
            has_turn_type = true;
            cursor.read(turn_type);
        }



        if (pv & (uint64_t{1} << 12)) {
            has_optional_messages_for_waypoint = true;
            cursor.read(optional_messages_for_waypoint);
        }



        if (pv & (uint64_t{1} << 13)) {
            has_waypoint_type = true;
            cursor.read(waypoint_type);
        }



        if (pv & (uint64_t{1} << 14)) {
            has_limit_type = true;
            cursor.read(limit_type);
        }



        if (pv & (uint64_t{1} << 15)) {
            has_loop_limit = true;
            cursor.read(loop_limit);
        }



        if (pv & (uint64_t{1} << 16)) {
            has_arrival_time = true;
            cursor.read_int(arrival_time, 5);
        }



        if (pv & (uint64_t{1} << 17)) {
            has_activity_id = true;
            cursor.read_int(activity_id, 3);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_waypoint_number = false;



    bool has_waypoint_to_latitude_or_relative_y = false;



    bool has_waypoint_to_longitude_or_relative_x = false;



    bool has_location_type = false;



    bool has_waypoint_to_altitude = false;



    bool has_waypoint_altitude_type = false;



    bool has_altitude_change_behaviour = false;



    bool has_waypoint_to_speed = false;



    bool has_waypoint_speed_type = false;



    bool has_next_waypoint = false;



    bool has_turn_type = false;



    bool has_optional_messages_for_waypoint = false;



    bool has_waypoint_type = false;



    bool has_limit_type = false;



    bool has_loop_limit = false;



    bool has_arrival_time = false;



    bool has_activity_id = false;


};

} // namespace generated
} // namespace dli

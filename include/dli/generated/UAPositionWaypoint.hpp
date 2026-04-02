#pragma once

#include "../BitCursor.hpp"
#include "../Bam.hpp"
#include "../Scaled.hpp"
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

    uint32_t waypoint_number;

    double waypoint_latitude; // [rad]

    double waypoint_longitude; // [rad]

    uint32_t location_type; // [enum]

    uint32_t waypoint_altitude; // [m]

    uint32_t altitude_type; // [enum]

    uint32_t altitude_change; // [enum]

    uint32_t waypoint_speed; // [m/s]

    uint32_t speed_type; // [enum]

    uint32_t next_waypoint;

    uint32_t turn_type; // [enum]

    uint32_t optional_messages; // [Bitmapped]

    uint32_t waypoint_type; // [enum]

    uint32_t limit_type; // [enum]

    uint32_t loop_limit;

    uint32_t activity_id;


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint32_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (1 << 0);



        if (has_waypoint_number) pv |= (1 << 1);



        if (has_waypoint_latitude) pv |= (1 << 2);



        if (has_waypoint_longitude) pv |= (1 << 3);



        if (has_location_type) pv |= (1 << 4);



        if (has_waypoint_altitude) pv |= (1 << 5);



        if (has_altitude_type) pv |= (1 << 6);



        if (has_altitude_change) pv |= (1 << 7);



        if (has_waypoint_speed) pv |= (1 << 8);



        if (has_speed_type) pv |= (1 << 9);



        if (has_next_waypoint) pv |= (1 << 10);



        if (has_turn_type) pv |= (1 << 11);



        if (has_optional_messages) pv |= (1 << 12);



        if (has_waypoint_type) pv |= (1 << 13);



        if (has_limit_type) pv |= (1 << 14);



        if (has_loop_limit) pv |= (1 << 15);



        if (has_activity_id) pv |= (1 << 16);


        
        cursor.write_int(pv, 3);

        // Write Fields


        if (pv & (1 << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (1 << 1)) {

            cursor.write(waypoint_number);

        }



        if (pv & (1 << 2)) {

            cursor.write(bam::to_bam32(waypoint_latitude));

        }



        if (pv & (1 << 3)) {

            cursor.write(bam::to_bam32(waypoint_longitude));

        }



        if (pv & (1 << 4)) {

            cursor.write(location_type);

        }



        if (pv & (1 << 5)) {

            cursor.write(waypoint_altitude);

        }



        if (pv & (1 << 6)) {

            cursor.write(altitude_type);

        }



        if (pv & (1 << 7)) {

            cursor.write(altitude_change);

        }



        if (pv & (1 << 8)) {

            cursor.write(waypoint_speed);

        }



        if (pv & (1 << 9)) {

            cursor.write(speed_type);

        }



        if (pv & (1 << 10)) {

            cursor.write(next_waypoint);

        }



        if (pv & (1 << 11)) {

            cursor.write(turn_type);

        }



        if (pv & (1 << 12)) {

            cursor.write(optional_messages);

        }



        if (pv & (1 << 13)) {

            cursor.write(waypoint_type);

        }



        if (pv & (1 << 14)) {

            cursor.write(limit_type);

        }



        if (pv & (1 << 15)) {

            cursor.write(loop_limit);

        }



        if (pv & (1 << 16)) {

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
            has_waypoint_number = true;
            cursor.read(waypoint_number);
        }



        if (pv & (1 << 2)) {
            has_waypoint_latitude = true;
            uint32_t tmp_waypoint_latitude; cursor.read(tmp_waypoint_latitude); waypoint_latitude = bam::from_bam32(tmp_waypoint_latitude);
        }



        if (pv & (1 << 3)) {
            has_waypoint_longitude = true;
            uint32_t tmp_waypoint_longitude; cursor.read(tmp_waypoint_longitude); waypoint_longitude = bam::from_bam32(tmp_waypoint_longitude);
        }



        if (pv & (1 << 4)) {
            has_location_type = true;
            cursor.read(location_type);
        }



        if (pv & (1 << 5)) {
            has_waypoint_altitude = true;
            cursor.read(waypoint_altitude);
        }



        if (pv & (1 << 6)) {
            has_altitude_type = true;
            cursor.read(altitude_type);
        }



        if (pv & (1 << 7)) {
            has_altitude_change = true;
            cursor.read(altitude_change);
        }



        if (pv & (1 << 8)) {
            has_waypoint_speed = true;
            cursor.read(waypoint_speed);
        }



        if (pv & (1 << 9)) {
            has_speed_type = true;
            cursor.read(speed_type);
        }



        if (pv & (1 << 10)) {
            has_next_waypoint = true;
            cursor.read(next_waypoint);
        }



        if (pv & (1 << 11)) {
            has_turn_type = true;
            cursor.read(turn_type);
        }



        if (pv & (1 << 12)) {
            has_optional_messages = true;
            cursor.read(optional_messages);
        }



        if (pv & (1 << 13)) {
            has_waypoint_type = true;
            cursor.read(waypoint_type);
        }



        if (pv & (1 << 14)) {
            has_limit_type = true;
            cursor.read(limit_type);
        }



        if (pv & (1 << 15)) {
            has_loop_limit = true;
            cursor.read(loop_limit);
        }



        if (pv & (1 << 16)) {
            has_activity_id = true;
            cursor.read(activity_id);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_waypoint_number = false;



    bool has_waypoint_latitude = false;



    bool has_waypoint_longitude = false;



    bool has_location_type = false;



    bool has_waypoint_altitude = false;



    bool has_altitude_type = false;



    bool has_altitude_change = false;



    bool has_waypoint_speed = false;



    bool has_speed_type = false;



    bool has_next_waypoint = false;



    bool has_turn_type = false;



    bool has_optional_messages = false;



    bool has_waypoint_type = false;



    bool has_limit_type = false;



    bool has_loop_limit = false;



    bool has_activity_id = false;


};

} // namespace generated
} // namespace dli

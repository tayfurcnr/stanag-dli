#pragma once

#include <dli/core/BitCursor.hpp>
#include <dli/core/Bam.hpp>
#include <dli/core/Scaled.hpp>
#include <cstdint>

namespace dli {
namespace generated {

/**
 * @brief Auto-generated class for Message #4001: FromToNextWaypointStates
 */
class FromToNextWaypointStates {
public:
    // Fields

    uint64_t time_stamp; // [ms]

    uint32_t altitude_type; // [enum]

    uint32_t speed_type; // [enum]

    double from_waypoint_latitude; // [rad]

    double from_waypoint_longitude; // [rad]

    uint32_t from_waypoint_altitude; // [m]

    uint64_t from_waypoint_time; // [ms]

    uint32_t from_waypoint_number;

    double to_waypoint_latitude; // [rad]

    double to_waypoint_longitude; // [rad]

    uint32_t to_waypoint_altitude; // [m]

    uint32_t to_waypoint_speed; // [m/s]

    uint64_t to_waypoint_time; // [ms]

    uint32_t to_waypoint_number;

    double next_waypoint_latitude; // [rad]

    double next_waypoint_longitude; // [rad]

    uint32_t next_waypoint_altitude; // [m]

    uint32_t next_waypoint_speed; // [m/s]

    uint64_t next_waypoint_time; // [ms]

    uint32_t next_waypoint_number;

    uint32_t loiter_valid_for_to_wp; // [enum]


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint32_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (1 << 0);



        if (has_altitude_type) pv |= (1 << 1);



        if (has_speed_type) pv |= (1 << 2);



        if (has_from_waypoint_latitude) pv |= (1 << 3);



        if (has_from_waypoint_longitude) pv |= (1 << 4);



        if (has_from_waypoint_altitude) pv |= (1 << 5);



        if (has_from_waypoint_time) pv |= (1 << 6);



        if (has_from_waypoint_number) pv |= (1 << 7);



        if (has_to_waypoint_latitude) pv |= (1 << 8);



        if (has_to_waypoint_longitude) pv |= (1 << 9);



        if (has_to_waypoint_altitude) pv |= (1 << 10);



        if (has_to_waypoint_speed) pv |= (1 << 11);



        if (has_to_waypoint_time) pv |= (1 << 12);



        if (has_to_waypoint_number) pv |= (1 << 13);



        if (has_next_waypoint_latitude) pv |= (1 << 14);



        if (has_next_waypoint_longitude) pv |= (1 << 15);



        if (has_next_waypoint_altitude) pv |= (1 << 16);



        if (has_next_waypoint_speed) pv |= (1 << 17);



        if (has_next_waypoint_time) pv |= (1 << 18);



        if (has_next_waypoint_number) pv |= (1 << 19);



        if (has_loiter_valid_for_to_wp) pv |= (1 << 20);


        
        cursor.write_int(pv, 3);

        // Write Fields


        if (pv & (1 << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (1 << 1)) {

            cursor.write(altitude_type);

        }



        if (pv & (1 << 2)) {

            cursor.write(speed_type);

        }



        if (pv & (1 << 3)) {

            cursor.write(bam::to_bam32(from_waypoint_latitude));

        }



        if (pv & (1 << 4)) {

            cursor.write(bam::to_bam32(from_waypoint_longitude));

        }



        if (pv & (1 << 5)) {

            cursor.write(from_waypoint_altitude);

        }



        if (pv & (1 << 6)) {

            cursor.write_int(from_waypoint_time, 5);

        }



        if (pv & (1 << 7)) {

            cursor.write(from_waypoint_number);

        }



        if (pv & (1 << 8)) {

            cursor.write(bam::to_bam32(to_waypoint_latitude));

        }



        if (pv & (1 << 9)) {

            cursor.write(bam::to_bam32(to_waypoint_longitude));

        }



        if (pv & (1 << 10)) {

            cursor.write(to_waypoint_altitude);

        }



        if (pv & (1 << 11)) {

            cursor.write(to_waypoint_speed);

        }



        if (pv & (1 << 12)) {

            cursor.write_int(to_waypoint_time, 5);

        }



        if (pv & (1 << 13)) {

            cursor.write(to_waypoint_number);

        }



        if (pv & (1 << 14)) {

            cursor.write(bam::to_bam32(next_waypoint_latitude));

        }



        if (pv & (1 << 15)) {

            cursor.write(bam::to_bam32(next_waypoint_longitude));

        }



        if (pv & (1 << 16)) {

            cursor.write(next_waypoint_altitude);

        }



        if (pv & (1 << 17)) {

            cursor.write(next_waypoint_speed);

        }



        if (pv & (1 << 18)) {

            cursor.write_int(next_waypoint_time, 5);

        }



        if (pv & (1 << 19)) {

            cursor.write(next_waypoint_number);

        }



        if (pv & (1 << 20)) {

            cursor.write(loiter_valid_for_to_wp);

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
            has_altitude_type = true;
            cursor.read(altitude_type);
        }



        if (pv & (1 << 2)) {
            has_speed_type = true;
            cursor.read(speed_type);
        }



        if (pv & (1 << 3)) {
            has_from_waypoint_latitude = true;
            uint32_t tmp_from_waypoint_latitude; cursor.read(tmp_from_waypoint_latitude); from_waypoint_latitude = bam::from_bam32(tmp_from_waypoint_latitude);
        }



        if (pv & (1 << 4)) {
            has_from_waypoint_longitude = true;
            uint32_t tmp_from_waypoint_longitude; cursor.read(tmp_from_waypoint_longitude); from_waypoint_longitude = bam::from_bam32(tmp_from_waypoint_longitude);
        }



        if (pv & (1 << 5)) {
            has_from_waypoint_altitude = true;
            cursor.read(from_waypoint_altitude);
        }



        if (pv & (1 << 6)) {
            has_from_waypoint_time = true;
            cursor.read_int(from_waypoint_time, 5);
        }



        if (pv & (1 << 7)) {
            has_from_waypoint_number = true;
            cursor.read(from_waypoint_number);
        }



        if (pv & (1 << 8)) {
            has_to_waypoint_latitude = true;
            uint32_t tmp_to_waypoint_latitude; cursor.read(tmp_to_waypoint_latitude); to_waypoint_latitude = bam::from_bam32(tmp_to_waypoint_latitude);
        }



        if (pv & (1 << 9)) {
            has_to_waypoint_longitude = true;
            uint32_t tmp_to_waypoint_longitude; cursor.read(tmp_to_waypoint_longitude); to_waypoint_longitude = bam::from_bam32(tmp_to_waypoint_longitude);
        }



        if (pv & (1 << 10)) {
            has_to_waypoint_altitude = true;
            cursor.read(to_waypoint_altitude);
        }



        if (pv & (1 << 11)) {
            has_to_waypoint_speed = true;
            cursor.read(to_waypoint_speed);
        }



        if (pv & (1 << 12)) {
            has_to_waypoint_time = true;
            cursor.read_int(to_waypoint_time, 5);
        }



        if (pv & (1 << 13)) {
            has_to_waypoint_number = true;
            cursor.read(to_waypoint_number);
        }



        if (pv & (1 << 14)) {
            has_next_waypoint_latitude = true;
            uint32_t tmp_next_waypoint_latitude; cursor.read(tmp_next_waypoint_latitude); next_waypoint_latitude = bam::from_bam32(tmp_next_waypoint_latitude);
        }



        if (pv & (1 << 15)) {
            has_next_waypoint_longitude = true;
            uint32_t tmp_next_waypoint_longitude; cursor.read(tmp_next_waypoint_longitude); next_waypoint_longitude = bam::from_bam32(tmp_next_waypoint_longitude);
        }



        if (pv & (1 << 16)) {
            has_next_waypoint_altitude = true;
            cursor.read(next_waypoint_altitude);
        }



        if (pv & (1 << 17)) {
            has_next_waypoint_speed = true;
            cursor.read(next_waypoint_speed);
        }



        if (pv & (1 << 18)) {
            has_next_waypoint_time = true;
            cursor.read_int(next_waypoint_time, 5);
        }



        if (pv & (1 << 19)) {
            has_next_waypoint_number = true;
            cursor.read(next_waypoint_number);
        }



        if (pv & (1 << 20)) {
            has_loiter_valid_for_to_wp = true;
            cursor.read(loiter_valid_for_to_wp);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_altitude_type = false;



    bool has_speed_type = false;



    bool has_from_waypoint_latitude = false;



    bool has_from_waypoint_longitude = false;



    bool has_from_waypoint_altitude = false;



    bool has_from_waypoint_time = false;



    bool has_from_waypoint_number = false;



    bool has_to_waypoint_latitude = false;



    bool has_to_waypoint_longitude = false;



    bool has_to_waypoint_altitude = false;



    bool has_to_waypoint_speed = false;



    bool has_to_waypoint_time = false;



    bool has_to_waypoint_number = false;



    bool has_next_waypoint_latitude = false;



    bool has_next_waypoint_longitude = false;



    bool has_next_waypoint_altitude = false;



    bool has_next_waypoint_speed = false;



    bool has_next_waypoint_time = false;



    bool has_next_waypoint_number = false;



    bool has_loiter_valid_for_to_wp = false;


};

} // namespace generated
} // namespace dli

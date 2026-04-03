#pragma once

#include <dli/core/BitCursor.hpp>
#include <dli/core/Bam.hpp>
#include <dli/core/Scaled.hpp>
#include <array>
#include <cstdint>

namespace dli {
namespace generated {

/**
 * @brief Auto-generated class for Message #3011: UAStickStatus
 */
class UAStickStatus {
public:
    // Fields

    uint64_t time_stamp; // [ms]

    int8_t lateral_stick;

    int8_t longitudinal_stick;

    int8_t rotational_stick_rudder;

    uint8_t throttle_stick___engine_1;

    int8_t pitch_stick___engine_1;

    uint8_t throttle_stick___engine_2;

    int8_t pitch_stick___engine_2;

    uint8_t throttle_stick___engine_3;

    int8_t pitch_stick___engine_3;

    uint8_t throttle_stick___engine_4;

    int8_t pitch_stick___engine_4;

    int8_t taxi_stick;


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint64_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (uint64_t{1} << 0);



        if (has_lateral_stick) pv |= (uint64_t{1} << 1);



        if (has_longitudinal_stick) pv |= (uint64_t{1} << 2);



        if (has_rotational_stick_rudder) pv |= (uint64_t{1} << 3);



        if (has_throttle_stick___engine_1) pv |= (uint64_t{1} << 4);



        if (has_pitch_stick___engine_1) pv |= (uint64_t{1} << 5);



        if (has_throttle_stick___engine_2) pv |= (uint64_t{1} << 6);



        if (has_pitch_stick___engine_2) pv |= (uint64_t{1} << 7);



        if (has_throttle_stick___engine_3) pv |= (uint64_t{1} << 8);



        if (has_pitch_stick___engine_3) pv |= (uint64_t{1} << 9);



        if (has_throttle_stick___engine_4) pv |= (uint64_t{1} << 10);



        if (has_pitch_stick___engine_4) pv |= (uint64_t{1} << 11);



        if (has_taxi_stick) pv |= (uint64_t{1} << 12);


        
        cursor.write_int(pv, 2);

        // Write Fields


        if (pv & (uint64_t{1} << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (uint64_t{1} << 1)) {

            cursor.write(lateral_stick);

        }



        if (pv & (uint64_t{1} << 2)) {

            cursor.write(longitudinal_stick);

        }



        if (pv & (uint64_t{1} << 3)) {

            cursor.write(rotational_stick_rudder);

        }



        if (pv & (uint64_t{1} << 4)) {

            cursor.write(throttle_stick___engine_1);

        }



        if (pv & (uint64_t{1} << 5)) {

            cursor.write(pitch_stick___engine_1);

        }



        if (pv & (uint64_t{1} << 6)) {

            cursor.write(throttle_stick___engine_2);

        }



        if (pv & (uint64_t{1} << 7)) {

            cursor.write(pitch_stick___engine_2);

        }



        if (pv & (uint64_t{1} << 8)) {

            cursor.write(throttle_stick___engine_3);

        }



        if (pv & (uint64_t{1} << 9)) {

            cursor.write(pitch_stick___engine_3);

        }



        if (pv & (uint64_t{1} << 10)) {

            cursor.write(throttle_stick___engine_4);

        }



        if (pv & (uint64_t{1} << 11)) {

            cursor.write(pitch_stick___engine_4);

        }



        if (pv & (uint64_t{1} << 12)) {

            cursor.write(taxi_stick);

        }


    }

    void deserialize(BitCursor& cursor) {
        uint64_t pv = 0;
        cursor.read_int(pv, 2);

        // Read Fields


        if (pv & (uint64_t{1} << 0)) {
            has_time_stamp = true;
            cursor.read_int(time_stamp, 5);
        }



        if (pv & (uint64_t{1} << 1)) {
            has_lateral_stick = true;
            cursor.read(lateral_stick);
        }



        if (pv & (uint64_t{1} << 2)) {
            has_longitudinal_stick = true;
            cursor.read(longitudinal_stick);
        }



        if (pv & (uint64_t{1} << 3)) {
            has_rotational_stick_rudder = true;
            cursor.read(rotational_stick_rudder);
        }



        if (pv & (uint64_t{1} << 4)) {
            has_throttle_stick___engine_1 = true;
            cursor.read(throttle_stick___engine_1);
        }



        if (pv & (uint64_t{1} << 5)) {
            has_pitch_stick___engine_1 = true;
            cursor.read(pitch_stick___engine_1);
        }



        if (pv & (uint64_t{1} << 6)) {
            has_throttle_stick___engine_2 = true;
            cursor.read(throttle_stick___engine_2);
        }



        if (pv & (uint64_t{1} << 7)) {
            has_pitch_stick___engine_2 = true;
            cursor.read(pitch_stick___engine_2);
        }



        if (pv & (uint64_t{1} << 8)) {
            has_throttle_stick___engine_3 = true;
            cursor.read(throttle_stick___engine_3);
        }



        if (pv & (uint64_t{1} << 9)) {
            has_pitch_stick___engine_3 = true;
            cursor.read(pitch_stick___engine_3);
        }



        if (pv & (uint64_t{1} << 10)) {
            has_throttle_stick___engine_4 = true;
            cursor.read(throttle_stick___engine_4);
        }



        if (pv & (uint64_t{1} << 11)) {
            has_pitch_stick___engine_4 = true;
            cursor.read(pitch_stick___engine_4);
        }



        if (pv & (uint64_t{1} << 12)) {
            has_taxi_stick = true;
            cursor.read(taxi_stick);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_lateral_stick = false;



    bool has_longitudinal_stick = false;



    bool has_rotational_stick_rudder = false;



    bool has_throttle_stick___engine_1 = false;



    bool has_pitch_stick___engine_1 = false;



    bool has_throttle_stick___engine_2 = false;



    bool has_pitch_stick___engine_2 = false;



    bool has_throttle_stick___engine_3 = false;



    bool has_pitch_stick___engine_3 = false;



    bool has_throttle_stick___engine_4 = false;



    bool has_pitch_stick___engine_4 = false;



    bool has_taxi_stick = false;


};

} // namespace generated
} // namespace dli

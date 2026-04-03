#pragma once

#include <dli/core/BitCursor.hpp>
#include <dli/core/Bam.hpp>
#include <dli/core/Scaled.hpp>
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

    uint32_t lateral_stick;

    uint32_t longitudinal_stick;

    uint32_t rotational_stick;

    uint32_t throttle_stick_eng1;

    uint32_t pitch_stick_eng1;

    uint32_t throttle_stick_eng2;

    uint32_t pitch_stick_eng2;

    uint32_t throttle_stick_eng3;

    uint32_t pitch_stick_eng3;

    uint32_t throttle_stick_eng4;

    uint32_t pitch_stick_eng4;

    uint32_t taxi_stick;


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint32_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (1 << 0);



        if (has_lateral_stick) pv |= (1 << 1);



        if (has_longitudinal_stick) pv |= (1 << 2);



        if (has_rotational_stick) pv |= (1 << 3);



        if (has_throttle_stick_eng1) pv |= (1 << 4);



        if (has_pitch_stick_eng1) pv |= (1 << 5);



        if (has_throttle_stick_eng2) pv |= (1 << 6);



        if (has_pitch_stick_eng2) pv |= (1 << 7);



        if (has_throttle_stick_eng3) pv |= (1 << 8);



        if (has_pitch_stick_eng3) pv |= (1 << 9);



        if (has_throttle_stick_eng4) pv |= (1 << 10);



        if (has_pitch_stick_eng4) pv |= (1 << 11);



        if (has_taxi_stick) pv |= (1 << 12);


        
        cursor.write_int(pv, 2);

        // Write Fields


        if (pv & (1 << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (1 << 1)) {

            cursor.write(lateral_stick);

        }



        if (pv & (1 << 2)) {

            cursor.write(longitudinal_stick);

        }



        if (pv & (1 << 3)) {

            cursor.write(rotational_stick);

        }



        if (pv & (1 << 4)) {

            cursor.write(throttle_stick_eng1);

        }



        if (pv & (1 << 5)) {

            cursor.write(pitch_stick_eng1);

        }



        if (pv & (1 << 6)) {

            cursor.write(throttle_stick_eng2);

        }



        if (pv & (1 << 7)) {

            cursor.write(pitch_stick_eng2);

        }



        if (pv & (1 << 8)) {

            cursor.write(throttle_stick_eng3);

        }



        if (pv & (1 << 9)) {

            cursor.write(pitch_stick_eng3);

        }



        if (pv & (1 << 10)) {

            cursor.write(throttle_stick_eng4);

        }



        if (pv & (1 << 11)) {

            cursor.write(pitch_stick_eng4);

        }



        if (pv & (1 << 12)) {

            cursor.write(taxi_stick);

        }


    }

    void deserialize(BitCursor& cursor) {
        uint32_t pv = 0;
        cursor.read_int(pv, 2);

        // Read Fields


        if (pv & (1 << 0)) {
            has_time_stamp = true;
            cursor.read_int(time_stamp, 5);
        }



        if (pv & (1 << 1)) {
            has_lateral_stick = true;
            cursor.read(lateral_stick);
        }



        if (pv & (1 << 2)) {
            has_longitudinal_stick = true;
            cursor.read(longitudinal_stick);
        }



        if (pv & (1 << 3)) {
            has_rotational_stick = true;
            cursor.read(rotational_stick);
        }



        if (pv & (1 << 4)) {
            has_throttle_stick_eng1 = true;
            cursor.read(throttle_stick_eng1);
        }



        if (pv & (1 << 5)) {
            has_pitch_stick_eng1 = true;
            cursor.read(pitch_stick_eng1);
        }



        if (pv & (1 << 6)) {
            has_throttle_stick_eng2 = true;
            cursor.read(throttle_stick_eng2);
        }



        if (pv & (1 << 7)) {
            has_pitch_stick_eng2 = true;
            cursor.read(pitch_stick_eng2);
        }



        if (pv & (1 << 8)) {
            has_throttle_stick_eng3 = true;
            cursor.read(throttle_stick_eng3);
        }



        if (pv & (1 << 9)) {
            has_pitch_stick_eng3 = true;
            cursor.read(pitch_stick_eng3);
        }



        if (pv & (1 << 10)) {
            has_throttle_stick_eng4 = true;
            cursor.read(throttle_stick_eng4);
        }



        if (pv & (1 << 11)) {
            has_pitch_stick_eng4 = true;
            cursor.read(pitch_stick_eng4);
        }



        if (pv & (1 << 12)) {
            has_taxi_stick = true;
            cursor.read(taxi_stick);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_lateral_stick = false;



    bool has_longitudinal_stick = false;



    bool has_rotational_stick = false;



    bool has_throttle_stick_eng1 = false;



    bool has_pitch_stick_eng1 = false;



    bool has_throttle_stick_eng2 = false;



    bool has_pitch_stick_eng2 = false;



    bool has_throttle_stick_eng3 = false;



    bool has_pitch_stick_eng3 = false;



    bool has_throttle_stick_eng4 = false;



    bool has_pitch_stick_eng4 = false;



    bool has_taxi_stick = false;


};

} // namespace generated
} // namespace dli

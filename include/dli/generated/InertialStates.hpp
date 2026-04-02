#pragma once

#include "../BitCursor.hpp"
#include "../Bam.hpp"
#include "../Scaled.hpp"
#include <cstdint>

namespace dli {
namespace generated {

/**
 * @brief Auto-generated class for Message #4000: InertialStates
 */
class InertialStates {
public:
    // Fields

    uint64_t time_stamp; // [ms]

    double latitude;

    double longitude;

    double altitude; // [m]

    uint32_t altitude_type; // [enum]

    uint32_t u_speed; // [m/s]

    uint32_t v_speed; // [m/s]

    uint32_t w_speed; // [m/s]

    uint32_t u_accel; // [m/s^2]

    uint32_t v_accel; // [m/s^2]

    uint32_t w_accel; // [m/s^2]

    double roll; // [rad]

    double pitch; // [rad]

    double heading; // [rad]

    uint32_t roll_rate; // [rad/s]

    uint32_t pitch_rate; // [rad/s]

    uint32_t turn_rate; // [rad/s]

    double magnetic_variation; // [rad]


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint32_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (1 << 0);



        if (has_latitude) pv |= (1 << 1);



        if (has_longitude) pv |= (1 << 2);



        if (has_altitude) pv |= (1 << 3);



        if (has_altitude_type) pv |= (1 << 4);



        if (has_u_speed) pv |= (1 << 5);



        if (has_v_speed) pv |= (1 << 6);



        if (has_w_speed) pv |= (1 << 7);



        if (has_u_accel) pv |= (1 << 8);



        if (has_v_accel) pv |= (1 << 9);



        if (has_w_accel) pv |= (1 << 10);



        if (has_roll) pv |= (1 << 11);



        if (has_pitch) pv |= (1 << 12);



        if (has_heading) pv |= (1 << 13);



        if (has_roll_rate) pv |= (1 << 14);



        if (has_pitch_rate) pv |= (1 << 15);



        if (has_turn_rate) pv |= (1 << 16);



        if (has_magnetic_variation) pv |= (1 << 17);


        
        cursor.write_int(pv, 3);

        // Write Fields


        if (pv & (1 << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (1 << 1)) {

            cursor.write(bam::to_bam32(latitude));

        }



        if (pv & (1 << 2)) {

            cursor.write(bam::to_bam32(longitude));

        }



        if (pv & (1 << 3)) {

            cursor.write(scaled::to_scaled<int32_t>(altitude, 0.0, 0.01));

        }



        if (pv & (1 << 4)) {

            cursor.write(altitude_type);

        }



        if (pv & (1 << 5)) {

            cursor.write(u_speed);

        }



        if (pv & (1 << 6)) {

            cursor.write(v_speed);

        }



        if (pv & (1 << 7)) {

            cursor.write(w_speed);

        }



        if (pv & (1 << 8)) {

            cursor.write(u_accel);

        }



        if (pv & (1 << 9)) {

            cursor.write(v_accel);

        }



        if (pv & (1 << 10)) {

            cursor.write(w_accel);

        }



        if (pv & (1 << 11)) {

            cursor.write(bam::to_bam16(roll));

        }



        if (pv & (1 << 12)) {

            cursor.write(bam::to_bam16(pitch));

        }



        if (pv & (1 << 13)) {

            cursor.write(bam::to_bam16(heading));

        }



        if (pv & (1 << 14)) {

            cursor.write(roll_rate);

        }



        if (pv & (1 << 15)) {

            cursor.write(pitch_rate);

        }



        if (pv & (1 << 16)) {

            cursor.write(turn_rate);

        }



        if (pv & (1 << 17)) {

            cursor.write(bam::to_bam16(magnetic_variation));

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
            has_latitude = true;
            uint32_t tmp_latitude; cursor.read(tmp_latitude); latitude = bam::from_bam32(tmp_latitude);
        }



        if (pv & (1 << 2)) {
            has_longitude = true;
            uint32_t tmp_longitude; cursor.read(tmp_longitude); longitude = bam::from_bam32(tmp_longitude);
        }



        if (pv & (1 << 3)) {
            has_altitude = true;
            int32_t tmp_altitude; cursor.read(tmp_altitude); altitude = scaled::from_scaled<int32_t, double>(tmp_altitude, 0.0, 0.01);
        }



        if (pv & (1 << 4)) {
            has_altitude_type = true;
            cursor.read(altitude_type);
        }



        if (pv & (1 << 5)) {
            has_u_speed = true;
            cursor.read(u_speed);
        }



        if (pv & (1 << 6)) {
            has_v_speed = true;
            cursor.read(v_speed);
        }



        if (pv & (1 << 7)) {
            has_w_speed = true;
            cursor.read(w_speed);
        }



        if (pv & (1 << 8)) {
            has_u_accel = true;
            cursor.read(u_accel);
        }



        if (pv & (1 << 9)) {
            has_v_accel = true;
            cursor.read(v_accel);
        }



        if (pv & (1 << 10)) {
            has_w_accel = true;
            cursor.read(w_accel);
        }



        if (pv & (1 << 11)) {
            has_roll = true;
            uint16_t tmp_roll; cursor.read(tmp_roll); roll = bam::from_bam16(tmp_roll);
        }



        if (pv & (1 << 12)) {
            has_pitch = true;
            uint16_t tmp_pitch; cursor.read(tmp_pitch); pitch = bam::from_bam16(tmp_pitch);
        }



        if (pv & (1 << 13)) {
            has_heading = true;
            uint16_t tmp_heading; cursor.read(tmp_heading); heading = bam::from_bam16(tmp_heading);
        }



        if (pv & (1 << 14)) {
            has_roll_rate = true;
            cursor.read(roll_rate);
        }



        if (pv & (1 << 15)) {
            has_pitch_rate = true;
            cursor.read(pitch_rate);
        }



        if (pv & (1 << 16)) {
            has_turn_rate = true;
            cursor.read(turn_rate);
        }



        if (pv & (1 << 17)) {
            has_magnetic_variation = true;
            uint16_t tmp_magnetic_variation; cursor.read(tmp_magnetic_variation); magnetic_variation = bam::from_bam16(tmp_magnetic_variation);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_latitude = false;



    bool has_longitude = false;



    bool has_altitude = false;



    bool has_altitude_type = false;



    bool has_u_speed = false;



    bool has_v_speed = false;



    bool has_w_speed = false;



    bool has_u_accel = false;



    bool has_v_accel = false;



    bool has_w_accel = false;



    bool has_roll = false;



    bool has_pitch = false;



    bool has_heading = false;



    bool has_roll_rate = false;



    bool has_pitch_rate = false;



    bool has_turn_rate = false;



    bool has_magnetic_variation = false;


};

} // namespace generated
} // namespace dli

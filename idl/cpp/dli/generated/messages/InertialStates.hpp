#pragma once

#include <dli/core/BitCursor.hpp>
#include <dli/core/Bam.hpp>
#include <dli/core/Scaled.hpp>
#include <array>
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

    double latitude; // [rad]

    double longitude; // [rad]

    double altitude; // [m]

    uint8_t altitude_type; // [enum]

    double u_speed; // [m/s]

    double v_speed; // [m/s]

    double w_speed; // [m/s]

    double u_accel; // [m/s^2]

    double v_accel; // [m/s^2]

    double w_accel; // [m/s^2]

    double roll; // [rad]

    double pitch; // [rad]

    double heading; // [rad]

    double roll_rate; // [rad/s]

    double pitch_rate; // [rad/s]

    double turn_rate; // [rad/s]

    double magnetic_variation; // [rad]


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint64_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (uint64_t{1} << 0);



        if (has_latitude) pv |= (uint64_t{1} << 1);



        if (has_longitude) pv |= (uint64_t{1} << 2);



        if (has_altitude) pv |= (uint64_t{1} << 3);



        if (has_altitude_type) pv |= (uint64_t{1} << 4);



        if (has_u_speed) pv |= (uint64_t{1} << 5);



        if (has_v_speed) pv |= (uint64_t{1} << 6);



        if (has_w_speed) pv |= (uint64_t{1} << 7);



        if (has_u_accel) pv |= (uint64_t{1} << 8);



        if (has_v_accel) pv |= (uint64_t{1} << 9);



        if (has_w_accel) pv |= (uint64_t{1} << 10);



        if (has_roll) pv |= (uint64_t{1} << 11);



        if (has_pitch) pv |= (uint64_t{1} << 12);



        if (has_heading) pv |= (uint64_t{1} << 13);



        if (has_roll_rate) pv |= (uint64_t{1} << 14);



        if (has_pitch_rate) pv |= (uint64_t{1} << 15);



        if (has_turn_rate) pv |= (uint64_t{1} << 16);



        if (has_magnetic_variation) pv |= (uint64_t{1} << 17);


        
        cursor.write_int(pv, 3);

        // Write Fields


        if (pv & (uint64_t{1} << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (uint64_t{1} << 1)) {

            cursor.write(bam::to_bam32(latitude));

        }



        if (pv & (uint64_t{1} << 2)) {

            cursor.write(bam::to_bam32(longitude));

        }



        if (pv & (uint64_t{1} << 3)) {

            cursor.write_int(scaled::to_scaled<int32_t>(altitude, 0.0, 0.02), 3);

        }



        if (pv & (uint64_t{1} << 4)) {

            cursor.write(altitude_type);

        }



        if (pv & (uint64_t{1} << 5)) {

            cursor.write(scaled::to_scaled<int16_t>(u_speed, 0.0, 0.05));

        }



        if (pv & (uint64_t{1} << 6)) {

            cursor.write(scaled::to_scaled<int16_t>(v_speed, 0.0, 0.05));

        }



        if (pv & (uint64_t{1} << 7)) {

            cursor.write(scaled::to_scaled<int16_t>(w_speed, 0.0, 0.05));

        }



        if (pv & (uint64_t{1} << 8)) {

            cursor.write(scaled::to_scaled<int16_t>(u_accel, 0.0, 0.005));

        }



        if (pv & (uint64_t{1} << 9)) {

            cursor.write(scaled::to_scaled<int16_t>(v_accel, 0.0, 0.005));

        }



        if (pv & (uint64_t{1} << 10)) {

            cursor.write(scaled::to_scaled<int16_t>(w_accel, 0.0, 0.005));

        }



        if (pv & (uint64_t{1} << 11)) {

            cursor.write(bam::to_bam16(roll));

        }



        if (pv & (uint64_t{1} << 12)) {

            cursor.write(bam::to_bam16(pitch));

        }



        if (pv & (uint64_t{1} << 13)) {

            cursor.write(bam::to_bam16(heading));

        }



        if (pv & (uint64_t{1} << 14)) {

            cursor.write(scaled::to_scaled<int16_t>(roll_rate, 0.0, 0.005));

        }



        if (pv & (uint64_t{1} << 15)) {

            cursor.write(scaled::to_scaled<int16_t>(pitch_rate, 0.0, 0.005));

        }



        if (pv & (uint64_t{1} << 16)) {

            cursor.write(scaled::to_scaled<int16_t>(turn_rate, 0.0, 0.005));

        }



        if (pv & (uint64_t{1} << 17)) {

            cursor.write(bam::to_bam16(magnetic_variation));

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
            has_latitude = true;
            uint32_t tmp_latitude; cursor.read(tmp_latitude); latitude = bam::from_bam32(tmp_latitude);
        }



        if (pv & (uint64_t{1} << 2)) {
            has_longitude = true;
            uint32_t tmp_longitude; cursor.read(tmp_longitude); longitude = bam::from_bam32(tmp_longitude);
        }



        if (pv & (uint64_t{1} << 3)) {
            has_altitude = true;
            int32_t tmp_altitude; cursor.read_int(tmp_altitude, 3); altitude = scaled::from_scaled<int32_t, double>(tmp_altitude, 0.0, 0.02);
        }



        if (pv & (uint64_t{1} << 4)) {
            has_altitude_type = true;
            cursor.read(altitude_type);
        }



        if (pv & (uint64_t{1} << 5)) {
            has_u_speed = true;
            int16_t tmp_u_speed; cursor.read(tmp_u_speed); u_speed = scaled::from_scaled<int16_t, double>(tmp_u_speed, 0.0, 0.05);
        }



        if (pv & (uint64_t{1} << 6)) {
            has_v_speed = true;
            int16_t tmp_v_speed; cursor.read(tmp_v_speed); v_speed = scaled::from_scaled<int16_t, double>(tmp_v_speed, 0.0, 0.05);
        }



        if (pv & (uint64_t{1} << 7)) {
            has_w_speed = true;
            int16_t tmp_w_speed; cursor.read(tmp_w_speed); w_speed = scaled::from_scaled<int16_t, double>(tmp_w_speed, 0.0, 0.05);
        }



        if (pv & (uint64_t{1} << 8)) {
            has_u_accel = true;
            int16_t tmp_u_accel; cursor.read(tmp_u_accel); u_accel = scaled::from_scaled<int16_t, double>(tmp_u_accel, 0.0, 0.005);
        }



        if (pv & (uint64_t{1} << 9)) {
            has_v_accel = true;
            int16_t tmp_v_accel; cursor.read(tmp_v_accel); v_accel = scaled::from_scaled<int16_t, double>(tmp_v_accel, 0.0, 0.005);
        }



        if (pv & (uint64_t{1} << 10)) {
            has_w_accel = true;
            int16_t tmp_w_accel; cursor.read(tmp_w_accel); w_accel = scaled::from_scaled<int16_t, double>(tmp_w_accel, 0.0, 0.005);
        }



        if (pv & (uint64_t{1} << 11)) {
            has_roll = true;
            uint16_t tmp_roll; cursor.read(tmp_roll); roll = bam::from_bam16(tmp_roll);
        }



        if (pv & (uint64_t{1} << 12)) {
            has_pitch = true;
            uint16_t tmp_pitch; cursor.read(tmp_pitch); pitch = bam::from_bam16(tmp_pitch);
        }



        if (pv & (uint64_t{1} << 13)) {
            has_heading = true;
            uint16_t tmp_heading; cursor.read(tmp_heading); heading = bam::from_bam16(tmp_heading);
        }



        if (pv & (uint64_t{1} << 14)) {
            has_roll_rate = true;
            int16_t tmp_roll_rate; cursor.read(tmp_roll_rate); roll_rate = scaled::from_scaled<int16_t, double>(tmp_roll_rate, 0.0, 0.005);
        }



        if (pv & (uint64_t{1} << 15)) {
            has_pitch_rate = true;
            int16_t tmp_pitch_rate; cursor.read(tmp_pitch_rate); pitch_rate = scaled::from_scaled<int16_t, double>(tmp_pitch_rate, 0.0, 0.005);
        }



        if (pv & (uint64_t{1} << 16)) {
            has_turn_rate = true;
            int16_t tmp_turn_rate; cursor.read(tmp_turn_rate); turn_rate = scaled::from_scaled<int16_t, double>(tmp_turn_rate, 0.0, 0.005);
        }



        if (pv & (uint64_t{1} << 17)) {
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

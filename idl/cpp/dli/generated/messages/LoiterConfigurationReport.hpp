#pragma once

#include <dli/core/BitCursor.hpp>
#include <dli/core/Bam.hpp>
#include <dli/core/Scaled.hpp>
#include <array>
#include <cstdint>

namespace dli {
namespace generated {

/**
 * @brief Auto-generated class for Message #3004: LoiterConfigurationReport
 */
class LoiterConfigurationReport {
public:
    // Fields

    uint64_t time_stamp; // [ms]

    uint8_t loiter_type; // [enum]

    double loiter_radius; // [m]

    double loiter_length; // [m]

    uint8_t loiter_length_units; // [enum]

    double loiter_bearing; // [rad]

    uint8_t loiter_direction; // [enum]

    double loiter_altitude; // [m]

    uint8_t altitude_type; // [enum]

    double loiter_speed; // [m/s]

    uint8_t speed_type; // [enum]

    uint8_t flying_behaviour; // [enum]

    uint16_t loiter_duration;

    uint8_t loiter_duration_units; // [enum]


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint64_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (uint64_t{1} << 0);



        if (has_loiter_type) pv |= (uint64_t{1} << 1);



        if (has_loiter_radius) pv |= (uint64_t{1} << 2);



        if (has_loiter_length) pv |= (uint64_t{1} << 3);



        if (has_loiter_length_units) pv |= (uint64_t{1} << 4);



        if (has_loiter_bearing) pv |= (uint64_t{1} << 5);



        if (has_loiter_direction) pv |= (uint64_t{1} << 6);



        if (has_loiter_altitude) pv |= (uint64_t{1} << 7);



        if (has_altitude_type) pv |= (uint64_t{1} << 8);



        if (has_loiter_speed) pv |= (uint64_t{1} << 9);



        if (has_speed_type) pv |= (uint64_t{1} << 10);



        if (has_flying_behaviour) pv |= (uint64_t{1} << 11);



        if (has_loiter_duration) pv |= (uint64_t{1} << 12);



        if (has_loiter_duration_units) pv |= (uint64_t{1} << 13);


        
        cursor.write_int(pv, 2);

        // Write Fields


        if (pv & (uint64_t{1} << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (uint64_t{1} << 1)) {

            cursor.write(loiter_type);

        }



        if (pv & (uint64_t{1} << 2)) {

            cursor.write(scaled::to_scaled<uint16_t>(loiter_radius, 0.0, 1.5));

        }



        if (pv & (uint64_t{1} << 3)) {

            cursor.write(scaled::to_scaled<uint16_t>(loiter_length, 0.0, 1.5));

        }



        if (pv & (uint64_t{1} << 4)) {

            cursor.write(loiter_length_units);

        }



        if (pv & (uint64_t{1} << 5)) {

            cursor.write(bam::to_bam16(loiter_bearing));

        }



        if (pv & (uint64_t{1} << 6)) {

            cursor.write(loiter_direction);

        }



        if (pv & (uint64_t{1} << 7)) {

            cursor.write_int(scaled::to_scaled<int32_t>(loiter_altitude, 0.0, 0.02), 3);

        }



        if (pv & (uint64_t{1} << 8)) {

            cursor.write(altitude_type);

        }



        if (pv & (uint64_t{1} << 9)) {

            cursor.write(scaled::to_scaled<uint16_t>(loiter_speed, 0.0, 0.5));

        }



        if (pv & (uint64_t{1} << 10)) {

            cursor.write(speed_type);

        }



        if (pv & (uint64_t{1} << 11)) {

            cursor.write(flying_behaviour);

        }



        if (pv & (uint64_t{1} << 12)) {

            cursor.write(loiter_duration);

        }



        if (pv & (uint64_t{1} << 13)) {

            cursor.write(loiter_duration_units);

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
            has_loiter_type = true;
            cursor.read(loiter_type);
        }



        if (pv & (uint64_t{1} << 2)) {
            has_loiter_radius = true;
            uint16_t tmp_loiter_radius; cursor.read(tmp_loiter_radius); loiter_radius = scaled::from_scaled<uint16_t, double>(tmp_loiter_radius, 0.0, 1.5);
        }



        if (pv & (uint64_t{1} << 3)) {
            has_loiter_length = true;
            uint16_t tmp_loiter_length; cursor.read(tmp_loiter_length); loiter_length = scaled::from_scaled<uint16_t, double>(tmp_loiter_length, 0.0, 1.5);
        }



        if (pv & (uint64_t{1} << 4)) {
            has_loiter_length_units = true;
            cursor.read(loiter_length_units);
        }



        if (pv & (uint64_t{1} << 5)) {
            has_loiter_bearing = true;
            uint16_t tmp_loiter_bearing; cursor.read(tmp_loiter_bearing); loiter_bearing = bam::from_bam16(tmp_loiter_bearing);
        }



        if (pv & (uint64_t{1} << 6)) {
            has_loiter_direction = true;
            cursor.read(loiter_direction);
        }



        if (pv & (uint64_t{1} << 7)) {
            has_loiter_altitude = true;
            int32_t tmp_loiter_altitude; cursor.read_int(tmp_loiter_altitude, 3); loiter_altitude = scaled::from_scaled<int32_t, double>(tmp_loiter_altitude, 0.0, 0.02);
        }



        if (pv & (uint64_t{1} << 8)) {
            has_altitude_type = true;
            cursor.read(altitude_type);
        }



        if (pv & (uint64_t{1} << 9)) {
            has_loiter_speed = true;
            uint16_t tmp_loiter_speed; cursor.read(tmp_loiter_speed); loiter_speed = scaled::from_scaled<uint16_t, double>(tmp_loiter_speed, 0.0, 0.5);
        }



        if (pv & (uint64_t{1} << 10)) {
            has_speed_type = true;
            cursor.read(speed_type);
        }



        if (pv & (uint64_t{1} << 11)) {
            has_flying_behaviour = true;
            cursor.read(flying_behaviour);
        }



        if (pv & (uint64_t{1} << 12)) {
            has_loiter_duration = true;
            cursor.read(loiter_duration);
        }



        if (pv & (uint64_t{1} << 13)) {
            has_loiter_duration_units = true;
            cursor.read(loiter_duration_units);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_loiter_type = false;



    bool has_loiter_radius = false;



    bool has_loiter_length = false;



    bool has_loiter_length_units = false;



    bool has_loiter_bearing = false;



    bool has_loiter_direction = false;



    bool has_loiter_altitude = false;



    bool has_altitude_type = false;



    bool has_loiter_speed = false;



    bool has_speed_type = false;



    bool has_flying_behaviour = false;



    bool has_loiter_duration = false;



    bool has_loiter_duration_units = false;


};

} // namespace generated
} // namespace dli

#pragma once

#include <dli/core/BitCursor.hpp>
#include <dli/core/Bam.hpp>
#include <dli/core/Scaled.hpp>
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

    uint32_t loiter_type; // [enum]

    uint32_t loiter_radius; // [m]

    uint32_t loiter_length; // [m]

    uint32_t loiter_length_units; // [enum]

    double loiter_bearing; // [rad]

    uint32_t loiter_direction; // [enum]

    uint32_t loiter_altitude; // [m]

    uint32_t altitude_type; // [enum]

    uint32_t loiter_speed; // [m/s]


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint32_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (1 << 0);



        if (has_loiter_type) pv |= (1 << 1);



        if (has_loiter_radius) pv |= (1 << 2);



        if (has_loiter_length) pv |= (1 << 3);



        if (has_loiter_length_units) pv |= (1 << 4);



        if (has_loiter_bearing) pv |= (1 << 5);



        if (has_loiter_direction) pv |= (1 << 6);



        if (has_loiter_altitude) pv |= (1 << 7);



        if (has_altitude_type) pv |= (1 << 8);



        if (has_loiter_speed) pv |= (1 << 9);


        
        cursor.write_int(pv, 2);

        // Write Fields


        if (pv & (1 << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (1 << 1)) {

            cursor.write(loiter_type);

        }



        if (pv & (1 << 2)) {

            cursor.write(loiter_radius);

        }



        if (pv & (1 << 3)) {

            cursor.write(loiter_length);

        }



        if (pv & (1 << 4)) {

            cursor.write(loiter_length_units);

        }



        if (pv & (1 << 5)) {

            cursor.write(bam::to_bam16(loiter_bearing));

        }



        if (pv & (1 << 6)) {

            cursor.write(loiter_direction);

        }



        if (pv & (1 << 7)) {

            cursor.write(loiter_altitude);

        }



        if (pv & (1 << 8)) {

            cursor.write(altitude_type);

        }



        if (pv & (1 << 9)) {

            cursor.write(loiter_speed);

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
            has_loiter_type = true;
            cursor.read(loiter_type);
        }



        if (pv & (1 << 2)) {
            has_loiter_radius = true;
            cursor.read(loiter_radius);
        }



        if (pv & (1 << 3)) {
            has_loiter_length = true;
            cursor.read(loiter_length);
        }



        if (pv & (1 << 4)) {
            has_loiter_length_units = true;
            cursor.read(loiter_length_units);
        }



        if (pv & (1 << 5)) {
            has_loiter_bearing = true;
            uint16_t tmp_loiter_bearing; cursor.read(tmp_loiter_bearing); loiter_bearing = bam::from_bam16(tmp_loiter_bearing);
        }



        if (pv & (1 << 6)) {
            has_loiter_direction = true;
            cursor.read(loiter_direction);
        }



        if (pv & (1 << 7)) {
            has_loiter_altitude = true;
            cursor.read(loiter_altitude);
        }



        if (pv & (1 << 8)) {
            has_altitude_type = true;
            cursor.read(altitude_type);
        }



        if (pv & (1 << 9)) {
            has_loiter_speed = true;
            cursor.read(loiter_speed);
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


};

} // namespace generated
} // namespace dli

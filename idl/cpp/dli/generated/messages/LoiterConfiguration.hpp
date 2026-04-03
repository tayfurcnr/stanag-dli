#pragma once

#include <dli/core/BitCursor.hpp>
#include <dli/core/Bam.hpp>
#include <dli/core/Scaled.hpp>
#include <array>
#include <cstdint>

namespace dli {
namespace generated {

/**
 * @brief Auto-generated class for Message #2017: LoiterConfiguration
 */
class LoiterConfiguration {
public:
    // Fields

    uint64_t time_stamp; // [ms]

    uint8_t loiter_type; // [enum]

    double loiter_radius; // [m]

    double loiter_length; // [m]

    uint8_t loiter_length_units; // [enum]

    double loiter_bearing; // [rad]

    uint8_t loiter_direction; // [enum]

    uint8_t flying_behaviour; // [enum]

    uint16_t loiter_duration;

    uint8_t loiter_duration_units; // [enum]

    uint32_t activity_id;


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



        if (has_flying_behaviour) pv |= (uint64_t{1} << 7);



        if (has_loiter_duration) pv |= (uint64_t{1} << 8);



        if (has_loiter_duration_units) pv |= (uint64_t{1} << 9);



        if (has_activity_id) pv |= (uint64_t{1} << 10);


        
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

            cursor.write(flying_behaviour);

        }



        if (pv & (uint64_t{1} << 8)) {

            cursor.write(loiter_duration);

        }



        if (pv & (uint64_t{1} << 9)) {

            cursor.write(loiter_duration_units);

        }



        if (pv & (uint64_t{1} << 10)) {

            cursor.write_int(activity_id, 3);

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
            has_flying_behaviour = true;
            cursor.read(flying_behaviour);
        }



        if (pv & (uint64_t{1} << 8)) {
            has_loiter_duration = true;
            cursor.read(loiter_duration);
        }



        if (pv & (uint64_t{1} << 9)) {
            has_loiter_duration_units = true;
            cursor.read(loiter_duration_units);
        }



        if (pv & (uint64_t{1} << 10)) {
            has_activity_id = true;
            cursor.read_int(activity_id, 3);
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



    bool has_flying_behaviour = false;



    bool has_loiter_duration = false;



    bool has_loiter_duration_units = false;



    bool has_activity_id = false;


};

} // namespace generated
} // namespace dli

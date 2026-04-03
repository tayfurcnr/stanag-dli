#pragma once

#include <dli/core/BitCursor.hpp>
#include <dli/core/Bam.hpp>
#include <dli/core/Scaled.hpp>
#include <array>
#include <cstdint>

namespace dli {
namespace generated {

/**
 * @brief Auto-generated class for Message #2007: UnmannedAircraftLights
 */
class UnmannedAircraftLights {
public:
    // Fields

    uint64_t time_stamp; // [ms]

    uint16_t set_lights; // [Bitmapped]

    uint32_t activity_id;


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint64_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (uint64_t{1} << 0);



        if (has_set_lights) pv |= (uint64_t{1} << 1);



        if (has_activity_id) pv |= (uint64_t{1} << 2);


        
        cursor.write_int(pv, 1);

        // Write Fields


        if (pv & (uint64_t{1} << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (uint64_t{1} << 1)) {

            cursor.write(set_lights);

        }



        if (pv & (uint64_t{1} << 2)) {

            cursor.write_int(activity_id, 3);

        }


    }

    void deserialize(BitCursor& cursor) {
        uint64_t pv = 0;
        cursor.read_int(pv, 1);

        // Read Fields


        if (pv & (uint64_t{1} << 0)) {
            has_time_stamp = true;
            cursor.read_int(time_stamp, 5);
        }



        if (pv & (uint64_t{1} << 1)) {
            has_set_lights = true;
            cursor.read(set_lights);
        }



        if (pv & (uint64_t{1} << 2)) {
            has_activity_id = true;
            cursor.read_int(activity_id, 3);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_set_lights = false;



    bool has_activity_id = false;


};

} // namespace generated
} // namespace dli

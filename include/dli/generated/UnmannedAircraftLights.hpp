#pragma once

#include "../BitCursor.hpp"
#include "../Bam.hpp"
#include "../Scaled.hpp"
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

    uint32_t ua_lights; // [Bitmapped]


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint32_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (1 << 0);



        if (has_ua_lights) pv |= (1 << 1);


        
        cursor.write_int(pv, 1);

        // Write Fields


        if (pv & (1 << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (1 << 1)) {

            cursor.write(ua_lights);

        }


    }

    void deserialize(BitCursor& cursor) {
        uint32_t pv = 0;
        cursor.read_int(pv, 1);

        // Read Fields


        if (pv & (1 << 0)) {
            has_time_stamp = true;
            cursor.read_int(time_stamp, 5);
        }



        if (pv & (1 << 1)) {
            has_ua_lights = true;
            cursor.read(ua_lights);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_ua_lights = false;


};

} // namespace generated
} // namespace dli

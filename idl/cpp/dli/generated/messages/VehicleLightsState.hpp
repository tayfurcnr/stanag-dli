#pragma once

#include <dli/core/BitCursor.hpp>
#include <dli/core/Bam.hpp>
#include <dli/core/Scaled.hpp>
#include <array>
#include <cstdint>

namespace dli {
namespace generated {

/**
 * @brief Auto-generated class for Message #3006: VehicleLightsState
 */
class VehicleLightsState {
public:
    // Fields

    uint64_t time_stamp; // [ms]

    uint16_t navigation_lights_state; // [Bitmapped]


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint64_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (uint64_t{1} << 0);



        if (has_navigation_lights_state) pv |= (uint64_t{1} << 1);


        
        cursor.write_int(pv, 1);

        // Write Fields


        if (pv & (uint64_t{1} << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (uint64_t{1} << 1)) {

            cursor.write(navigation_lights_state);

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
            has_navigation_lights_state = true;
            cursor.read(navigation_lights_state);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_navigation_lights_state = false;


};

} // namespace generated
} // namespace dli

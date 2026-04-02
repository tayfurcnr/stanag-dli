#pragma once

#include "../BitCursor.hpp"
#include "../Bam.hpp"
#include "../Scaled.hpp"
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

    uint32_t lights_state; // [Bitmapped]


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint32_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (1 << 0);



        if (has_lights_state) pv |= (1 << 1);


        
        cursor.write_int(pv, 1);

        // Write Fields


        if (pv & (1 << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (1 << 1)) {

            cursor.write(lights_state);

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
            has_lights_state = true;
            cursor.read(lights_state);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_lights_state = false;


};

} // namespace generated
} // namespace dli

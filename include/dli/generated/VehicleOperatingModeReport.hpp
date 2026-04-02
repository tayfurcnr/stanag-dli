#pragma once

#include "../BitCursor.hpp"
#include "../Bam.hpp"
#include "../Scaled.hpp"
#include <cstdint>

namespace dli {
namespace generated {

/**
 * @brief Auto-generated class for Message #3001: VehicleOperatingModeReport
 */
class VehicleOperatingModeReport {
public:
    // Fields

    uint64_t time_stamp; // [ms]

    uint32_t flight_path_control_mode; // [enum]


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint32_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (1 << 0);



        if (has_flight_path_control_mode) pv |= (1 << 1);


        
        cursor.write_int(pv, 1);

        // Write Fields


        if (pv & (1 << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (1 << 1)) {

            cursor.write(flight_path_control_mode);

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
            has_flight_path_control_mode = true;
            cursor.read(flight_path_control_mode);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_flight_path_control_mode = false;


};

} // namespace generated
} // namespace dli

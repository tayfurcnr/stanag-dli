#pragma once

#include <dli/core/BitCursor.hpp>
#include <dli/core/Bam.hpp>
#include <dli/core/Scaled.hpp>
#include <array>
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

    uint8_t select_flight_path_control_mode; // [enum]


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint64_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (uint64_t{1} << 0);



        if (has_select_flight_path_control_mode) pv |= (uint64_t{1} << 1);


        
        cursor.write_int(pv, 1);

        // Write Fields


        if (pv & (uint64_t{1} << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (uint64_t{1} << 1)) {

            cursor.write(select_flight_path_control_mode);

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
            has_select_flight_path_control_mode = true;
            cursor.read(select_flight_path_control_mode);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_select_flight_path_control_mode = false;


};

} // namespace generated
} // namespace dli

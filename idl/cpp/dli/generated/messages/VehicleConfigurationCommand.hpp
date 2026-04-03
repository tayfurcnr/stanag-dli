#pragma once

#include <dli/core/BitCursor.hpp>
#include <dli/core/Bam.hpp>
#include <dli/core/Scaled.hpp>
#include <array>
#include <cstdint>

namespace dli {
namespace generated {

/**
 * @brief Auto-generated class for Message #2000: VehicleConfigurationCommand
 */
class VehicleConfigurationCommand {
public:
    // Fields

    uint64_t time_stamp; // [ms]

    uint8_t energy_storage_unit;

    double initial_propulsion_energy; // [%]


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint64_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (uint64_t{1} << 0);



        if (has_energy_storage_unit) pv |= (uint64_t{1} << 1);



        if (has_initial_propulsion_energy) pv |= (uint64_t{1} << 2);


        
        cursor.write_int(pv, 1);

        // Write Fields


        if (pv & (uint64_t{1} << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (uint64_t{1} << 1)) {

            cursor.write(energy_storage_unit);

        }



        if (pv & (uint64_t{1} << 2)) {

            cursor.write(scaled::to_scaled<uint16_t>(initial_propulsion_energy, 0.0, 0.002));

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
            has_energy_storage_unit = true;
            cursor.read(energy_storage_unit);
        }



        if (pv & (uint64_t{1} << 2)) {
            has_initial_propulsion_energy = true;
            uint16_t tmp_initial_propulsion_energy; cursor.read(tmp_initial_propulsion_energy); initial_propulsion_energy = scaled::from_scaled<uint16_t, double>(tmp_initial_propulsion_energy, 0.0, 0.002);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_energy_storage_unit = false;



    bool has_initial_propulsion_energy = false;


};

} // namespace generated
} // namespace dli

#pragma once

#include <dli/core/BitCursor.hpp>
#include <dli/core/Bam.hpp>
#include <dli/core/Scaled.hpp>
#include <array>
#include <cstdint>

namespace dli {
namespace generated {

/**
 * @brief Auto-generated class for Message #3: VehicleID
 */
class VehicleID {
public:
    // Fields

    uint64_t time_stamp; // [ms]

    uint32_t vsm_id;

    uint32_t vehicle_id_update;

    uint16_t vehicle_type; // [enum]

    uint16_t vehicle_subtype;

    uint8_t owning_id; // [enum]

    std::array<uint8_t, 16> tail_number;

    std::array<uint8_t, 20> mission_id;

    std::array<uint8_t, 32> atc_call_sign;

    uint16_t configuration_checksum;


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint64_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (uint64_t{1} << 0);



        if (has_vsm_id) pv |= (uint64_t{1} << 1);



        if (has_vehicle_id_update) pv |= (uint64_t{1} << 2);



        if (has_vehicle_type) pv |= (uint64_t{1} << 3);



        if (has_vehicle_subtype) pv |= (uint64_t{1} << 4);



        if (has_owning_id) pv |= (uint64_t{1} << 5);



        if (has_tail_number) pv |= (uint64_t{1} << 6);



        if (has_mission_id) pv |= (uint64_t{1} << 7);



        if (has_atc_call_sign) pv |= (uint64_t{1} << 8);



        if (has_configuration_checksum) pv |= (uint64_t{1} << 9);


        
        cursor.write_int(pv, 2);

        // Write Fields


        if (pv & (uint64_t{1} << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (uint64_t{1} << 1)) {

            cursor.write(vsm_id);

        }



        if (pv & (uint64_t{1} << 2)) {

            cursor.write(vehicle_id_update);

        }



        if (pv & (uint64_t{1} << 3)) {

            cursor.write(vehicle_type);

        }



        if (pv & (uint64_t{1} << 4)) {

            cursor.write(vehicle_subtype);

        }



        if (pv & (uint64_t{1} << 5)) {

            cursor.write(owning_id);

        }



        if (pv & (uint64_t{1} << 6)) {

            for (const auto& byte : tail_number) { cursor.write(byte); }

        }



        if (pv & (uint64_t{1} << 7)) {

            for (const auto& byte : mission_id) { cursor.write(byte); }

        }



        if (pv & (uint64_t{1} << 8)) {

            for (const auto& byte : atc_call_sign) { cursor.write(byte); }

        }



        if (pv & (uint64_t{1} << 9)) {

            cursor.write(configuration_checksum);

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
            has_vsm_id = true;
            cursor.read(vsm_id);
        }



        if (pv & (uint64_t{1} << 2)) {
            has_vehicle_id_update = true;
            cursor.read(vehicle_id_update);
        }



        if (pv & (uint64_t{1} << 3)) {
            has_vehicle_type = true;
            cursor.read(vehicle_type);
        }



        if (pv & (uint64_t{1} << 4)) {
            has_vehicle_subtype = true;
            cursor.read(vehicle_subtype);
        }



        if (pv & (uint64_t{1} << 5)) {
            has_owning_id = true;
            cursor.read(owning_id);
        }



        if (pv & (uint64_t{1} << 6)) {
            has_tail_number = true;
            for (auto& byte : tail_number) { cursor.read(byte); }
        }



        if (pv & (uint64_t{1} << 7)) {
            has_mission_id = true;
            for (auto& byte : mission_id) { cursor.read(byte); }
        }



        if (pv & (uint64_t{1} << 8)) {
            has_atc_call_sign = true;
            for (auto& byte : atc_call_sign) { cursor.read(byte); }
        }



        if (pv & (uint64_t{1} << 9)) {
            has_configuration_checksum = true;
            cursor.read(configuration_checksum);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_vsm_id = false;



    bool has_vehicle_id_update = false;



    bool has_vehicle_type = false;



    bool has_vehicle_subtype = false;



    bool has_owning_id = false;



    bool has_tail_number = false;



    bool has_mission_id = false;



    bool has_atc_call_sign = false;



    bool has_configuration_checksum = false;


};

} // namespace generated
} // namespace dli

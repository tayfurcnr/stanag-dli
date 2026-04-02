#pragma once

#include "../BitCursor.hpp"
#include "../Bam.hpp"
#include "../Scaled.hpp"
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

    uint32_t vehicle_type; // [enum]

    uint32_t vehicle_subtype;

    uint32_t owning_id; // [enum]

    uint32_t tail_number;

    uint32_t mission_id;

    uint32_t atc_call_sign;


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint32_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (1 << 0);



        if (has_vsm_id) pv |= (1 << 1);



        if (has_vehicle_id_update) pv |= (1 << 2);



        if (has_vehicle_type) pv |= (1 << 3);



        if (has_vehicle_subtype) pv |= (1 << 4);



        if (has_owning_id) pv |= (1 << 5);



        if (has_tail_number) pv |= (1 << 6);



        if (has_mission_id) pv |= (1 << 7);



        if (has_atc_call_sign) pv |= (1 << 8);


        
        cursor.write_int(pv, 2);

        // Write Fields


        if (pv & (1 << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (1 << 1)) {

            cursor.write(vsm_id);

        }



        if (pv & (1 << 2)) {

            cursor.write(vehicle_id_update);

        }



        if (pv & (1 << 3)) {

            cursor.write(vehicle_type);

        }



        if (pv & (1 << 4)) {

            cursor.write(vehicle_subtype);

        }



        if (pv & (1 << 5)) {

            cursor.write(owning_id);

        }



        if (pv & (1 << 6)) {

            cursor.write(tail_number);

        }



        if (pv & (1 << 7)) {

            cursor.write(mission_id);

        }



        if (pv & (1 << 8)) {

            cursor.write(atc_call_sign);

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
            has_vsm_id = true;
            cursor.read(vsm_id);
        }



        if (pv & (1 << 2)) {
            has_vehicle_id_update = true;
            cursor.read(vehicle_id_update);
        }



        if (pv & (1 << 3)) {
            has_vehicle_type = true;
            cursor.read(vehicle_type);
        }



        if (pv & (1 << 4)) {
            has_vehicle_subtype = true;
            cursor.read(vehicle_subtype);
        }



        if (pv & (1 << 5)) {
            has_owning_id = true;
            cursor.read(owning_id);
        }



        if (pv & (1 << 6)) {
            has_tail_number = true;
            cursor.read(tail_number);
        }



        if (pv & (1 << 7)) {
            has_mission_id = true;
            cursor.read(mission_id);
        }



        if (pv & (1 << 8)) {
            has_atc_call_sign = true;
            cursor.read(atc_call_sign);
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


};

} // namespace generated
} // namespace dli

#pragma once

#include <dli/core/BitCursor.hpp>
#include <dli/core/Bam.hpp>
#include <dli/core/Scaled.hpp>
#include <cstdint>

namespace dli {
namespace generated {

/**
 * @brief Auto-generated class for Message #4: PositiveHandoverAuthorisationRequest
 */
class PositiveHandoverAuthorisationRequest {
public:
    // Fields

    uint64_t time_stamp; // [ms]

    uint32_t vsm_id;

    uint32_t data_link_id;

    uint32_t vehicle_type; // [enum]

    uint32_t vehicle_subtype;

    uint32_t requested_handover_loi; // [Bitmapped]

    uint32_t flight_mode_offset;

    uint32_t requested_flight_mode; // [Bitmapped]

    uint32_t controlled_stn_1_16; // [Bitmapped]

    uint32_t component_number; // [Bitmapped]

    uint32_t sub_component_number; // [Bitmapped]

    uint32_t requesting_cucs_type; // [enum]

    uint32_t requesting_cucs_subtype;

    uint32_t requesting_cucs_id;

    uint32_t presence_vector_support; // [enum]

    uint32_t controlled_stn_17_32; // [Bitmapped]


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint32_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (1 << 0);



        if (has_vsm_id) pv |= (1 << 1);



        if (has_data_link_id) pv |= (1 << 2);



        if (has_vehicle_type) pv |= (1 << 3);



        if (has_vehicle_subtype) pv |= (1 << 4);



        if (has_requested_handover_loi) pv |= (1 << 5);



        if (has_flight_mode_offset) pv |= (1 << 6);



        if (has_requested_flight_mode) pv |= (1 << 7);



        if (has_controlled_stn_1_16) pv |= (1 << 8);



        if (has_component_number) pv |= (1 << 9);



        if (has_sub_component_number) pv |= (1 << 10);



        if (has_requesting_cucs_type) pv |= (1 << 11);



        if (has_requesting_cucs_subtype) pv |= (1 << 12);



        if (has_requesting_cucs_id) pv |= (1 << 13);



        if (has_presence_vector_support) pv |= (1 << 14);



        if (has_controlled_stn_17_32) pv |= (1 << 15);


        
        cursor.write_int(pv, 2);

        // Write Fields


        if (pv & (1 << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (1 << 1)) {

            cursor.write(vsm_id);

        }



        if (pv & (1 << 2)) {

            cursor.write(data_link_id);

        }



        if (pv & (1 << 3)) {

            cursor.write(vehicle_type);

        }



        if (pv & (1 << 4)) {

            cursor.write(vehicle_subtype);

        }



        if (pv & (1 << 5)) {

            cursor.write(requested_handover_loi);

        }



        if (pv & (1 << 6)) {

            cursor.write(flight_mode_offset);

        }



        if (pv & (1 << 7)) {

            cursor.write(requested_flight_mode);

        }



        if (pv & (1 << 8)) {

            cursor.write(controlled_stn_1_16);

        }



        if (pv & (1 << 9)) {

            cursor.write(component_number);

        }



        if (pv & (1 << 10)) {

            cursor.write(sub_component_number);

        }



        if (pv & (1 << 11)) {

            cursor.write(requesting_cucs_type);

        }



        if (pv & (1 << 12)) {

            cursor.write(requesting_cucs_subtype);

        }



        if (pv & (1 << 13)) {

            cursor.write(requesting_cucs_id);

        }



        if (pv & (1 << 14)) {

            cursor.write(presence_vector_support);

        }



        if (pv & (1 << 15)) {

            cursor.write(controlled_stn_17_32);

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
            has_data_link_id = true;
            cursor.read(data_link_id);
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
            has_requested_handover_loi = true;
            cursor.read(requested_handover_loi);
        }



        if (pv & (1 << 6)) {
            has_flight_mode_offset = true;
            cursor.read(flight_mode_offset);
        }



        if (pv & (1 << 7)) {
            has_requested_flight_mode = true;
            cursor.read(requested_flight_mode);
        }



        if (pv & (1 << 8)) {
            has_controlled_stn_1_16 = true;
            cursor.read(controlled_stn_1_16);
        }



        if (pv & (1 << 9)) {
            has_component_number = true;
            cursor.read(component_number);
        }



        if (pv & (1 << 10)) {
            has_sub_component_number = true;
            cursor.read(sub_component_number);
        }



        if (pv & (1 << 11)) {
            has_requesting_cucs_type = true;
            cursor.read(requesting_cucs_type);
        }



        if (pv & (1 << 12)) {
            has_requesting_cucs_subtype = true;
            cursor.read(requesting_cucs_subtype);
        }



        if (pv & (1 << 13)) {
            has_requesting_cucs_id = true;
            cursor.read(requesting_cucs_id);
        }



        if (pv & (1 << 14)) {
            has_presence_vector_support = true;
            cursor.read(presence_vector_support);
        }



        if (pv & (1 << 15)) {
            has_controlled_stn_17_32 = true;
            cursor.read(controlled_stn_17_32);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_vsm_id = false;



    bool has_data_link_id = false;



    bool has_vehicle_type = false;



    bool has_vehicle_subtype = false;



    bool has_requested_handover_loi = false;



    bool has_flight_mode_offset = false;



    bool has_requested_flight_mode = false;



    bool has_controlled_stn_1_16 = false;



    bool has_component_number = false;



    bool has_sub_component_number = false;



    bool has_requesting_cucs_type = false;



    bool has_requesting_cucs_subtype = false;



    bool has_requesting_cucs_id = false;



    bool has_presence_vector_support = false;



    bool has_controlled_stn_17_32 = false;


};

} // namespace generated
} // namespace dli

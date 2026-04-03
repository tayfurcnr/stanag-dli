#pragma once

#include <dli/core/BitCursor.hpp>
#include <dli/core/Bam.hpp>
#include <dli/core/Scaled.hpp>
#include <array>
#include <cstdint>

namespace dli {
namespace generated {

/**
 * @brief Auto-generated class for Message #5: PositiveHandoverAuthorisationGranted
 */
class PositiveHandoverAuthorisationGranted {
public:
    // Fields

    uint64_t time_stamp; // [ms]

    uint32_t vsm_id;

    uint32_t data_link_id;

    uint8_t loi_authorized; // [Bitmapped]

    uint8_t flight_mode_offset;

    uint32_t flight_modes_authorized; // [Bitmapped]

    uint16_t controlled_station_1_16_authorized; // [Bitmapped]

    uint16_t component_number_authorized; // [Bitmapped]

    uint16_t sub_component_number_authorized; // [Bitmapped]

    uint16_t vehicle_type; // [enum]

    uint16_t vehicle_subtype;

    uint8_t requesting_cucs_type; // [enum]

    uint16_t requesting_cucs_subtype;

    uint32_t requesting_cucs_id;

    uint8_t presence_vector_support; // [enum]

    uint16_t controlled_station_17_32_authorized; // [Bitmapped]


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint64_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (uint64_t{1} << 0);



        if (has_vsm_id) pv |= (uint64_t{1} << 1);



        if (has_data_link_id) pv |= (uint64_t{1} << 2);



        if (has_loi_authorized) pv |= (uint64_t{1} << 3);



        if (has_flight_mode_offset) pv |= (uint64_t{1} << 4);



        if (has_flight_modes_authorized) pv |= (uint64_t{1} << 5);



        if (has_controlled_station_1_16_authorized) pv |= (uint64_t{1} << 6);



        if (has_component_number_authorized) pv |= (uint64_t{1} << 7);



        if (has_sub_component_number_authorized) pv |= (uint64_t{1} << 8);



        if (has_vehicle_type) pv |= (uint64_t{1} << 9);



        if (has_vehicle_subtype) pv |= (uint64_t{1} << 10);



        if (has_requesting_cucs_type) pv |= (uint64_t{1} << 11);



        if (has_requesting_cucs_subtype) pv |= (uint64_t{1} << 12);



        if (has_requesting_cucs_id) pv |= (uint64_t{1} << 13);



        if (has_presence_vector_support) pv |= (uint64_t{1} << 14);



        if (has_controlled_station_17_32_authorized) pv |= (uint64_t{1} << 15);


        
        cursor.write_int(pv, 3);

        // Write Fields


        if (pv & (uint64_t{1} << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (uint64_t{1} << 1)) {

            cursor.write(vsm_id);

        }



        if (pv & (uint64_t{1} << 2)) {

            cursor.write(data_link_id);

        }



        if (pv & (uint64_t{1} << 3)) {

            cursor.write(loi_authorized);

        }



        if (pv & (uint64_t{1} << 4)) {

            cursor.write(flight_mode_offset);

        }



        if (pv & (uint64_t{1} << 5)) {

            cursor.write(flight_modes_authorized);

        }



        if (pv & (uint64_t{1} << 6)) {

            cursor.write(controlled_station_1_16_authorized);

        }



        if (pv & (uint64_t{1} << 7)) {

            cursor.write(component_number_authorized);

        }



        if (pv & (uint64_t{1} << 8)) {

            cursor.write(sub_component_number_authorized);

        }



        if (pv & (uint64_t{1} << 9)) {

            cursor.write(vehicle_type);

        }



        if (pv & (uint64_t{1} << 10)) {

            cursor.write(vehicle_subtype);

        }



        if (pv & (uint64_t{1} << 11)) {

            cursor.write(requesting_cucs_type);

        }



        if (pv & (uint64_t{1} << 12)) {

            cursor.write(requesting_cucs_subtype);

        }



        if (pv & (uint64_t{1} << 13)) {

            cursor.write(requesting_cucs_id);

        }



        if (pv & (uint64_t{1} << 14)) {

            cursor.write(presence_vector_support);

        }



        if (pv & (uint64_t{1} << 15)) {

            cursor.write(controlled_station_17_32_authorized);

        }


    }

    void deserialize(BitCursor& cursor) {
        uint64_t pv = 0;
        cursor.read_int(pv, 3);

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
            has_data_link_id = true;
            cursor.read(data_link_id);
        }



        if (pv & (uint64_t{1} << 3)) {
            has_loi_authorized = true;
            cursor.read(loi_authorized);
        }



        if (pv & (uint64_t{1} << 4)) {
            has_flight_mode_offset = true;
            cursor.read(flight_mode_offset);
        }



        if (pv & (uint64_t{1} << 5)) {
            has_flight_modes_authorized = true;
            cursor.read(flight_modes_authorized);
        }



        if (pv & (uint64_t{1} << 6)) {
            has_controlled_station_1_16_authorized = true;
            cursor.read(controlled_station_1_16_authorized);
        }



        if (pv & (uint64_t{1} << 7)) {
            has_component_number_authorized = true;
            cursor.read(component_number_authorized);
        }



        if (pv & (uint64_t{1} << 8)) {
            has_sub_component_number_authorized = true;
            cursor.read(sub_component_number_authorized);
        }



        if (pv & (uint64_t{1} << 9)) {
            has_vehicle_type = true;
            cursor.read(vehicle_type);
        }



        if (pv & (uint64_t{1} << 10)) {
            has_vehicle_subtype = true;
            cursor.read(vehicle_subtype);
        }



        if (pv & (uint64_t{1} << 11)) {
            has_requesting_cucs_type = true;
            cursor.read(requesting_cucs_type);
        }



        if (pv & (uint64_t{1} << 12)) {
            has_requesting_cucs_subtype = true;
            cursor.read(requesting_cucs_subtype);
        }



        if (pv & (uint64_t{1} << 13)) {
            has_requesting_cucs_id = true;
            cursor.read(requesting_cucs_id);
        }



        if (pv & (uint64_t{1} << 14)) {
            has_presence_vector_support = true;
            cursor.read(presence_vector_support);
        }



        if (pv & (uint64_t{1} << 15)) {
            has_controlled_station_17_32_authorized = true;
            cursor.read(controlled_station_17_32_authorized);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_vsm_id = false;



    bool has_data_link_id = false;



    bool has_loi_authorized = false;



    bool has_flight_mode_offset = false;



    bool has_flight_modes_authorized = false;



    bool has_controlled_station_1_16_authorized = false;



    bool has_component_number_authorized = false;



    bool has_sub_component_number_authorized = false;



    bool has_vehicle_type = false;



    bool has_vehicle_subtype = false;



    bool has_requesting_cucs_type = false;



    bool has_requesting_cucs_subtype = false;



    bool has_requesting_cucs_id = false;



    bool has_presence_vector_support = false;



    bool has_controlled_station_17_32_authorized = false;


};

} // namespace generated
} // namespace dli

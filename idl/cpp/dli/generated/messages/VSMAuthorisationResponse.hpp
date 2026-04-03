#pragma once

#include <dli/core/BitCursor.hpp>
#include <dli/core/Bam.hpp>
#include <dli/core/Scaled.hpp>
#include <array>
#include <cstdint>

namespace dli {
namespace generated {

/**
 * @brief Auto-generated class for Message #2: VSMAuthorisationResponse
 */
class VSMAuthorisationResponse {
public:
    // Fields

    uint64_t time_stamp; // [ms]

    uint32_t vsm_id;

    uint32_t data_link_id;

    uint8_t access_authorized; // [enum]

    uint8_t access_granted; // [enum]

    uint8_t loi_authorized; // [Bitmapped]

    uint8_t loi_granted; // [Bitmapped]

    uint8_t flight_modes_granted; // [enum]

    uint16_t controlled_station_1_16; // [Bitmapped]

    uint16_t component_number; // [Bitmapped]

    uint16_t sub_component_number; // [Bitmapped]

    uint8_t payload_type; // [enum]

    uint8_t access_requested; // [Bitmapped]

    uint16_t vehicle_type; // [enum]

    uint16_t vehicle_subtype;

    uint8_t cucs_type; // [enum]

    uint16_t cucs_subtype;

    uint8_t presence_vector_support; // [enum]

    uint16_t controlled_station_17_32; // [Bitmapped]


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint64_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (uint64_t{1} << 0);



        if (has_vsm_id) pv |= (uint64_t{1} << 1);



        if (has_data_link_id) pv |= (uint64_t{1} << 2);



        if (has_access_authorized) pv |= (uint64_t{1} << 3);



        if (has_access_granted) pv |= (uint64_t{1} << 4);



        if (has_loi_authorized) pv |= (uint64_t{1} << 5);



        if (has_loi_granted) pv |= (uint64_t{1} << 6);



        if (has_flight_modes_granted) pv |= (uint64_t{1} << 7);



        if (has_controlled_station_1_16) pv |= (uint64_t{1} << 8);



        if (has_component_number) pv |= (uint64_t{1} << 9);



        if (has_sub_component_number) pv |= (uint64_t{1} << 10);



        if (has_payload_type) pv |= (uint64_t{1} << 11);



        if (has_access_requested) pv |= (uint64_t{1} << 12);



        if (has_vehicle_type) pv |= (uint64_t{1} << 13);



        if (has_vehicle_subtype) pv |= (uint64_t{1} << 14);



        if (has_cucs_type) pv |= (uint64_t{1} << 15);



        if (has_cucs_subtype) pv |= (uint64_t{1} << 16);



        if (has_presence_vector_support) pv |= (uint64_t{1} << 17);



        if (has_controlled_station_17_32) pv |= (uint64_t{1} << 18);


        
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

            cursor.write(access_authorized);

        }



        if (pv & (uint64_t{1} << 4)) {

            cursor.write(access_granted);

        }



        if (pv & (uint64_t{1} << 5)) {

            cursor.write(loi_authorized);

        }



        if (pv & (uint64_t{1} << 6)) {

            cursor.write(loi_granted);

        }



        if (pv & (uint64_t{1} << 7)) {

            cursor.write(flight_modes_granted);

        }



        if (pv & (uint64_t{1} << 8)) {

            cursor.write(controlled_station_1_16);

        }



        if (pv & (uint64_t{1} << 9)) {

            cursor.write(component_number);

        }



        if (pv & (uint64_t{1} << 10)) {

            cursor.write(sub_component_number);

        }



        if (pv & (uint64_t{1} << 11)) {

            cursor.write(payload_type);

        }



        if (pv & (uint64_t{1} << 12)) {

            cursor.write(access_requested);

        }



        if (pv & (uint64_t{1} << 13)) {

            cursor.write(vehicle_type);

        }



        if (pv & (uint64_t{1} << 14)) {

            cursor.write(vehicle_subtype);

        }



        if (pv & (uint64_t{1} << 15)) {

            cursor.write(cucs_type);

        }



        if (pv & (uint64_t{1} << 16)) {

            cursor.write(cucs_subtype);

        }



        if (pv & (uint64_t{1} << 17)) {

            cursor.write(presence_vector_support);

        }



        if (pv & (uint64_t{1} << 18)) {

            cursor.write(controlled_station_17_32);

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
            has_access_authorized = true;
            cursor.read(access_authorized);
        }



        if (pv & (uint64_t{1} << 4)) {
            has_access_granted = true;
            cursor.read(access_granted);
        }



        if (pv & (uint64_t{1} << 5)) {
            has_loi_authorized = true;
            cursor.read(loi_authorized);
        }



        if (pv & (uint64_t{1} << 6)) {
            has_loi_granted = true;
            cursor.read(loi_granted);
        }



        if (pv & (uint64_t{1} << 7)) {
            has_flight_modes_granted = true;
            cursor.read(flight_modes_granted);
        }



        if (pv & (uint64_t{1} << 8)) {
            has_controlled_station_1_16 = true;
            cursor.read(controlled_station_1_16);
        }



        if (pv & (uint64_t{1} << 9)) {
            has_component_number = true;
            cursor.read(component_number);
        }



        if (pv & (uint64_t{1} << 10)) {
            has_sub_component_number = true;
            cursor.read(sub_component_number);
        }



        if (pv & (uint64_t{1} << 11)) {
            has_payload_type = true;
            cursor.read(payload_type);
        }



        if (pv & (uint64_t{1} << 12)) {
            has_access_requested = true;
            cursor.read(access_requested);
        }



        if (pv & (uint64_t{1} << 13)) {
            has_vehicle_type = true;
            cursor.read(vehicle_type);
        }



        if (pv & (uint64_t{1} << 14)) {
            has_vehicle_subtype = true;
            cursor.read(vehicle_subtype);
        }



        if (pv & (uint64_t{1} << 15)) {
            has_cucs_type = true;
            cursor.read(cucs_type);
        }



        if (pv & (uint64_t{1} << 16)) {
            has_cucs_subtype = true;
            cursor.read(cucs_subtype);
        }



        if (pv & (uint64_t{1} << 17)) {
            has_presence_vector_support = true;
            cursor.read(presence_vector_support);
        }



        if (pv & (uint64_t{1} << 18)) {
            has_controlled_station_17_32 = true;
            cursor.read(controlled_station_17_32);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_vsm_id = false;



    bool has_data_link_id = false;



    bool has_access_authorized = false;



    bool has_access_granted = false;



    bool has_loi_authorized = false;



    bool has_loi_granted = false;



    bool has_flight_modes_granted = false;



    bool has_controlled_station_1_16 = false;



    bool has_component_number = false;



    bool has_sub_component_number = false;



    bool has_payload_type = false;



    bool has_access_requested = false;



    bool has_vehicle_type = false;



    bool has_vehicle_subtype = false;



    bool has_cucs_type = false;



    bool has_cucs_subtype = false;



    bool has_presence_vector_support = false;



    bool has_controlled_station_17_32 = false;


};

} // namespace generated
} // namespace dli

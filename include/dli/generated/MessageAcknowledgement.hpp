#pragma once

#include "../BitCursor.hpp"
#include "../Bam.hpp"
#include "../Scaled.hpp"
#include <cstdint>

namespace dli {
namespace generated {

/**
 * @brief Auto-generated class for Message #17000: MessageAcknowledgement
 */
class MessageAcknowledgement {
public:
    // Fields

    uint64_t time_stamp; // [ms]

    uint64_t original_time_stamp; // [ms]

    uint32_t original_message_type;

    uint32_t acknowledgement_type; // [enum]


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint32_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (1 << 0);



        if (has_original_time_stamp) pv |= (1 << 1);



        if (has_original_message_type) pv |= (1 << 2);



        if (has_acknowledgement_type) pv |= (1 << 3);


        
        cursor.write_int(pv, 1);

        // Write Fields


        if (pv & (1 << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (1 << 1)) {

            cursor.write_int(original_time_stamp, 5);

        }



        if (pv & (1 << 2)) {

            cursor.write(original_message_type);

        }



        if (pv & (1 << 3)) {

            cursor.write(acknowledgement_type);

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
            has_original_time_stamp = true;
            cursor.read_int(original_time_stamp, 5);
        }



        if (pv & (1 << 2)) {
            has_original_message_type = true;
            cursor.read(original_message_type);
        }



        if (pv & (1 << 3)) {
            has_acknowledgement_type = true;
            cursor.read(acknowledgement_type);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_original_time_stamp = false;



    bool has_original_message_type = false;



    bool has_acknowledgement_type = false;


};

} // namespace generated
} // namespace dli

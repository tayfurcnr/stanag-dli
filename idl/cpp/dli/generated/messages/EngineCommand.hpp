#pragma once

#include <dli/core/BitCursor.hpp>
#include <dli/core/Bam.hpp>
#include <dli/core/Scaled.hpp>
#include <array>
#include <cstdint>

namespace dli {
namespace generated {

/**
 * @brief Auto-generated class for Message #2008: EngineCommand
 */
class EngineCommand {
public:
    // Fields

    uint64_t time_stamp; // [ms]

    uint8_t engine_number;

    uint8_t engine_command; // [enum]

    uint8_t reverse_thrust_power; // [enum]

    uint8_t reverse_thrust; // [enum]

    uint8_t ignition_switch_power; // [enum]

    uint8_t ignition_switch_activation; // [enum]

    uint32_t activity_id;


    /**
     * @brief Serializes the message into the provided BitCursor.
     */
    void serialize(BitCursor& cursor) const {
        uint64_t pv = 0;
        // Calculate Presence Vector (PV)


        if (has_time_stamp) pv |= (uint64_t{1} << 0);



        if (has_engine_number) pv |= (uint64_t{1} << 1);



        if (has_engine_command) pv |= (uint64_t{1} << 2);



        if (has_reverse_thrust_power) pv |= (uint64_t{1} << 3);



        if (has_reverse_thrust) pv |= (uint64_t{1} << 4);



        if (has_ignition_switch_power) pv |= (uint64_t{1} << 5);



        if (has_ignition_switch_activation) pv |= (uint64_t{1} << 6);



        if (has_activity_id) pv |= (uint64_t{1} << 7);


        
        cursor.write_int(pv, 1);

        // Write Fields


        if (pv & (uint64_t{1} << 0)) {

            cursor.write_int(time_stamp, 5);

        }



        if (pv & (uint64_t{1} << 1)) {

            cursor.write(engine_number);

        }



        if (pv & (uint64_t{1} << 2)) {

            cursor.write(engine_command);

        }



        if (pv & (uint64_t{1} << 3)) {

            cursor.write(reverse_thrust_power);

        }



        if (pv & (uint64_t{1} << 4)) {

            cursor.write(reverse_thrust);

        }



        if (pv & (uint64_t{1} << 5)) {

            cursor.write(ignition_switch_power);

        }



        if (pv & (uint64_t{1} << 6)) {

            cursor.write(ignition_switch_activation);

        }



        if (pv & (uint64_t{1} << 7)) {

            cursor.write_int(activity_id, 3);

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
            has_engine_number = true;
            cursor.read(engine_number);
        }



        if (pv & (uint64_t{1} << 2)) {
            has_engine_command = true;
            cursor.read(engine_command);
        }



        if (pv & (uint64_t{1} << 3)) {
            has_reverse_thrust_power = true;
            cursor.read(reverse_thrust_power);
        }



        if (pv & (uint64_t{1} << 4)) {
            has_reverse_thrust = true;
            cursor.read(reverse_thrust);
        }



        if (pv & (uint64_t{1} << 5)) {
            has_ignition_switch_power = true;
            cursor.read(ignition_switch_power);
        }



        if (pv & (uint64_t{1} << 6)) {
            has_ignition_switch_activation = true;
            cursor.read(ignition_switch_activation);
        }



        if (pv & (uint64_t{1} << 7)) {
            has_activity_id = true;
            cursor.read_int(activity_id, 3);
        }


    }

    // Presence Flags for optional fields


    bool has_time_stamp = false;



    bool has_engine_number = false;



    bool has_engine_command = false;



    bool has_reverse_thrust_power = false;



    bool has_reverse_thrust = false;



    bool has_ignition_switch_power = false;



    bool has_ignition_switch_activation = false;



    bool has_activity_id = false;


};

} // namespace generated
} // namespace dli

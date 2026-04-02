#pragma once

#include <cstdint>
#include "BitCursor.hpp"

namespace dli {

/**
 * @brief DLI Message Wrapper Header (Table 4-1, AEP-84 Vol II)
 * Fixed 16-byte structure defining the message identity and routing.
 */
struct DliHeader {
    uint16_t reserved_start{0}; // DLI 3081: 2-byte reserved
    uint16_t payload_length{0}; // DLI 3091: Message Data length
    uint32_t source_id{0};      // Section 1.7.6: 4-byte ID
    uint32_t destination_id{0}; // Section 1.7.6: 4-byte ID
    uint16_t message_type{0};   // 16-bit Message Type
    uint16_t message_properties{0}; // Bitmapped properties
    uint32_t reserved_end{0};   // 4-byte padding/reserved to reach 20-byte wrapper

    static constexpr size_t FIXED_SIZE = 20;

    void serialize(BitCursor& cursor) const {
        cursor.write<uint16_t>(reserved_start);
        cursor.write<uint16_t>(payload_length);
        cursor.write<uint32_t>(source_id);
        cursor.write<uint32_t>(destination_id);
        cursor.write<uint16_t>(message_type);
        cursor.write<uint16_t>(message_properties);
        cursor.write<uint32_t>(reserved_end);
    }

    bool deserialize(BitCursor& cursor) {
        cursor.read<uint16_t>(reserved_start);
        cursor.read<uint16_t>(payload_length);
        cursor.read<uint32_t>(source_id);
        cursor.read<uint32_t>(destination_id);
        cursor.read<uint16_t>(message_type);
        cursor.read<uint16_t>(message_properties);
        cursor.read<uint32_t>(reserved_end);
        return cursor.error() == ErrorState::None;
    }

    // Helper to extract Checksum Type (bits 7:6)
    uint8_t get_checksum_type() const {
        return static_cast<uint8_t>((message_properties >> 6) & 0x03);
    }

    // Helper to get version (bits 14:8)
    uint8_t get_idd_version() const {
        return static_cast<uint8_t>((message_properties >> 8) & 0x7F);
    }

    // Helper to check ACK bit (bit 15)
    bool requires_ack() const {
        return (message_properties & 0x8000) != 0;
    }
};

} // namespace dli

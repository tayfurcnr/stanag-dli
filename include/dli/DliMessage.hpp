#pragma once

#include "DliHeader.hpp"
#include "Checksum.hpp"
#include <optional>
#include <vector>

namespace dli {

/**
 * @brief Complete DLI Protocol Message
 * Combines the fixed Header, a specific Message Body (Payload),
 * and an optional checksum.
 */
template <typename TBody>
struct DliMessage {
    DliHeader header;
    TBody body;
    std::optional<uint32_t> checksum; // Supports 0, 2, or 4 byte checksums

    /**
     * @brief Serialize the whole message into a cursor.
     * Automatically calculates payload length.
     */
    void serialize(BitCursor& cursor) {
        // 1. Placeholder for header (will update length later)
        size_t headerStart = cursor.position();
        header.serialize(cursor);

        // 2. Serialize Body
        size_t bodyStart = cursor.position();
        body.serialize(cursor);
        size_t bodyEnd = cursor.position();

        // 3. Update Payload Length in Header and re-serialize header
        header.payload_length = static_cast<uint16_t>(bodyEnd - bodyStart);

        
        
        size_t currentOffset = cursor.position();
        cursor.setPosition(headerStart);
        header.serialize(cursor);
        cursor.setPosition(currentOffset);

        // 4. Auto-Compute and Serialize Checksum based on Header Properties
        uint8_t type = header.get_checksum_type();
        if (type > 0) {
            const uint8_t* start_ptr = cursor.data() + headerStart;
            size_t length = bodyEnd - headerStart;

            if (type == 0x01) { // 2 bytes (CRC-16-CCITT)
                uint16_t cksum = dli::Checksum::calculateCRC16(start_ptr, length);
                cursor.write<uint16_t>(cksum);
                checksum = cksum;
            } else if (type >= 0x02) { // 4 bytes (CRC-32)
                uint32_t cksum = dli::Checksum::calculateCRC32(start_ptr, length);
                cursor.write<uint32_t>(cksum);
                checksum = cksum;
            }
        }
    }

    /**
     * @brief Deserialize a message. 
     * Expects cursor to be at the start of the message.
     */
    bool deserialize(BitCursor& cursor) {
        if (!header.deserialize(cursor)) return false;
        
        // Deserialize body (void return type in generated code)
        body.deserialize(cursor);
        if (cursor.error() != ErrorState::None) return false;

        // Optional Checksum parsing
        uint8_t cksumType = header.get_checksum_type();
        if (cksumType == 0x01) {
            uint16_t val;
            cursor.read<uint16_t>(val);
            checksum = val;
        } else if (cksumType >= 0x02) {
            uint32_t val;
            cursor.read<uint32_t>(val);
            checksum = val;
        } else {
            checksum = std::nullopt;
        }

        return cursor.error() == ErrorState::None;
    }
};

} // namespace dli

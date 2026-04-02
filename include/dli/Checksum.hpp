#pragma once

#include <cstdint>
#include <vector>

namespace dli {

/**
 * @brief Standardized Checksum Utilities for STANAG 4586 DLI.
 */
class Checksum {
public:
    /**
     * @brief Simple CRC-32 (typical for DLI 4-byte checksum)
     */
    static uint32_t calculateCRC32(const uint8_t* data, size_t length) {
        uint32_t crc = 0xFFFFFFFF;
        for (size_t i = 0; i < length; i++) {
            crc ^= data[i];
            for (int j = 0; j < 8; j++) {
                crc = (crc >> 1) ^ (0xEDB88320 & (-(crc & 1)));
            }
        }
        return ~crc;
    }

    /**
     * @brief 16-bit Checksum (CRC-16-CCITT Poly: 0x1021) as per STANAG 4586 AEP-84
     */
    static uint16_t calculateCRC16(const uint8_t* data, size_t length) {
        uint16_t crc = 0xFFFF;
        for (size_t i = 0; i < length; ++i) {
            crc ^= (static_cast<uint16_t>(data[i]) << 8);
            for (int j = 0; j < 8; ++j) {
                if (crc & 0x8000) {
                    crc = (crc << 1) ^ 0x1021;
                } else {
                    crc = (crc << 1);
                }
            }
        }
        return crc;
    }
};

} // namespace dli

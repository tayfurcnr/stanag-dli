#pragma once

#include <cmath>
#include <cstdint>

namespace dli {
namespace bam {

/**
 * @brief Binary Angular Measurement (BAM) conversion kernels.
 * Inputs are assumed to be in the domain [-PI, PI).
 */
constexpr double PI = 3.14159265358979323846;

inline uint16_t to_bam16(double radians) {
    // Range check (optional, but good for DLI safety)
    if (radians < -PI || radians >= PI) {
        // Handle wrapping or error
    }
    return static_cast<uint16_t>((radians / PI) * 32768.0 + 32768.0);
}

inline double from_bam16(uint16_t bam) {
    return (static_cast<double>(bam) - 32768.0) / 32768.0 * PI;
}

inline uint32_t to_bam32(double radians) {
    return static_cast<uint32_t>((radians / PI) * 2147483648.0 + 2147483648.0);
}

inline double from_bam32(uint32_t bam) {
    return (static_cast<double>(bam) - 2147483648.0) / 2147483648.0 * PI;
}

} // namespace bam
} // namespace dli

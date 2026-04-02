#pragma once

#include <cstdint>

namespace dli {
namespace scaled {

/**
 * @brief Standardized linear scaling mapping logic.
 */
template <typename IntType, typename RealType>
inline IntType to_scaled(RealType physical, RealType offset, RealType scale) {
    return static_cast<IntType>((physical - offset) / scale);
}

template <typename IntType, typename RealType>
inline RealType from_scaled(IntType raw, RealType offset, RealType scale) {
    return static_cast<RealType>(raw) * scale + offset;
}

} // namespace scaled
} // namespace dli

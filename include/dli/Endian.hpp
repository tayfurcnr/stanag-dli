#pragma once

#include <cstdint>
#include <cstring>
#include <type_traits>

#if defined(__linux__) || defined(__FreeBSD__)
#include <endian.h>
#elif defined(__APPLE__)
#include <libkern/OSByteOrder.h>
#endif

namespace dli {
namespace endian {

/**
 * @brief Ensures big-endian serialization regardless of host architecture.
 */
template <typename T>
inline T to_network(T value) {
    static_assert(std::is_integral<T>::value, "Only integral types supported for endian swap.");
    
    if constexpr (sizeof(T) == 1) return value;
    else if constexpr (sizeof(T) == 2) return htobe16(value);
    else if constexpr (sizeof(T) == 4) return htobe32(value);
    else if constexpr (sizeof(T) == 8) return htobe64(value);
    return value;
}

template <typename T>
inline T from_network(T value) {
    static_assert(std::is_integral<T>::value, "Only integral types supported for endian swap.");
    
    if constexpr (sizeof(T) == 1) return value;
    else if constexpr (sizeof(T) == 2) return be16toh(value);
    else if constexpr (sizeof(T) == 4) return be32toh(value);
    else if constexpr (sizeof(T) == 8) return be64toh(value);
    return value;
}

} // namespace endian
} // namespace dli

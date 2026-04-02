#pragma once

#include <cstdint>

namespace dli {

/**
 * @brief Standardized error states for the DLI runtime.
 */
enum class ErrorState {
    None = 0,
    EndOfStream,           ///< Attempted to read/write beyond buffer limits
    InvalidPresenceVector, ///< PV bit mismatch or corrupted PV
    RangeError,            ///< Value exceeds logical domain (e.g., BAM overflow)
    DecodeError,           ///< General field decoding failure
    InvalidLength          ///< Message length field does not match actual bytes
};

} // namespace dli

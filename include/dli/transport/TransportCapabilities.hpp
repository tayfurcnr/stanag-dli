#ifndef DLI_TRANSPORT_CAPABILITIES_HPP
#define DLI_TRANSPORT_CAPABILITIES_HPP

namespace dli {

/**
 * @brief Formal validation modes for incoming DLI frames.
 */
enum class ValidationMode {
    STRICT,  ///< Fail-fast on any malformed header or checksum mismatch.
    LENIENT  ///< Attempt to recover or log warnings (reserved for legacy interoperability).
};

/**
 * @brief Feature flags to communicate active SDK policies during interoperability handshakes.
 */
struct TransportCapabilities {
    /**
     * @brief Enables multi-message concatenation within a single MTU.
     */
    bool supports_packing = true;

    /**
     * @brief Defines how strictly the SDK validates incoming DLI wire-format.
     */
    ValidationMode validation_mode = ValidationMode::STRICT;

    /**
     * @brief Enables logical epsilon adjustments for intra-millisecond timestamps
     *        to ensure reliable ACK correlation (Destination ID based).
     */
    bool timestamp_collision_avoidance = true;
};

} // namespace dli

#endif // DLI_TRANSPORT_CAPABILITIES_HPP

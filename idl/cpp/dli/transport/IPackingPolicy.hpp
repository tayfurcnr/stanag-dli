#ifndef DLI_I_PACKING_POLICY_HPP
#define DLI_I_PACKING_POLICY_HPP

#include <cstddef>
#include <vector>
#include <cstdint>

namespace dli {

/**
 * @brief Abstract interface for throughput-optimized message packing strategies.
 * 
 * Implementations define when to flush the transport buffer based on MTU constraints,
 * latency requirements, or message priority, without altering individual DLI message semantics.
 */
class IPackingPolicy {
public:
    virtual ~IPackingPolicy() = default;

    /**
     * @brief Evaluates if the current accumulated buffer should be transmitted.
     * 
     * @param current_size Current size of the packed buffer in bytes.
     * @param next_message_size Expected size of the next DLI frame to be added.
     * @param mtu Maximum Transmission Unit (implementation policy default is 548).
     * @return true if the buffer should be flushed BEFORE adding the next message.
     */
    virtual bool should_flush(size_t current_size, size_t next_message_size, size_t mtu) const = 0;

    /**
     * @brief Called after a successful transmission to reset policy-specific timers/state.
     */
    virtual void on_flush() = 0;
};

/**
 * @brief Default 'MTU-Limited' packing policy.
 * 
 * Flushes the buffer only when the next message would exceed the MTU threshold.
 */
class MtuBatchingPolicy : public IPackingPolicy {
public:
    bool should_flush(size_t current_size, size_t next_message_size, size_t mtu) const override {
        // If empty, never flush
        if (current_size == 0) return false;
        
        // Flush if adding the next message + wrapper buffer space exceeds MTU
        return (current_size + next_message_size) > mtu;
    }

    void on_flush() override {
        // No state to reset for simple MTU policy
    }
};

} // namespace dli

#endif // DLI_I_PACKING_POLICY_HPP

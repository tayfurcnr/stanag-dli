#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>
#include <dli/core/ErrorState.hpp>
#include <dli/core/Endian.hpp>

namespace dli {

/**
 * @brief Orchestrates byte-aligned bit-level I/O.
 * Phase 1: Only byte-aligned operations supported.
 */
class BitCursor {
public:
    BitCursor(uint8_t* buffer, size_t size)
        : m_buffer(buffer), m_size(size), m_pos(0), m_error(ErrorState::None) {}

    /**
     * @brief Writes an integral value in Big-Endian.
     */
    template <typename T>
    void write(T value) {
        if (m_pos + sizeof(T) > m_size) {
            m_error = ErrorState::EndOfStream;
            return;
        }
        T network_val = endian::to_network(value);
        std::memcpy(m_buffer + m_pos, &network_val, sizeof(T));
        m_pos += sizeof(T);
    }

    /**
     * @brief Reads an integral value from Big-Endian.
     */
    template <typename T>
    void read(T& out_value) {
        if (m_pos + sizeof(T) > m_size) {
            m_error = ErrorState::EndOfStream;
            return;
        }
        T network_val;
        std::memcpy(&network_val, m_buffer + m_pos, sizeof(T));
        out_value = endian::from_network(network_val);
        m_pos += sizeof(T);
    }

    /**
     * @brief Presence-aware write.
     */
    template <typename T>
    void write_if(uint32_t pv, uint8_t bit_index, T value) {
        if (pv & (1 << bit_index)) {
            write(value);
        }
    }

    /**
     * @brief Presence-aware read.
     */
    template <typename T>
    void read_if(uint32_t pv, uint8_t bit_index, T& out_value) {
        if (pv & (1 << bit_index)) {
            read(out_value);
        }
    }

    /**
     * @brief Writes an integral value in Big-Endian with a specific byte size.
     */
    template <typename T>
    void write_int(T value, size_t byte_size) {
        if (m_pos + byte_size > m_size) {
            m_error = ErrorState::EndOfStream;
            return;
        }
        T network_val = endian::to_network(value);
        // Copy the last 'byte_size' bytes for Big-Endian serialization
        uint8_t temp[sizeof(T)];
        std::memcpy(temp, &network_val, sizeof(T));
        
        // In Big-Endian, the significant bytes are at the end of the host-swapped network_val
        // but to_network already swapped them. 
        // Example: uint32 0x12345678 -> network (htobe32) 0x12345678 (on BE) or 0x78563412 (on LE).
        // Actually, if we use htobe32, we just copy the bytes.
        size_t start_offset = sizeof(T) - byte_size;
        std::memcpy(m_buffer + m_pos, temp + start_offset, byte_size);
        m_pos += byte_size;
    }

    /**
     * @brief Reads an integral value from Big-Endian with a specific byte size.
     */
    template <typename T>
    void read_int(T& out_value, size_t byte_size) {
        if (m_pos + byte_size > m_size) {
            m_error = ErrorState::EndOfStream;
            return;
        }
        T network_val = 0;
        uint8_t temp[sizeof(T)] = {0};
        size_t start_offset = sizeof(T) - byte_size;
        std::memcpy(temp + start_offset, m_buffer + m_pos, byte_size);
        std::memcpy(&network_val, temp, sizeof(T));
        out_value = endian::from_network(network_val);
        m_pos += byte_size;
    }

    /**
     * @brief Writes a value only if the corresponding bit in the Presence Vector (PV) is set.
     */
    template <typename T>
    void write_if(uint32_t pv, int bit, T value) {
        if (pv & (1 << bit)) {
            write(value);
        }
    }

    /**
     * @brief Reads a value only if the corresponding bit in the Presence Vector (PV) is set.
     */
    template <typename T>
    void read_if(uint32_t pv, int bit, T& out_value) {
        if (pv & (1 << bit)) {
            read(out_value);
        }
    }

    size_t position() const { return m_pos; }
    size_t byteOffset() const { return m_pos; }
    void setPosition(size_t pos) { m_pos = pos; }
    void setByteOffset(size_t pos) { m_pos = pos; }
    ErrorState error() const { return m_error; }
    void setError(ErrorState err) { m_error = err; }
    
    const uint8_t* data() const { return m_buffer; }

private:
    uint8_t* m_buffer;
    size_t m_size;
    size_t m_pos;
    ErrorState m_error;
};

} // namespace dli

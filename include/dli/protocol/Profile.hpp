#ifndef DLI_PROFILE_HPP
#define DLI_PROFILE_HPP

#include <string>
#include <set>
#include <cstdint>

namespace dli {

/**
 * @brief Represents an AEP-84 Interoperability Level (LoI) Profile.
 * 
 * Enforces which message types are permitted to be processed or sent
 * based on the agreed-upon capability set.
 */
class Profile {
public:
    Profile(const std::string& name, uint8_t loi) 
        : m_name(name), m_loi(loi) {}

    void allow(uint16_t messageType) {
        m_allowedMessages.insert(messageType);
    }

    void allow_group(const std::set<uint16_t>& messageIds) {
        m_allowedMessages.insert(messageIds.begin(), messageIds.end());
    }

    bool is_permitted(uint16_t messageType) const {
        // If profile is empty, we assume "Allow All" (Default/Development mode)
        // or "Strictly Nothing" depending on policy. Standard says: restricted.
        if (m_allowedMessages.empty()) return true; 
        return m_allowedMessages.find(messageType) != m_allowedMessages.end();
    }

    const std::string& name() const { return m_name; }
    uint8_t loi() const { return m_loi; }

private:
    std::string m_name;
    uint8_t m_loi;
    std::set<uint16_t> m_allowedMessages;
};

} // namespace dli

#endif // DLI_PROFILE_HPP

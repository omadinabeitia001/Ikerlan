#include "repeating_key_xor.hpp"
#include <sstream>
#include <iomanip>

std::string repeatingKeyXOR(const std::string& plaintext, const std::string& key) {
    std::ostringstream oss;
    for (size_t i = 0; i < plaintext.size(); ++i) {
        uint8_t xor_byte = plaintext[i] ^ key[i % key.size()];
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(xor_byte);
    }
    return oss.str();
}

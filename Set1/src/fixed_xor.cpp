#include "fixed_xor.hpp"
#include <stdexcept>
#include <iomanip>
#include <sstream>

std::string fixed_xor(const std::string& hex1, const std::string& hex2) {
    if (hex1.length() != hex2.length()) {
        throw std::invalid_argument("Buffers must be of equal length");
    }

    std::stringstream result;
    for (size_t i = 0; i < hex1.length(); i += 2) {
        unsigned char byte1 = std::stoi(hex1.substr(i, 2), nullptr, 16);
        unsigned char byte2 = std::stoi(hex2.substr(i, 2), nullptr, 16);
        unsigned char xor_byte = byte1 ^ byte2;
        result << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(xor_byte);
    }

    return result.str();
}

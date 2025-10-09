#include "../include/hex_to_base64.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <stdexcept>

std::vector<uint8_t> hexToBytes(const std::string& hex) {
    if (hex.size() % 2 != 0)
        throw std::invalid_argument("hex string must have even length");

    std::vector<uint8_t> bytes;
    bytes.reserve(hex.size() / 2);
    for (size_t i = 0; i < hex.length(); i += 2) {
        uint8_t byte = static_cast<uint8_t>(std::stoul(hex.substr(i, 2), nullptr, 16));
        bytes.push_back(byte);
    }
    return bytes;
}

std::string bytesToBase64(const std::vector<uint8_t>& bytes) {
    static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::string base64;
    int val = 0, valb = -6;
    for (uint8_t c : bytes) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            base64.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) base64.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (base64.size() % 4) base64.push_back('=');
    return base64;
}

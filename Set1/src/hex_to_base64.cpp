#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "../include/hex_to_base64.hpp"

std::vector<uint8_t> hexToBytes(const std::string& hex) {
    std::vector<uint8_t> bytes;
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        uint8_t byte = (uint8_t) strtol(byteString.c_str(), nullptr, 16);
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

int main() {
    std::string hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    
    std::vector<uint8_t> bytes = hexToBytes(hex);
    std::string base64 = bytesToBase64(bytes);

    std::cout << base64 << std::endl;

    return 0;
}

#pragma once
#include <string>
#include "single_byte_xor.hpp"

struct DetectionResult {
    std::string original_hex;
    uint8_t key;
    std::string plaintext;
};

DetectionResult detectSingleByteXOR(const std::vector<std::string>& lines);

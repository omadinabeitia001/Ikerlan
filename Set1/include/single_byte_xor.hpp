#pragma once
#include <string>
#include <vector>

struct SingleByteXORResult {
    uint8_t key;
    std::string plaintext;
};

SingleByteXORResult breakSingleByteXOR(const std::vector<uint8_t>& bytes);

double scoreEnglish(const std::string& text);

std::vector<uint8_t> hexToBytes(const std::string& hex);  // ✅ Aquí


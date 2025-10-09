#pragma once
#include <string>
#include <vector>


struct SingleByteXORResult {
    uint8_t key;
    std::string plaintext;
};

SingleByteXORResult breakSingleByteXOR(const std::string& hex);

double scoreEnglish(const std::string& text);

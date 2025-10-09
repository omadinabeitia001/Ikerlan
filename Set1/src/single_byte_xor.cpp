#include "single_byte_xor.hpp"
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include <iomanip>

std::vector<uint8_t> hexToBytes(const std::string& hex) {
    std::vector<uint8_t> bytes;
    for (size_t i = 0; i < hex.length(); i += 2) {
        bytes.push_back(std::stoi(hex.substr(i, 2), nullptr, 16));
    }
    return bytes;
}

double scoreEnglish(const std::string& text) {
    double score = 0.0;
    for (char c : text) {
        c = std::tolower(c);
        if (std::isalpha(c)) score += 1.0;
        if (c == ' ') score += 1.5;
        if (c == 'e') score += 2.0;
    }
    return score;
}

SingleByteXORResult breakSingleByteXOR(const std::string& hex) {
    auto bytes = hexToBytes(hex);
    double bestScore = -1.0;
    std::string bestText;
    uint8_t bestKey = 0;

    for (int key = 0; key <= 255; ++key) {
        std::string candidate;
        for (uint8_t b : bytes) {
            candidate += static_cast<char>(b ^ key);
        }
        double score = scoreEnglish(candidate);
        if (score > bestScore) {
            bestScore = score;
            bestText = candidate;
            bestKey = key;
        }
    }

    return {bestKey, bestText};
}

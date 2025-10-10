#include "utils.hpp"
#include <random>
#include <string>

std::string generateRandomAESKey() {
    std::string key;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    for (int i = 0; i < 16; ++i) {
        key += static_cast<char>(dis(gen));
    }
    return key;
}

std::string generateRandomBytes(size_t length) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 255);
    std::string result;
    result.reserve(length);
    for (size_t i = 0; i < length; ++i) {
        result += static_cast<char>(dist(rng));
    }
    return result;
}
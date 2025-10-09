#include "hamming_distance.hpp"
#include <stdexcept>

int hammingDistance(const std::string& a, const std::string& b) {
    if (a.size() != b.size()) throw std::invalid_argument("Strings must be equal length");

    int distance = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        uint8_t diff = a[i] ^ b[i];
        distance += __builtin_popcount(diff);
    }
    return distance;
}

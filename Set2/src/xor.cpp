#include "xor.hpp"
#include <stdexcept>

std::vector<uint8_t> xorBuffers(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Buffers must be of equal length");
    }

    std::vector<uint8_t> result(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] ^ b[i];
    }

    return result;
}

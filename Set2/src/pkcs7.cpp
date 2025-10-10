#include "pkcs7.hpp"
#include <cstddef>  // ← Esto define size_t
#include <stdexcept>



std::vector<uint8_t> pkcs7Pad(const std::vector<uint8_t>& input, size_t blockSize) {
    size_t padLen = blockSize - (input.size() % blockSize);
    std::vector<uint8_t> padded = input;
    padded.insert(padded.end(), padLen, static_cast<uint8_t>(padLen));
    return padded;
}

std::vector<uint8_t> pkcs7Unpad(const std::vector<uint8_t>& input) {
    if (input.empty()) throw std::runtime_error("Input is empty");

    uint8_t padLen = input.back();
    if (padLen == 0 || padLen > input.size()) throw std::runtime_error("Invalid padding");

    for (size_t i = input.size() - padLen; i < input.size(); ++i) {
        if (input[i] != padLen) throw std::runtime_error("Bad padding");
    }

    return std::vector<uint8_t>(input.begin(), input.end() - padLen);
}

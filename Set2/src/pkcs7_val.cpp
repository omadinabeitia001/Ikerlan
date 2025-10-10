#include "pkcs7_val.hpp"
#include <stdexcept>

std::vector<uint8_t> pkcs7ValidateAndStrip(const std::vector<uint8_t>& input) {
    if (input.empty()) {
        throw std::runtime_error("Input vacío");
    }

    uint8_t padValue = input.back();
    if (padValue == 0 || padValue > input.size()) {
        throw std::runtime_error("Padding inválido");
    }

    for (size_t i = input.size() - padValue; i < input.size(); ++i) {
        if (input[i] != padValue) {
            throw std::runtime_error("Padding inválido");
        }
    }

    return std::vector<uint8_t>(input.begin(), input.end() - padValue);
}
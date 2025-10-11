#include "pkcs7_set3.hpp"
#include <stdexcept>

namespace pkcs7_set3 {

void pkcs7Pad(std::vector<uint8_t>& data, size_t blockSize) {
    size_t padLen = blockSize - (data.size() % blockSize);
    for (size_t i = 0; i < padLen; ++i) {
        data.push_back(static_cast<uint8_t>(padLen));
    }
}

void pkcs7ValidateAndStrip(std::vector<uint8_t>& data) {
    if (data.empty()) throw std::runtime_error("Datos vacíos");

    uint8_t padLen = data.back();
    if (padLen == 0 || padLen > data.size()) {
        throw std::runtime_error("Padding inválido");
    }

    for (size_t i = 0; i < padLen; ++i) {
        if (data[data.size() - 1 - i] != padLen) {
            throw std::runtime_error("Padding inválido");
        }
    }

    data.resize(data.size() - padLen);
}

}

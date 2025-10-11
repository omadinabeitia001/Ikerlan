#pragma once
#include <vector>
#include <cstdint>
#include <cstddef>  

namespace pkcs7_set3 {

// Aplica padding PKCS#7 al vector
void pkcs7Pad(std::vector<uint8_t>& data, size_t blockSize);

// Valida y elimina el padding PKCS#7 del vector
void pkcs7ValidateAndStrip(std::vector<uint8_t>& data);

}

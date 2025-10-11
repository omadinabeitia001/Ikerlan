#pragma once
#include <vector>
#include <string>
#include <cstdint>

namespace ctr {

// Construye el bloque nonce || contador (ambos en little endian)
std::vector<uint8_t> buildCTRBlock(uint64_t nonce, uint64_t counter);

// Cifra o descifra usando AES-CTR (simétrico)
std::vector<uint8_t> aesCTR(const std::vector<uint8_t>& input, const std::string& key, uint64_t nonce);

}

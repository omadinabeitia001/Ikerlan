#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <map>  

namespace ctr_stats {

// Carga y decodifica las líneas base64 desde el archivo
std::vector<std::vector<uint8_t>> loadCiphertexts(const std::string& path);

// Trunca todos los ciphertexts a la longitud mínima
std::vector<std::vector<uint8_t>> truncateToMinLength(const std::vector<std::vector<uint8_t>>& ciphertexts);

// Rompe el keystream como si fuera repeating-key XOR
std::vector<uint8_t> breakFixedNonceCTR(const std::vector<std::vector<uint8_t>>& ciphertexts);

// Descifra usando el keystream
std::vector<std::string> decryptWithKeystream(const std::vector<std::vector<uint8_t>>& ciphertexts, const std::vector<uint8_t>& keystream);

}

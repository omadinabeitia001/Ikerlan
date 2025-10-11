#pragma once
#include <vector>
#include <string>
#include <cstdint>

namespace ctr_breaker {

// Carga las líneas base64 y las convierte en plaintexts
std::vector<std::vector<uint8_t>> loadPlaintexts();

// Cifra cada línea con CTR usando nonce fijo
std::vector<std::vector<uint8_t>> encryptWithFixedNonce(const std::vector<std::vector<uint8_t>>& plaintexts, const std::string& key);

// Estima el keystream usando análisis por frecuencia
std::vector<uint8_t> recoverKeystream(const std::vector<std::vector<uint8_t>>& ciphertexts);

// Descifra los ciphertexts usando el keystream
std::vector<std::string> decryptWithKeystream(const std::vector<std::vector<uint8_t>>& ciphertexts, const std::vector<uint8_t>& keystream);

}

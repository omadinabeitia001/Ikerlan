#pragma once
#include <vector>
#include <cstdint>
#include <string>


namespace pad_oracle {

struct EncryptionResult {
    std::vector<uint8_t> ciphertext;
    std::string iv;
};

// Inicializa la clave global del oracle (solo una vez)
bool padding_oracle_init();

// Genera un IV aleatorio y cifra un mensaje aleatorio con AES-CBC
EncryptionResult encryption_oracle();

// Devuelve true si el ciphertext tiene padding PKCS#7 válido al descifrar
bool padding_oracle_check(const std::string& iv, const std::vector<uint8_t>& ciphertext);


} // namespace pad_oracle

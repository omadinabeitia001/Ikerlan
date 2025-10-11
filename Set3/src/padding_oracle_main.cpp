#include "padding_oracle.hpp"
#include "utils.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

int main(int argc, char** argv) {
    pad_oracle::EncryptionResult enc = pad_oracle::encryption_oracle();

    std::cout << "Ciphertext (hex): ";
    for (uint8_t byte : enc.ciphertext) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
    }
    std::cout << std::endl;

    std::cout << "IV (hex): ";
    for (char c : enc.iv) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)(uint8_t)c;
    }
    std::cout << std::endl;

    // Usar IV como string directamente
    std::string iv = enc.iv;

    // Comprobación de padding original
    bool ok = pad_oracle::padding_oracle_check(iv, enc.ciphertext);
    std::cout << "¿Padding válido?: " << (ok ? "Sí ✅" : "No ❌") << std::endl;

    // Manipulación del ciphertext
    std::vector<uint8_t> tampered = enc.ciphertext;
    if (!tampered.empty()) {
        tampered[0] ^= 0x01; // modificar un byte
    }

    bool ok_tampered = pad_oracle::padding_oracle_check(iv, tampered);
    std::cout << "¿Padding tras manipulación?: " << (ok_tampered ? "Sí ✅" : "No ❌") << std::endl;

    return 0;
}

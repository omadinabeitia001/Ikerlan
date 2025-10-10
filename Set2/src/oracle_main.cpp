#include <iostream>
#include "oracle.hpp"

int main() {
    srand(time(nullptr)); // Semilla aleatoria

    std::vector<uint8_t> input(64, 'A'); // Input con bloques repetidos
    auto ciphertext = encryption_oracle(input);
    std::string mode = detectEncryptionMode(ciphertext);

    std::cout << "🔍 Modo detectado: " << mode << "\n";
    return 0;
}

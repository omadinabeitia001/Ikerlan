#include <iostream>
#include "byte_ecb.hpp"

int main() {
    std::cout << "Descifrando unknown-string con ataque byte-at-a-time ECB...\n";
    std::string decrypted = decryptUnknownString();
    std::cout << "\nTexto descifrado:\n" << decrypted << "\n";
    return 0;
}

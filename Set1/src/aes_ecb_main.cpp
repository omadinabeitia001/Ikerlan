#include "aes_ecb.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::ifstream file("../data/7.txt");
    if (!file.is_open()) {
        std::cerr << "Error: no se pudo abrir el archivo 7.txt" << std::endl;
        return 1;
    }

    std::string base64Ciphertext((std::istreambuf_iterator<char>(file)),
                                  std::istreambuf_iterator<char>());

    // Elimina saltos de línea
    base64Ciphertext.erase(
        std::remove(base64Ciphertext.begin(), base64Ciphertext.end(), '\n'),
        base64Ciphertext.end()
    );

    std::string key = "YELLOW SUBMARINE";
    std::string ciphertext = base64Decode(base64Ciphertext);
    std::string plaintext = aesECBDecrypt(ciphertext, key);

    std::cout << plaintext << std::endl;
    return 0;
}

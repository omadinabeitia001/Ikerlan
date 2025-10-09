#include "../include/break_repeating_key_xor.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm> // <-- Hau behar da std::remove-erako

int main() {
    std::ifstream file("../data/6.txt");
    if (!file.is_open()) {
        std::cerr << "Errorea: ezin da fitxategia ireki." << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string base64Ciphertext = buffer.str();

    // Saltos de línea kendu
    base64Ciphertext.erase(
        std::remove(base64Ciphertext.begin(), base64Ciphertext.end(), '\n'),
        base64Ciphertext.end()
    );

    std::string plaintext = breakRepeatingKeyXOR(base64Ciphertext);
    std::cout << plaintext << std::endl;

    return 0;
}

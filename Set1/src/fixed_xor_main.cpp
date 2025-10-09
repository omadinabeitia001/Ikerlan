#include <iostream>
#include "fixed_xor.hpp"

int main() {
    std::string hex1 = "1c0111001f010100061a024b53535009181c";
    std::string hex2 = "686974207468652062756c6c277320657965";

    try {
        std::string result = fixed_xor(hex1, hex2);
        std::cout << "Resultado XOR: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

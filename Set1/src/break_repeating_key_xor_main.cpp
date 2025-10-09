#include <iostream>
#include <fstream>
#include "../include/break_repeating_key_xor.hpp"

int main() {
    std::ifstream file("../data/6.txt");
    std::string base64Ciphertext((std::istreambuf_iterator<char>(file)),
                                  std::istreambuf_iterator<char>());

    std::string plaintext = breakRepeatingKeyXOR(base64Ciphertext);
    std::cout << "Deszifratu: \n" << plaintext << std::endl;

    return 0;
}

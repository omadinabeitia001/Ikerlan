#include <iostream>
#include "single_byte_xor.hpp"

int main() {
    std::string hex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    auto result = breakSingleByteXOR(hex);

    std::cout << "Key: " << static_cast<int>(result.key) << std::endl;
    std::cout << "Plaintext: " << result.plaintext << std::endl;

    return 0;
}

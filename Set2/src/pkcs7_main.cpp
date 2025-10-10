#include <iostream>
#include <vector>
#include <iomanip>
#include <cstddef>  // ← Esto define size_t
#include <stdexcept>
#include "pkcs7.hpp"

int main() {
    std::string inputStr = "YELLOW SUBMARINE";
    std::vector<uint8_t> input(inputStr.begin(), inputStr.end());

    size_t blockSize = 20;
    auto padded = pkcs7Pad(input, blockSize);

    std::cout << "Texto padded (" << padded.size() << " bytes): ";
    for (uint8_t byte : padded) {
        if (std::isprint(byte)) std::cout << static_cast<char>(byte);
        else std::cout << "\\x" << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
    }
    std::cout << std::endl;

    return 0;
}

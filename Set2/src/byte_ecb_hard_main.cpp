#include <iostream>
#include "byte_ecb_hard.hpp"

int main() {
    std::string result = decryptUnknownStringWithPrefix();
    std::cout << "Texto descifrado:\n" << result << std::endl;
    return 0;
}

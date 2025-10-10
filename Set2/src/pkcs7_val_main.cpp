#include <iostream>
#include "pkcs7_val.hpp"

int main() {
    std::vector<uint8_t> input = {
        'I','C','E',' ','I','C','E',' ','B','A','B','Y', 4,4,4,4
    };

    try {
        auto stripped = pkcs7ValidateAndStrip(input);
        std::string result(stripped.begin(), stripped.end());
        std::cout << "Texto sin padding: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error de padding: " << e.what() << std::endl;
    }

    return 0;
}

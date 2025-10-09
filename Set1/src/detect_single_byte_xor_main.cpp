#include <iostream>
#include <fstream>
#include <vector>
#include "detect_single_byte_xor.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Erabilera: " << argv[0] << " <fitxategia.txt>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Fitxategia ezin da ireki: " << argv[1] << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }

    auto result = detectSingleByteXOR(lines);

    std::cout << "Hasierako lerroa: " << result.original_hex << std::endl;
    std::cout << "Klabea: " << static_cast<int>(result.key) << std::endl;
    std::cout << "Deszifratutako testua: " << result.plaintext << std::endl;

    return 0;
}

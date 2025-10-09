#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

int countRepeatedBlocks(const std::string& hexLine) {
    std::vector<std::string> blocks;
    for (size_t i = 0; i + 32 <= hexLine.size(); i += 32) {
        blocks.push_back(hexLine.substr(i, 32)); // 32 hex chars = 16 bytes
    }

    std::unordered_set<std::string> uniqueBlocks(blocks.begin(), blocks.end());
    return blocks.size() - uniqueBlocks.size(); // Cuántos bloques se repiten
}

int main() {
    std::ifstream file("../data/8.txt");
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo 8.txt" << std::endl;
        return 1;
    }

    std::string line;
    int maxRepeats = 0;
    std::string ecbCandidate;

    while (std::getline(file, line)) {
        int repeats = countRepeatedBlocks(line);
        if (repeats > maxRepeats) {
            maxRepeats = repeats;
            ecbCandidate = line;
        }
    }

    std::cout << "Texto cifrado con ECB:\n" << ecbCandidate << std::endl;
    return 0;
}

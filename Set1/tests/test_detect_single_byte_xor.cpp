#include <gtest/gtest.h>
#include "../include/detect_single_byte_xor.hpp"
#include <fstream>
#include <vector>
#include <string>

TEST(DetectSingleByteXORTest, DetectsEncryptedLineInRealFile) {
    std::ifstream file("../data/4.txt");  
    ASSERT_TRUE(file.is_open()) << "Fitxategia ezin da ireki";

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }

    auto result = detectSingleByteXOR(lines);

    // Testua egiaztatu
    EXPECT_NE(result.plaintext.find("Now that the party is jumping"), std::string::npos)
        << "Ez da aurkitu espero zen esaldia testu deszifratuan";
}

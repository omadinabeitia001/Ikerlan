#include <gtest/gtest.h>
#include "../include/break_repeating_key_xor.hpp"
#include <fstream>
#include <string>

TEST(BreakRepeatingKeyXORTest, DecryptsCorrectly) {
    std::ifstream file("../data/6.txt");
    ASSERT_TRUE(file.is_open());

    std::string base64Ciphertext((std::istreambuf_iterator<char>(file)),
                                  std::istreambuf_iterator<char>());

    base64Ciphertext.erase(
        std::remove(base64Ciphertext.begin(), base64Ciphertext.end(), '\n'),
        base64Ciphertext.end()
    );

    std::string plaintext = breakRepeatingKeyXOR(base64Ciphertext);

    EXPECT_NE(plaintext.find("I'm back and I'm ringin' the bell"), std::string::npos);
    EXPECT_NE(plaintext.find("Play that funky music"), std::string::npos);

}

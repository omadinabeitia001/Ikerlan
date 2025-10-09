#include <gtest/gtest.h>
#include "../include/aes_ecb.hpp"
#include <fstream>
#include <string>
#include <algorithm>

TEST(AES_ECBTest, DecryptsCorrectly) {
    std::ifstream file("../data/7.txt");
    ASSERT_TRUE(file.is_open());

    std::string base64Ciphertext((std::istreambuf_iterator<char>(file)),
                                  std::istreambuf_iterator<char>());

    base64Ciphertext.erase(
        std::remove(base64Ciphertext.begin(), base64Ciphertext.end(), '\n'),
        base64Ciphertext.end()
    );

    std::string key = "YELLOW SUBMARINE";
    std::string ciphertext = base64Decode(base64Ciphertext);
    std::string plaintext = aesECBDecrypt(ciphertext, key);

    EXPECT_NE(plaintext.find("Play that funky music"), std::string::npos);
    EXPECT_NE(plaintext.find("Vanilla Ice is sellin' and you people are buyin'"), std::string::npos);
}

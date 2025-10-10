#include <gtest/gtest.h>
#include "cbc.hpp"
#include <fstream>
#include "base64.hpp"

TEST(CBCDecryptTest, DecryptsCorrectly) {
    std::ifstream file("../data/10.txt");
    std::string base64Data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    auto ciphertext = base64Decode(base64Data);

    std::string key = "YELLOW SUBMARINE";
    std::vector<uint8_t> iv(16, 0x00);

    auto plaintext = aesCBCDecrypt(ciphertext, key, iv);

    std::string expectedStart = "I'm back and I'm ringin' the bell";
    std::string actualStart(plaintext.begin(), plaintext.begin() + expectedStart.size());

    ASSERT_EQ(actualStart, expectedStart);
}

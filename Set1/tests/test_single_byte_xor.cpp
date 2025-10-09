#include <gtest/gtest.h>
#include "../include/single_byte_xor.hpp"

TEST(SingleByteXORTest, BasicDecryption) {
    std::string hex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    auto result = breakSingleByteXOR(hex);

    EXPECT_EQ(result.plaintext, "Cooking MC's like a pound of bacon");
}

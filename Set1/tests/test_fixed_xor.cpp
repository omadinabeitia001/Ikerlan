#include <gtest/gtest.h>
#include "../include/fixed_xor.hpp"

TEST(FixedXORTest, BasicXOR) {
    std::string hex1 = "1c0111001f010100061a024b53535009181c";
    std::string hex2 = "686974207468652062756c6c277320657965";
    std::string expected = "746865206b696420646f6e277420706c6179";

    std::string result = fixed_xor(hex1, hex2);
    EXPECT_EQ(result, expected);
}

TEST(FixedXORTest, UnequalLengthThrows) {
    std::string hex1 = "1c0111";
    std::string hex2 = "68697420";

    EXPECT_THROW(fixed_xor(hex1, hex2), std::invalid_argument);
}

#include <gtest/gtest.h>
#include "pkcs7.hpp"

TEST(PKCS7Test, PadsCorrectly) {
    std::vector<uint8_t> input = {'Y','E','L','L','O','W',' ','S','U','B','M','A','R','I','N','E'};
    auto padded = pkcs7Pad(input, 20);
    ASSERT_EQ(padded.size(), 20);
    ASSERT_EQ(padded[16], 0x04);
    ASSERT_EQ(padded[19], 0x04);
}

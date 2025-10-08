#include <gtest/gtest.h>
#include "../include/hex_to_base64.hpp"

TEST(HexToBase64Test, BasicConversion) {
    std::string hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    std::string expected = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

    auto bytes = hexToBytes(hex);
    auto result = bytesToBase64(bytes);

    EXPECT_EQ(result, expected);
}

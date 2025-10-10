#include "pkcs7_val.hpp"
#include <gtest/gtest.h>

TEST(PKCS7Validation, ValidPadding) {
    std::vector<uint8_t> input = {
        'I','C','E',' ','I','C','E',' ','B','A','B','Y', 4,4,4,4
    };
    auto stripped = pkcs7ValidateAndStrip(input);
    std::string result(stripped.begin(), stripped.end());
    ASSERT_EQ(result, "ICE ICE BABY");
}

TEST(PKCS7Validation, InvalidPaddingValue) {
    std::vector<uint8_t> input = {
        'I','C','E',' ','I','C','E',' ','B','A','B','Y', 5,5,5,5
    };
    ASSERT_THROW(pkcs7ValidateAndStrip(input), std::runtime_error);
}

TEST(PKCS7Validation, InvalidPaddingSequence) {
    std::vector<uint8_t> input = {
        'I','C','E',' ','I','C','E',' ','B','A','B','Y', 1,2,3,4
    };
    ASSERT_THROW(pkcs7ValidateAndStrip(input), std::runtime_error);
}

TEST(PKCS7Validation, FullBlockPaddingValid) {
    std::vector<uint8_t> input(16, 16); // 16 bytes of value 16
    auto stripped = pkcs7ValidateAndStrip(input);
    ASSERT_TRUE(stripped.empty());
}

TEST(PKCS7Validation, ZeroPaddingInvalid) {
    std::vector<uint8_t> input = {
        'T','E','S','T', 0
    };
    ASSERT_THROW(pkcs7ValidateAndStrip(input), std::runtime_error);
}

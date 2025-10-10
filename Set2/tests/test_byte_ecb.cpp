#include <gtest/gtest.h>
#include "byte_ecb.hpp"

TEST(ByteECBTest, DecryptsUnknownString) {
    std::string result = decryptUnknownString();
    ASSERT_TRUE(result.find("Rollin'") != std::string::npos);
    ASSERT_TRUE(result.length() > 100);
}

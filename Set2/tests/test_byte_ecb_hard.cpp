#include "byte_ecb_hard.hpp"
#include <gtest/gtest.h>

TEST(ByteECBHardTest, DecryptsUnknownStringWithPrefix) {
    std::string result = decryptUnknownStringWithPrefix();
    std::cout << "Texto descifrado:\n" << result << std::endl;
    ASSERT_FALSE(result.empty());
}

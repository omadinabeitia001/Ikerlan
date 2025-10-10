#include <gtest/gtest.h>
#include "ecb_cut.hpp"

TEST(ECBCutAndPasteTest, CreatesAdminProfile) {
    std::string key = "YELLOW SUBMARINE";
    std::string forged = generateAdminProfile(key);
    auto parsed = parseKV(forged);

    ASSERT_EQ(parsed["role"], "admin");
    ASSERT_EQ(parsed["uid"], "10");
}

#include <gtest/gtest.h>
#include "../include/hamming_distance.hpp"

TEST(HammingDistanceTest, BasicExample) {
    std::string a = "this is a test";
    std::string b = "wokka wokka!!!";
    EXPECT_EQ(hammingDistance(a, b), 37);
}

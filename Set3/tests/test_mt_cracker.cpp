#include <gtest/gtest.h>
#include "mt_cracker.hpp"
#include "mt19937.hpp"

TEST(MTCrackerTest, CracksSeedFromOutput) {
    uint32_t seed;
    uint32_t output = simulate_rng(seed);

    uint32_t cracked = crack_seed(output, 2000); // 2000 segundos de margen

    EXPECT_EQ(cracked, seed) << "Failed to crack seed from output";
}

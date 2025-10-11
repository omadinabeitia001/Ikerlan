#include <gtest/gtest.h>
#include "mt19937.hpp"

TEST(MT19937Test, FirstTenOutputsMatchReference) {
    MT19937 rng(5489);  // Semilla estándar del paper original

    std::vector<uint32_t> expected = {
        3499211612, 581869302, 3890346734, 3586334585, 545404204,
        4161255391, 3922919429, 949333985, 2715962298, 1323567403
    };

    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(rng.extract_number(), expected[i]) << "Mismatch at index " << i;
    }
}

#include <gtest/gtest.h>
#include "ctr_stats.hpp"

TEST(CTRStatsTest, RecoversLegibleTextFromFixedNonceCTR) {
    auto ciphertexts = ctr_stats::loadCiphertexts("../data/20.txt");
    auto truncated = ctr_stats::truncateToMinLength(ciphertexts);
    auto keystream = ctr_stats::breakFixedNonceCTR(truncated);
    auto recovered = ctr_stats::decryptWithKeystream(truncated, keystream);

    int legibleLines = 0;
    for (const auto& line : recovered) {
        if (line.find("the") != std::string::npos || line.find("and") != std::string::npos || line.find("is") != std::string::npos) {
            legibleLines++;
        }
    }

    EXPECT_GT(legibleLines, 10);  // al menos 10 líneas deben contener palabras comunes
}

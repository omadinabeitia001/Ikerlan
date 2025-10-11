#include "ctr_stats.hpp"
#include <iostream>

int main() {
    auto ciphertexts = ctr_stats::loadCiphertexts("../data/20.txt");
    auto truncated = ctr_stats::truncateToMinLength(ciphertexts);
    auto keystream = ctr_stats::breakFixedNonceCTR(truncated);
    auto recovered = ctr_stats::decryptWithKeystream(truncated, keystream);

    for (const auto& line : recovered) {
        std::cout << line << std::endl;
    }

    return 0;
}

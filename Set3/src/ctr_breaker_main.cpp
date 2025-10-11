#include "ctr_breaker.hpp"
#include "utils_set3.hpp"
#include <iostream>

int main() {
    std::string key = utils_set3::generateRandomAESKey();
    auto plaintexts = ctr_breaker::loadPlaintexts();
    auto ciphertexts = ctr_breaker::encryptWithFixedNonce(plaintexts, key);
    auto keystream = ctr_breaker::recoverKeystream(ciphertexts);
    auto recovered = ctr_breaker::decryptWithKeystream(ciphertexts, keystream);

    for (const auto& line : recovered) {
        std::cout << line << std::endl;
    }

    return 0;
}

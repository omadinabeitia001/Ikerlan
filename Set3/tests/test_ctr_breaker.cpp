#include <gtest/gtest.h>
#include "ctr_breaker.hpp"
#include "utils_set3.hpp"

TEST(CTRBreakerTest, RecoversKeystreamAndDecrypts) {
    std::string key = utils_set3::generateRandomAESKey();
    auto plaintexts = ctr_breaker::loadPlaintexts();
    auto ciphertexts = ctr_breaker::encryptWithFixedNonce(plaintexts, key);
    auto keystream = ctr_breaker::recoverKeystream(ciphertexts);
    auto recovered = ctr_breaker::decryptWithKeystream(ciphertexts, keystream);

    // Validamos que al menos algunas líneas contienen palabras legibles
    int readableLines = 0;
    for (const auto& line : recovered) {
        if (line.find("the") != std::string::npos || line.find("and") != std::string::npos) {
            readableLines++;
        }
    }

    EXPECT_GT(readableLines, 5);  // al menos 5 líneas deben contener palabras comunes
}

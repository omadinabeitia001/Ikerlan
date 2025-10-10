#include "cbc_bitflip.hpp"
#include <gtest/gtest.h>

TEST(CBCBitflipTest, InjectionSucceeds) {
    std::string input = "XXXXXXXXXXXXXX";
    auto ciphertext = cbcEncryptProfile(input);
    auto hacked = performBitflipAttack(ciphertext);
    ASSERT_TRUE(cbcDecryptAndCheck(hacked));
}

TEST(CBCBitflipTest, NormalInputFails) {
    std::string input = ";admin=true;";
    auto ciphertext = cbcEncryptProfile(input);
    ASSERT_FALSE(cbcDecryptAndCheck(ciphertext));
}

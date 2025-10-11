#include <gtest/gtest.h>
#include "mt_stream.hpp"

TEST(MTStreamTest, EncryptDecryptWorks) {
    std::string msg = "HelloWorld12345";
    std::vector<uint8_t> input(msg.begin(), msg.end());
    auto encrypted = mt_stream_cipher(input, 42);
    auto decrypted = mt_stream_cipher(encrypted, 42);
    EXPECT_EQ(decrypted, input);
}

TEST(MTStreamTest, CanRecoverSeed) {
    std::string known = "AAAAAAAAAAAAAA";
    std::string prefix = "junk";
    std::string full = prefix + known;
    std::vector<uint8_t> input(full.begin(), full.end());
    auto encrypted = mt_stream_cipher(input, 1234);
    uint16_t cracked = recover_mt_stream_seed(encrypted, known);
    EXPECT_EQ(cracked, 1234);
}

TEST(MTStreamTest, TokenDetectionWorks) {
    std::string token = generate_token();
    EXPECT_TRUE(is_mt_token(token));
}

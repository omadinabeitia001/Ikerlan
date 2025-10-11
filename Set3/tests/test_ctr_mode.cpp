#include <gtest/gtest.h>
#include "ctr_mode.hpp"
#include "utils_set3.hpp"

TEST(CTRModeTest, DecryptsKnownCiphertext) {
    std::string base64 = "L77na/nrFsKvynd6HzOoG7GHTLXsTVu9qvY/2syLXzhPweyyMTJULu/6/kXX0KSvoOLSFQ==";
    std::vector<uint8_t> ciphertext = utils_set3::base64Decode(base64);
    std::vector<uint8_t> plaintext = ctr::aesCTR(ciphertext, "YELLOW SUBMARINE", 0);

    std::string result(plaintext.begin(), plaintext.end());
    EXPECT_TRUE(result.find("Ice, Ice, baby") != std::string::npos);  // ✅ texto real
}

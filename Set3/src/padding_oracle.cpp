#include "padding_oracle.hpp"
#include "aes_cbc.hpp"
#include "pkcs7_set3.hpp"

#include "utils_set3.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

namespace pad_oracle {

static std::string g_key;

bool padding_oracle_init() {
    if (g_key.empty()) {
        g_key = utils_set3::generateRandomAESKey();
        if (g_key.size() != 16) {
            throw std::runtime_error("generateRandomAESKey() no devolvió 16 bytes");
        }
    }
    return true;
}

static const std::vector<std::string> base64_msgs = {
    "V2hlbiBpbiBkb3VidCwgeW91IGdvdGEgZ2lvIHdpdGggeW91ciBndXQ=",
    "TGlmZSBpcyBsaWtlIGEgYm94IG9mIGNob2NvbGF0ZXMu",
    "QXR0YWNrIGFuZCBwYWRkaW5nIG9yYWNsZXMgYXJlIGZ1biE="
};

EncryptionResult encryption_oracle() {
    padding_oracle_init();

    size_t idx = rand() % base64_msgs.size();
    std::string chosen = base64_msgs[idx];

    std::vector<uint8_t> plaintext = utils_set3::base64Decode(chosen);
    pkcs7_set3::pkcs7Pad(plaintext, 16);

    std::string iv = utils_set3::generateRandomBytes(16);
    std::vector<uint8_t> ciphertext = aesCBCEncrypt(plaintext, g_key, iv);

    return { ciphertext, iv };
}

bool padding_oracle_check(const std::string& iv, const std::vector<uint8_t>& ciphertext) {
    try {
        std::vector<uint8_t> plaintext = aesCBCDecrypt(ciphertext, g_key, iv);
        pkcs7_set3::pkcs7ValidateAndStrip(plaintext);
        return true;
    } catch (...) {
        return false;
    }
}

}

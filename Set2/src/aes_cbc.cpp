#include "aes_cbc.hpp"
#include "aes_ecb.hpp"
#include <vector>
#include <string>
#include <cstdint>

std::vector<uint8_t> aesCBCEncrypt(const std::vector<uint8_t>& plaintext, const std::string& key, const std::string& iv) {
    const size_t blockSize = 16;
    std::vector<uint8_t> ciphertext;
    std::vector<uint8_t> previous(iv.begin(), iv.end());

    for (size_t i = 0; i < plaintext.size(); i += blockSize) {
        std::vector<uint8_t> block(plaintext.begin() + i, plaintext.begin() + i + blockSize);
        for (size_t j = 0; j < blockSize; ++j) {
            block[j] ^= previous[j];
        }
        auto encrypted = aesECBEncrypt(block, key);
        ciphertext.insert(ciphertext.end(), encrypted.begin(), encrypted.end());
        previous = encrypted;
    }

    return ciphertext;
}

std::vector<uint8_t> aesCBCDecrypt(const std::vector<uint8_t>& ciphertext, const std::string& key, const std::string& iv) {
    const size_t blockSize = 16;
    std::vector<uint8_t> plaintext;
    std::vector<uint8_t> previous(iv.begin(), iv.end());

    for (size_t i = 0; i < ciphertext.size(); i += blockSize) {
        std::vector<uint8_t> block(ciphertext.begin() + i, ciphertext.begin() + i + blockSize);
        auto decrypted = aesECBDecrypt(block, key);
        for (size_t j = 0; j < blockSize; ++j) {
            decrypted[j] ^= previous[j];
        }
        plaintext.insert(plaintext.end(), decrypted.begin(), decrypted.end());
        previous = block;
    }

    return plaintext;
}

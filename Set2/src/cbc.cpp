#include "cbc.hpp"
#include "aes_ecb.hpp"
#include "xor.hpp"
#include "pkcs7.hpp"
#include <stdexcept>
#include <openssl/evp.h>



std::vector<uint8_t> aesCBCDecrypt(const std::vector<uint8_t>& ciphertext, const std::string& key, const std::vector<uint8_t>& iv) {
    const size_t blockSize = 16;

    if (ciphertext.size() % blockSize != 0) {
        throw std::runtime_error("Ciphertext size must be a multiple of 16");
    }

    std::vector<uint8_t> plaintext;
    std::vector<uint8_t> prevBlock = iv;

    for (size_t i = 0; i < ciphertext.size(); i += blockSize) {
        std::vector<uint8_t> block(ciphertext.begin() + i, ciphertext.begin() + i + blockSize);
        auto decrypted = aesECBDecrypt(block, key);
        auto xored = xorBuffers(decrypted, prevBlock);
        plaintext.insert(plaintext.end(), xored.begin(), xored.end());
        prevBlock = block;
    }

    return pkcs7Unpad(plaintext);
}

std::vector<uint8_t> aesCBCEncrypt(const std::vector<uint8_t>& plaintext, const std::string& key, const std::vector<uint8_t>& iv) {
    if (plaintext.empty()) {
        throw std::runtime_error("Plaintext is empty");
    }
    if (plaintext.size() % 16 != 0) {
        throw std::runtime_error("Plaintext size must be a multiple of 16");
    }

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    std::vector<uint8_t> ciphertext(plaintext.size() + EVP_MAX_BLOCK_LENGTH);
    int len = 0, finalLen = 0;

    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, reinterpret_cast<const unsigned char*>(key.data()), iv.data());
    EVP_CIPHER_CTX_set_padding(ctx, 0);

    EVP_EncryptUpdate(ctx, ciphertext.data(), &len, plaintext.data(), plaintext.size());
    EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &finalLen);
    EVP_CIPHER_CTX_free(ctx);

    ciphertext.resize(len + finalLen);
    return ciphertext;
}

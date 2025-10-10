#include "aes_ecb.hpp"
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <stdexcept>
#include <vector>
#include <string>
#include "base64.hpp"

std::vector<uint8_t> aesECBDecrypt(const std::vector<uint8_t>& ciphertext, const std::string& key) {
    if (ciphertext.empty()) {
        throw std::runtime_error("Ciphertext is empty");
    }
    if (ciphertext.size() % 16 != 0) {
        throw std::runtime_error("Ciphertext size must be a multiple of 16");
    }

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    std::vector<uint8_t> plaintext(ciphertext.size() + EVP_MAX_BLOCK_LENGTH);
    int len = 0, finalLen = 0;

    EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), nullptr, reinterpret_cast<const unsigned char*>(key.data()), nullptr);
    EVP_CIPHER_CTX_set_padding(ctx, 0);

    EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(), ciphertext.size());
    EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &finalLen);
    EVP_CIPHER_CTX_free(ctx);

    plaintext.resize(len + finalLen);
    return plaintext;
}

std::vector<uint8_t> aesECBEncrypt(const std::vector<uint8_t>& plaintext, const std::string& key) {
    if (plaintext.empty()) {
        throw std::runtime_error("Plaintext is empty");
    }

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    std::vector<uint8_t> ciphertext(plaintext.size() + EVP_MAX_BLOCK_LENGTH);
    int len = 0, finalLen = 0;

    EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), nullptr, reinterpret_cast<const unsigned char*>(key.data()), nullptr);
    EVP_CIPHER_CTX_set_padding(ctx, 0);

    EVP_EncryptUpdate(ctx, ciphertext.data(), &len, plaintext.data(), plaintext.size());
    EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &finalLen);
    EVP_CIPHER_CTX_free(ctx);

    ciphertext.resize(len + finalLen);
    return ciphertext;
}

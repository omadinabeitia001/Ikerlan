#include "aes_ecb.hpp"
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <vector>
#include <stdexcept>
#include <string>
#include <algorithm>

std::string base64Decode(const std::string& input) {
    size_t maxDecodedSize = (input.length() * 3) / 4;
    std::vector<char> buffer(maxDecodedSize);

    BIO* bio = BIO_new_mem_buf(input.data(), input.length());
    BIO* b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

    int decodedLength = BIO_read(bio, buffer.data(), maxDecodedSize);
    BIO_free_all(bio);

    if (decodedLength <= 0) {
        throw std::runtime_error("Base64 decoding failed");
    }

    return std::string(buffer.data(), decodedLength);
}

std::string aesECBDecrypt(const std::string& ciphertext, const std::string& key) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    std::vector<unsigned char> plaintext(ciphertext.size() + EVP_MAX_BLOCK_LENGTH);
    int len = 0, finalLen = 0;

    EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), nullptr, (const unsigned char*)key.data(), nullptr);
    EVP_CIPHER_CTX_set_padding(ctx, 0); // No padding automático

    EVP_DecryptUpdate(ctx, plaintext.data(), &len, (const unsigned char*)ciphertext.data(), ciphertext.size());
    EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &finalLen);
    EVP_CIPHER_CTX_free(ctx);

    return std::string(plaintext.begin(), plaintext.begin() + len + finalLen);
}

#include "break_repeating_key_xor.hpp"
#include "hamming_distance.hpp"
#include "single_byte_xor.hpp"
#include "repeating_key_xor.hpp"
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <sstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <cmath>
#include <map>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <iomanip>
#include <fstream>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

std::string base64Decode(const std::string& input) {
    BIO* bio, *b64;
    char* buffer = (char*)malloc(input.length());
    memset(buffer, 0, input.length());

    bio = BIO_new_mem_buf(input.data(), input.length());
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

    int decodedLength = BIO_read(bio, buffer, input.length());
    BIO_free_all(bio);

    std::string result(buffer, decodedLength);
    free(buffer);
    return result;
}

int normalizedHamming(const std::string& a, const std::string& b, int keysize) {
    return hammingDistance(a, b) / keysize;
}

std::string breakRepeatingKeyXOR(const std::string& base64Ciphertext) {
    std::string ciphertext = base64Decode(base64Ciphertext);

    int bestKeysize = 0;
    double bestScore = std::numeric_limits<double>::max();

    for (int keysize = 2; keysize <= 40; ++keysize) {
        std::string block1 = ciphertext.substr(0, keysize);
        std::string block2 = ciphertext.substr(keysize, keysize);
        std::string block3 = ciphertext.substr(2 * keysize, keysize);
        std::string block4 = ciphertext.substr(3 * keysize, keysize);

        double dist1 = hammingDistance(block1, block2) / static_cast<double>(keysize);
        double dist2 = hammingDistance(block2, block3) / static_cast<double>(keysize);
        double dist3 = hammingDistance(block3, block4) / static_cast<double>(keysize);
        double avgDist = (dist1 + dist2 + dist3) / 3.0;

        if (avgDist < bestScore) {
            bestScore = avgDist;
            bestKeysize = keysize;
        }
    }

    std::vector<std::string> blocks;
    for (size_t i = 0; i < ciphertext.size(); i += bestKeysize) {
        blocks.push_back(ciphertext.substr(i, bestKeysize));
    }

    std::vector<std::string> transposed(bestKeysize);
    for (const auto& block : blocks) {
        for (size_t i = 0; i < block.size(); ++i) {
            transposed[i] += block[i];
        }
    }

    std::string key;
    for (const auto& block : transposed) {
        auto result = breakSingleByteXOR(block);
        key += static_cast<char>(result.key);
    }

    std::string plaintext;
    for (size_t i = 0; i < ciphertext.size(); ++i) {
        plaintext += ciphertext[i] ^ key[i % key.size()];
    }

    return plaintext;
}

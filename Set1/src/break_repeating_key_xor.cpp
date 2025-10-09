#include "break_repeating_key_xor.hpp"
#include "hamming_distance.hpp"
#include "single_byte_xor.hpp"
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <vector>
#include <string>
#include <limits>
#include <stdexcept>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream> // Para imprimir clave si quieres

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

std::string breakRepeatingKeyXOR(const std::string& base64Ciphertext) {
    std::string ciphertext = base64Decode(base64Ciphertext);

    std::vector<std::pair<int, double>> keysizeScores;

    for (int keysize = 2; keysize <= 40; ++keysize) {
        if (ciphertext.size() < 4 * keysize) continue;

        std::string block1 = ciphertext.substr(0, keysize);
        std::string block2 = ciphertext.substr(keysize, keysize);
        std::string block3 = ciphertext.substr(2 * keysize, keysize);
        std::string block4 = ciphertext.substr(3 * keysize, keysize);

        double dist1 = hammingDistance(block1, block2) / static_cast<double>(keysize);
        double dist2 = hammingDistance(block2, block3) / static_cast<double>(keysize);
        double dist3 = hammingDistance(block3, block4) / static_cast<double>(keysize);
        double avgDist = (dist1 + dist2 + dist3) / 3.0;

        keysizeScores.push_back({keysize, avgDist});
    }

    std::sort(keysizeScores.begin(), keysizeScores.end(),
              [](const auto& a, const auto& b) { return a.second < b.second; });

    std::string bestPlaintext;
    double bestTextScore = -1.0;

    for (int i = 0; i < 3; ++i) {
        int keysize = keysizeScores[i].first;

        std::vector<std::string> blocks;
        for (size_t j = 0; j < ciphertext.size(); j += keysize) {
            blocks.push_back(ciphertext.substr(j, keysize));
        }

        std::vector<std::string> transposed(keysize);
        for (const auto& block : blocks) {
            for (size_t k = 0; k < block.size(); ++k) {
                transposed[k] += block[k];
            }
        }

        std::string key;
        for (const auto& block : transposed) {
            std::vector<uint8_t> blockBytes(block.begin(), block.end());
            auto result = breakSingleByteXOR(blockBytes);
            key += static_cast<char>(result.key);
        }

        std::string plaintext;
        for (size_t j = 0; j < ciphertext.size(); ++j) {
            plaintext += ciphertext[j] ^ key[j % key.size()];
        }

        double score = scoreEnglish(plaintext);
        if (score > bestTextScore) {
            bestTextScore = score;
            bestPlaintext = plaintext;

            // Opcional: imprime la clave
            std::cout << "Clave encontrada: " << key << std::endl;
        }
    }

    std::cout << "Texto elegido:\n" << bestPlaintext.substr(0, 300) << std::endl;

    return bestPlaintext;
}

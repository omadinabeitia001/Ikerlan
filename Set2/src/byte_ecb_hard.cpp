#include "byte_ecb_hard.hpp"
#include "aes_ecb.hpp"
#include "pkcs7.hpp"
#include "base64.hpp"
#include "utils.hpp"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <random>

// Clave AES fija
static std::string globalKey = generateRandomAESKey();

// Texto secreto codificado en base64
static std::string base64Secret =
    "Um9sbGluJyBpbiBteSA1LjAKV2l0aCBteSByYWctdG9wIGRvd24gc28gbXkg"
    "aGFpciBjYW4gYmxvdwpUaGUgZ2lybGllcyBvbiBzdGFuZGJ5IHdhdmluZyBq"
    "dXN0IHRvIHNheSBoaQpEaWQgeW91IHN0b3A/IE5vLCBJIGp1c3QgZHJvdmUg"
    "YnkK";

// Genera un prefijo aleatorio de longitud aleatoria
std::string generateRandomPrefix() {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(5, 32);
    int len = dist(rng);
    return generateRandomBytes(len);
}
static std::string fixedPrefix = generateRandomPrefix();  
// Oráculo con prefijo aleatorio
std::vector<uint8_t> encryptionOracleWithPrefix(const std::string& input) {
    static std::string fixedPrefix = generateRandomPrefix();

    // Decodifica el secreto solo una vez
    static std::vector<uint8_t> decodedSecret = base64Decode(base64Secret);
    std::string unknown(decodedSecret.begin(), decodedSecret.end());

    std::string full = fixedPrefix + input + unknown;
    auto padded = pkcs7Pad(std::vector<uint8_t>(full.begin(), full.end()), 16);
    return aesECBEncrypt(padded, globalKey);
}

// Detecta cuántos bytes tiene el prefijo aleatorio
int detectPrefixLength() {
    const int blockSize = 16;
    std::string marker(2 * blockSize, 'A');

    for (int pad = 0; pad < blockSize * 2; ++pad) {
        std::string input(pad, 'X');
        input += marker;

        auto ciphertext = encryptionOracleWithPrefix(input);

        for (size_t i = 0; i < ciphertext.size() - 2 * blockSize; i += blockSize) {
            bool match = true;
            for (int j = 0; j < blockSize; ++j) {
                if (ciphertext[i + j] != ciphertext[i + blockSize + j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                int prefixLen = i - pad;
                return prefixLen;
            }
        }
    }

    std::cerr << "No se pudo detectar el prefijo." << std::endl;
    return -1;
}

// Descifra el texto secreto con prefijo aleatorio
std::string decryptUnknownStringWithPrefix() {
    const int blockSize = 16;
    int prefixLen = detectPrefixLength();
    if (prefixLen < 0) return "Error al detectar prefijo.";

    int misalignment = prefixLen % blockSize;
    int padLen = blockSize - misalignment;
    std::string alignmentPad(padLen, 'A');

    std::string known;

    for (int i = 0; i < 138; ++i) {
        int blockOffset = (prefixLen + padLen + known.size()) / blockSize;
        int padSize = blockSize - (known.size() % blockSize) - 1;
        std::string prefix = alignmentPad + std::string(padSize, 'A');

        auto target = encryptionOracleWithPrefix(prefix);
        if (target.size() < (blockOffset + 1) * blockSize) break;

        std::map<std::vector<uint8_t>, char> dict;
        for (int b = 0; b < 256; ++b) {
            std::string test = prefix + known + static_cast<char>(b);
            auto testBlock = encryptionOracleWithPrefix(test);
            std::vector<uint8_t> key(
                testBlock.begin() + blockOffset * blockSize,
                testBlock.begin() + (blockOffset + 1) * blockSize
            );
            dict[key] = static_cast<char>(b);
        }

        std::vector<uint8_t> targetBlock(
            target.begin() + blockOffset * blockSize,
            target.begin() + (blockOffset + 1) * blockSize
        );

        if (dict.count(targetBlock)) {
            known += dict[targetBlock];
            std::cout << "Descifrado hasta ahora: " << known << std::endl;
        } else {
            break;
        }
    }

    return known;
}

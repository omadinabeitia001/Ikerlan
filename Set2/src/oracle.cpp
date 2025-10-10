#include "oracle.hpp"
#include "aes_ecb.hpp"
#include "cbc.hpp"
#include "pkcs7.hpp"
#include <cstdlib>
#include <ctime>
#include <set>

std::vector<uint8_t> generateRandomAESKey() {
    std::vector<uint8_t> key(16);
    for (auto& byte : key) byte = rand() % 256;
    return key;
}

std::vector<uint8_t> encryption_oracle(const std::vector<uint8_t>& input) {
    std::vector<uint8_t> key = generateRandomAESKey();
    std::vector<uint8_t> iv(16);
    for (auto& byte : iv) byte = rand() % 256;

    int prefixLen = 5 + rand() % 6;
    int suffixLen = 5 + rand() % 6;

    std::vector<uint8_t> modifiedInput;
    for (int i = 0; i < prefixLen; ++i) modifiedInput.push_back(rand() % 256);
    modifiedInput.insert(modifiedInput.end(), input.begin(), input.end());
    for (int i = 0; i < suffixLen; ++i) modifiedInput.push_back(rand() % 256);

    auto padded = pkcs7Pad(modifiedInput, 16);
    bool useECB = rand() % 2;

    if (useECB) {
        return aesECBEncrypt(padded, std::string(key.begin(), key.end()));
    } else {
        return aesCBCEncrypt(padded, std::string(key.begin(), key.end()), iv);
    }
}

std::string detectEncryptionMode(const std::vector<uint8_t>& ciphertext) {
    const size_t blockSize = 16;
    std::set<std::vector<uint8_t>> seenBlocks;

    for (size_t i = 0; i + blockSize <= ciphertext.size(); i += blockSize) {
        std::vector<uint8_t> block(ciphertext.begin() + i, ciphertext.begin() + i + blockSize);
        if (seenBlocks.count(block)) {
            return "ECB";
        }
        seenBlocks.insert(block);
    }
    return "CBC";
}
std::pair<std::vector<uint8_t>, std::string> test_encryption_oracle(const std::vector<uint8_t>& input) {
    std::vector<uint8_t> key = generateRandomAESKey();
    std::vector<uint8_t> iv(16);
    for (auto& byte : iv) byte = rand() % 256;

    int prefixLen = 5 + rand() % 6;
    int suffixLen = 5 + rand() % 6;

    std::vector<uint8_t> modifiedInput;
    for (int i = 0; i < prefixLen; ++i) modifiedInput.push_back(rand() % 256);
    modifiedInput.insert(modifiedInput.end(), input.begin(), input.end());
    for (int i = 0; i < suffixLen; ++i) modifiedInput.push_back(rand() % 256);

    auto padded = pkcs7Pad(modifiedInput, 16);
    bool useECB = rand() % 2;

    std::vector<uint8_t> ciphertext;
    std::string mode;

    if (useECB) {
        ciphertext = aesECBEncrypt(padded, std::string(key.begin(), key.end()));
        mode = "ECB";
    } else {
        ciphertext = aesCBCEncrypt(padded, std::string(key.begin(), key.end()), iv);
        mode = "CBC";
    }

    return {ciphertext, mode};
}

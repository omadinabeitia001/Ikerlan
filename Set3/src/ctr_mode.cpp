#include "ctr_mode.hpp"
#include "aes_ecb.hpp"  // Usa AES-ECB como base

namespace ctr {

std::vector<uint8_t> buildCTRBlock(uint64_t nonce, uint64_t counter) {
    std::vector<uint8_t> block(16);
    for (int i = 0; i < 8; ++i) block[i] = (nonce >> (8 * i)) & 0xFF;
    for (int i = 0; i < 8; ++i) block[8 + i] = (counter >> (8 * i)) & 0xFF;
    return block;
}

std::vector<uint8_t> aesCTR(const std::vector<uint8_t>& input, const std::string& key, uint64_t nonce) {
    std::vector<uint8_t> output;
    size_t blockSize = 16;
    size_t numBlocks = (input.size() + blockSize - 1) / blockSize;

    for (size_t i = 0; i < numBlocks; ++i) {
        std::vector<uint8_t> ctrBlock = buildCTRBlock(nonce, i);
        std::vector<uint8_t> keystream = aesECBEncrypt(ctrBlock, key);

        size_t offset = i * blockSize;
        size_t chunkSize = std::min(blockSize, input.size() - offset);

        for (size_t j = 0; j < chunkSize; ++j) {
            output.push_back(input[offset + j] ^ keystream[j]);
        }
    }

    return output;
}

}

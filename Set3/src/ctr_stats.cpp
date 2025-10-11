#include "ctr_stats.hpp"
#include "utils_set3.hpp"
#include <fstream>
#include <algorithm>
#include <cctype>

namespace ctr_stats {

std::vector<std::vector<uint8_t>> loadCiphertexts(const std::string& path) {
    std::ifstream file(path);
    std::vector<std::vector<uint8_t>> ciphertexts;
    std::string line;
    while (std::getline(file, line)) {
        ciphertexts.push_back(utils_set3::base64Decode(line));
    }
    return ciphertexts;
}

std::vector<std::vector<uint8_t>> truncateToMinLength(const std::vector<std::vector<uint8_t>>& ciphertexts) {
    size_t minLen = ciphertexts[0].size();
    for (const auto& c : ciphertexts) {
        minLen = std::min(minLen, c.size());
    }

    std::vector<std::vector<uint8_t>> truncated;
    for (const auto& c : ciphertexts) {
        truncated.emplace_back(c.begin(), c.begin() + minLen);
    }
    return truncated;
}

std::vector<uint8_t> breakFixedNonceCTR(const std::vector<std::vector<uint8_t>>& ciphertexts) {
    size_t keyLen = ciphertexts[0].size();
    std::vector<uint8_t> keystream(keyLen);

    for (size_t i = 0; i < keyLen; ++i) {
        std::map<uint8_t, int> scores;
        for (uint8_t k = 0; k < 255; ++k) {
            int score = 0;
            for (const auto& c : ciphertexts) {
                char ch = c[i] ^ k;
                if (isalpha(ch) || ch == ' ') score++;
            }
            scores[k] = score;
        }

        keystream[i] = std::max_element(scores.begin(), scores.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; })->first;
    }

    return keystream;
}

std::vector<std::string> decryptWithKeystream(const std::vector<std::vector<uint8_t>>& ciphertexts, const std::vector<uint8_t>& keystream) {
    std::vector<std::string> results;
    for (const auto& c : ciphertexts) {
        std::string line;
        for (size_t i = 0; i < c.size(); ++i) {
            line += static_cast<char>(c[i] ^ keystream[i]);
        }
        results.push_back(line);
    }
    return results;
}

}

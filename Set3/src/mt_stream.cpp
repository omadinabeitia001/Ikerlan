#include "mt_stream.hpp"
#include "mt19937.hpp"
#include <ctime>

std::vector<uint8_t> mt_stream_cipher(const std::vector<uint8_t>& input, uint16_t seed) {
    MT19937 rng(seed);
    std::vector<uint8_t> output;
    for (size_t i = 0; i < input.size(); ++i) {
        if (i % 4 == 0) rng.extract_number();
        uint8_t keystream_byte = (rng.extract_number() >> ((i % 4) * 8)) & 0xFF;
        output.push_back(input[i] ^ keystream_byte);
    }
    return output;
}

uint16_t recover_mt_stream_seed(const std::vector<uint8_t>& ciphertext, const std::string& known_suffix) {
    for (uint16_t seed = 0; seed < 65536; ++seed) {
        auto decrypted = mt_stream_cipher(ciphertext, seed);
        if (decrypted.size() >= known_suffix.size()) {
            bool match = true;
            for (size_t i = 0; i < known_suffix.size(); ++i) {
                if (decrypted[decrypted.size() - known_suffix.size() + i] != known_suffix[i]) {
                    match = false;
                    break;
                }
            }
            if (match) return seed;
        }
    }
    return 0xFFFF;
}

std::string generate_token() {
    uint32_t seed = static_cast<uint32_t>(std::time(nullptr));
    MT19937 rng(seed);
    std::string token;
    for (int i = 0; i < 16; ++i) {
        token += static_cast<char>(rng.extract_number() & 0xFF);
    }
    return token;
}

bool is_mt_token(const std::string& token, uint32_t time_window) {
    uint32_t now = static_cast<uint32_t>(std::time(nullptr));
    for (uint32_t t = now - time_window; t <= now + time_window; ++t) {
        MT19937 rng(t);
        std::string candidate;
        for (size_t i = 0; i < token.size(); ++i) {
            candidate += static_cast<char>(rng.extract_number() & 0xFF);
        }
        if (candidate == token) return true;
    }
    return false;
}

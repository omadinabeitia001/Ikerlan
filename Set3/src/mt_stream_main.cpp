#include <iostream>
#include "mt_stream.hpp"

int main() {
    std::string known = "AAAAAAAAAAAAAA";
    std::string prefix = "randomprefix";
    std::string full = prefix + known;

    std::vector<uint8_t> plaintext(full.begin(), full.end());
    uint16_t seed = 1337;

    auto ciphertext = mt_stream_cipher(plaintext, seed);
    uint16_t cracked = recover_mt_stream_seed(ciphertext, known);

    std::cout << "Original seed: " << seed << "\n";
    std::cout << "Cracked seed:  " << cracked << "\n";

    std::string token = generate_token();
    std::cout << "Generated token: " << token << "\n";
    std::cout << "Is MT token? " << (is_mt_token(token) ? "✅ yes" : "❌ no") << "\n";

    return 0;
}

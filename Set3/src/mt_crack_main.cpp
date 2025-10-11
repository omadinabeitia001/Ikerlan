#include <iostream>
#include <ctime>
#include "mt_cracker.hpp"

int main() {
    uint32_t real_seed;
    uint32_t output = simulate_rng(real_seed);

    std::cout << "[+] RNG output: " << output << std::endl;

    uint32_t cracked = crack_seed(output);

    if (cracked == real_seed) {
        std::cout << "[✓] Seed cracked successfully: " << cracked << std::endl;
    } else {
        std::cout << "[✗] Failed to crack seed. Got: " << cracked << ", expected: " << real_seed << std::endl;
    }

    return 0;
}

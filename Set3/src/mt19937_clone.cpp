#include "mt19937_clone.hpp"

#define N 624
#define M 397
#define MATRIX_A 0x9908b0df
#define UPPER_MASK 0x80000000
#define LOWER_MASK 0x7fffffff

MT19937Clone::MT19937Clone(uint32_t seed) : state(N), index(N) {
    state[0] = seed;
    for (int i = 1; i < N; i++) {
        state[i] = 1812433253UL * (state[i - 1] ^ (state[i - 1] >> 30)) + i;
    }
}

uint32_t MT19937Clone::extract_number() {
    if (index >= N) twist();

    uint32_t y = state[index];
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680;
    y ^= (y << 15) & 0xefc60000;
    y ^= (y >> 18);

    index++;
    return y;
}

void MT19937Clone::twist() {
    for (int i = 0; i < N; i++) {
        uint32_t y = (state[i] & UPPER_MASK) + (state[(i + 1) % N] & LOWER_MASK);
        state[i] = state[(i + M) % N] ^ (y >> 1);
        if (y % 2) state[i] ^= MATRIX_A;
    }
    index = 0;
}

void MT19937Clone::set_state(const std::vector<uint32_t>& s) {
    state = s;
}

void MT19937Clone::set_index(int idx) {
    index = idx;
}

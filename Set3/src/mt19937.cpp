// mt19937.cpp
#include "mt19937.hpp"
#include <cstdint>

const int MT19937::w;
const int MT19937::n;
const int MT19937::m;
const uint32_t MT19937::a;
const uint32_t MT19937::u;
const uint32_t MT19937::d;
const uint32_t MT19937::s;
const uint32_t MT19937::b;
const uint32_t MT19937::t;
const uint32_t MT19937::c;
const uint32_t MT19937::l;
const uint32_t MT19937::f;

// Constructor delega a seed_mt
MT19937::MT19937(uint32_t seed) : MT(n), index(n) {
    seed_mt(seed);
}

void MT19937::seed_mt(uint32_t seed) {
    MT[0] = seed;
    for (int i = 1; i < n; ++i) {
        uint32_t prev = MT[i-1];
        MT[i] = f * (prev ^ (prev >> (w - 2))) + (uint32_t)i;
    }
    index = n;
}

uint32_t MT19937::extract_number() {
    if (index >= n) {
        twist();
    }

    uint32_t y = MT[index];

    // tempering (exacto)
    y ^= (y >> u);
    y ^= (y << s) & b;
    y ^= (y << t) & c;
    y ^= (y >> l);

    ++index;
    return y;
}

void MT19937::twist() {
    const uint32_t upper_mask = 0x80000000u;
    const uint32_t lower_mask = 0x7FFFFFFFu;

    for (int i = 0; i < n; ++i) {
        uint32_t x = (MT[i] & upper_mask) + (MT[(i + 1) % n] & lower_mask);
        uint32_t xA = x >> 1;
        if (x & 1u) { // lowest bit set
            xA ^= a;
        }
        MT[i] = MT[(i + m) % n] ^ xA;
    }
    index = 0;
}

void MT19937::set_state(const std::vector<uint32_t>& new_state) {
    // expect new_state.size() == n, but we won't assert here (puedes añadir check)
    MT = new_state;
    index = 0;
}


#include "mt_clone.hpp"

// Constructor por defecto
MTClone::MTClone() : index(N) {
    seed(5489); // semilla por defecto
}

// Constructor con semilla
MTClone::MTClone(uint32_t s) : index(N) {
    seed(s);
}

// Inicializa el estado interno con una semilla
void MTClone::seed(uint32_t s) {
    mt[0] = s;
    for (int i = 1; i < N; i++) {
        mt[i] = 1812433253u * (mt[i - 1] ^ (mt[i - 1] >> 30)) + i;
    }
    index = N;
}

uint32_t MTClone::extract_number() {
    if (index >= N) twist();

    uint32_t y = mt[index];
    // temper
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9D2C5680u;
    y ^= (y << 15) & 0xEFC60000u;
    y ^= (y >> 18);

    ++index;
    return y;
}

void MTClone::twist() {
    for (int i = 0; i < N; ++i) {
        uint32_t x = (mt[i] & UPPER_MASK) + (mt[(i + 1) % N] & LOWER_MASK);
        uint32_t xA = x >> 1;
        if ((x & 1u) != 0) xA ^= MATRIX_A;
        mt[i] = mt[(i + M) % N] ^ xA;
    }
    index = 0;
}

void MTClone::set_state(const std::array<uint32_t, N>& st) {
    mt = st;
    index = N; // para que twist se llame en la próxima extracción
}

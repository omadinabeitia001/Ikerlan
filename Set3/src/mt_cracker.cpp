#include "mt_cracker.hpp"
#include "mt19937.hpp"
#include <ctime>
#include <cstdlib>

// Simula el comportamiento de un sistema que usa MT19937 con una semilla basada en el timestamp
uint32_t simulate_rng(uint32_t& used_seed) {
    // Simula espera aleatoria antes de sembrar
    std::srand(std::time(nullptr));
    int wait1 = 40 + std::rand() % 961; // entre 40 y 1000 segundos
    int wait2 = 40 + std::rand() % 961;

    // Simula el paso del tiempo
    std::time_t now = std::time(nullptr);
    used_seed = static_cast<uint32_t>(now + wait1);

    // Crea el RNG con la semilla simulada
    MT19937 rng(used_seed);
    (void)wait2; // Simula otra espera (no afecta al RNG)

    // Devuelve la primera salida del RNG
    return rng.extract_number();
}

// Intenta descubrir la semilla original a partir de una salida del RNG
uint32_t crack_seed(uint32_t output, uint32_t time_window) {
    std::time_t now = std::time(nullptr);

    // Recorre posibles timestamps en una ventana alrededor del tiempo actual
    for (uint32_t t = now + time_window; t >= now - time_window; --t) {
        MT19937 rng(t);
        if (rng.extract_number() == output) {
            return t; // Semilla encontrada
        }
    }

    return 0; // No se encontró ninguna semilla que produzca esa salida
}

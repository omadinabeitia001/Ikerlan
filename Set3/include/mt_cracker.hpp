#ifndef MT_CRACKER_HPP
#define MT_CRACKER_HPP

#include <cstdint>

uint32_t simulate_rng(uint32_t& used_seed);
uint32_t crack_seed(uint32_t output, uint32_t time_window = 2000);

#endif

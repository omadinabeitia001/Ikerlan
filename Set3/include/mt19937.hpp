#ifndef MT19937_HPP
#define MT19937_HPP

#include <cstdint>
#include <vector>

class MT19937 {
public:
    MT19937(uint32_t seed);
    uint32_t extract_number();
    void seed_mt(uint32_t seed);
    void set_state(const std::vector<uint32_t>& new_state); 

private:
    static const int w = 32;
    static const int n = 624;
    static const int m = 397;
    static const uint32_t a = 0x9908B0DF;
    static const uint32_t u = 11;
    static const uint32_t d = 0xFFFFFFFF;
    static const uint32_t s = 7;
    static const uint32_t b = 0x9D2C5680;
    static const uint32_t t = 15;
    static const uint32_t c = 0xEFC60000;
    static const uint32_t l = 18;
    static const uint32_t f = 1812433253;

    std::vector<uint32_t> MT;
    int index;

    void twist();
};

#endif

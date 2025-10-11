#ifndef MT_CLONE_HPP
#define MT_CLONE_HPP

#include <array>
#include <cstdint>

class MTClone {
public:
    static const int N = 624;
    static const int M = 397;
    static const uint32_t MATRIX_A = 0x9908B0DFu;
    static const uint32_t UPPER_MASK = 0x80000000u;
    static const uint32_t LOWER_MASK = 0x7FFFFFFFu;

    MTClone();           // constructor por defecto
    MTClone(uint32_t s); // constructor con semilla

    uint32_t extract_number();
    void set_state(const std::array<uint32_t, N>& st);

private:
    void twist();
    void seed(uint32_t s);

    std::array<uint32_t, N> mt{};
    int index;
};

#endif

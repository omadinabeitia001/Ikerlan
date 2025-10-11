#pragma once
#include <vector>
#include <cstdint>

class MT19937Clone {
public:
    MT19937Clone(uint32_t seed = 5489);
    uint32_t extract_number();
    void set_state(const std::vector<uint32_t>& s);
    void set_index(int idx);

private:
    void twist();
    std::vector<uint32_t> state;
    int index;
};

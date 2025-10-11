#include <cstdint>

uint32_t undo_right_shift_xor(uint32_t y, int shift) {
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        uint32_t part = (i - shift >= 0) ? ((result >> shift) & 1) : 0;
        result |= (((y >> i) & 1) ^ part) << i;
    }
    return result;
}

uint32_t undo_left_shift_xor_and(uint32_t y, int shift, uint32_t mask) {
    uint32_t result = 0;
    for (int i = 31; i >= 0; i--) {
        uint32_t part = (i + shift <= 31) ? (((result << shift) & mask) >> i) & 1 : 0;
        result |= (((y >> i) & 1) ^ part) << i;
    }
    return result;
}

uint32_t untemper(uint32_t y) {
    y = undo_right_shift_xor(y, 18);
    y = undo_left_shift_xor_and(y, 15, 0xEFC60000);
    y = undo_left_shift_xor_and(y, 7, 0x9D2C5680);
    y = undo_right_shift_xor(y, 11);
    return y;
}

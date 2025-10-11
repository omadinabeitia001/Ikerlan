#ifndef UNTEMPER_HPP
#define UNTEMPER_HPP

#include <cstdint>

uint32_t undo_right_shift_xor(uint32_t y, int shift);
uint32_t undo_left_shift_xor_and(uint32_t y, int shift, uint32_t mask);
uint32_t untemper(uint32_t y);

#endif // UNTEMPER_HPP

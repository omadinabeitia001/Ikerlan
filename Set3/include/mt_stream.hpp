#ifndef MT_STREAM_HPP
#define MT_STREAM_HPP

#include <vector>
#include <string>
#include <cstdint>

std::vector<uint8_t> mt_stream_cipher(const std::vector<uint8_t>& input, uint16_t seed);
uint16_t recover_mt_stream_seed(const std::vector<uint8_t>& ciphertext, const std::string& known_suffix);

std::string generate_token();
bool is_mt_token(const std::string& token, uint32_t time_window = 300);

#endif

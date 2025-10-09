#ifndef HEX_TO_BASE64_HPP
#define HEX_TO_BASE64_HPP

#include <string>
#include <vector>

std::vector<uint8_t> hexToBytes(const std::string& hex);
std::string bytesToBase64(const std::vector<uint8_t>& bytes);

#endif // HEX_TO_BASE64_HPP

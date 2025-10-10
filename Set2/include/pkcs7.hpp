#pragma once
#include <vector>
#include <cstdint>
#include <cstddef>  // Esto define size_t


std::vector<uint8_t> pkcs7Pad(const std::vector<uint8_t>& input, size_t blockSize);
std::vector<uint8_t> pkcs7Unpad(const std::vector<uint8_t>& input);

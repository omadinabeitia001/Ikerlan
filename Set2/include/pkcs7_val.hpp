#pragma once
#include <vector>
#include <cstdint>

std::vector<uint8_t> pkcs7ValidateAndStrip(const std::vector<uint8_t>& input);

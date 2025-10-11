#pragma once
#include <vector>
#include <cstdint>
#include "pkcs7.hpp"

std::vector<uint8_t> pkcs7ValidateAndStrip(const std::vector<uint8_t>& input);

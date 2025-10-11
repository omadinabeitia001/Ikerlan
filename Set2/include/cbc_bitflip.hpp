#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include "pkcs7.hpp"
std::vector<uint8_t> cbcEncryptProfile(const std::string& userdata);
bool cbcDecryptAndCheck(const std::vector<uint8_t>& ciphertext);
std::vector<uint8_t> performBitflipAttack(const std::vector<uint8_t>& ciphertext);


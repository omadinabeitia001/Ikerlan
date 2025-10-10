#pragma once
#include <vector>
#include <string>
#include <cstdint>

std::vector<uint8_t> aesCBCEncrypt(const std::vector<uint8_t>& plaintext, const std::string& key, const std::string& iv);
std::vector<uint8_t> aesCBCDecrypt(const std::vector<uint8_t>& ciphertext, const std::string& key, const std::string& iv);

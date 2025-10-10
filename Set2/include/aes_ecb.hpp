#pragma once
#include <string>
#include <vector>
#include <cstdint>

std::vector<uint8_t> base64Decode(const std::string& input);
std::vector<uint8_t> aesECBDecrypt(const std::vector<uint8_t>& ciphertext, const std::string& key);
std::vector<uint8_t> aesECBEncrypt(const std::vector<uint8_t>& plaintext, const std::string& key);

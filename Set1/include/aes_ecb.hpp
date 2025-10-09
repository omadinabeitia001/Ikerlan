#pragma once
#include <string>

std::string base64Decode(const std::string& input);
std::string aesECBDecrypt(const std::string& ciphertext, const std::string& key);

#pragma once
#include <vector>
#include <string>

std::vector<uint8_t> generateRandomAESKey();
std::vector<uint8_t> encryption_oracle(const std::vector<uint8_t>& input);
std::string detectEncryptionMode(const std::vector<uint8_t>& ciphertext);
std::pair<std::vector<uint8_t>, std::string> test_encryption_oracle(const std::vector<uint8_t>& input);

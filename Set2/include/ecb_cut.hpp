#pragma once
#include <string>
#include <vector>
#include <map>

std::string profile_for(const std::string& email);
std::map<std::string, std::string> parseKV(const std::string& input);
std::vector<uint8_t> encryptProfile(const std::string& profile, const std::string& key);
std::string decryptProfile(const std::vector<uint8_t>& ciphertext, const std::string& key);
std::string generateAdminProfile(const std::string& key);

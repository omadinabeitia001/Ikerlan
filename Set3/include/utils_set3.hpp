#pragma once
#include <vector>
#include <string>

namespace utils_set3 {

std::string generateRandomAESKey();
std::string generateRandomBytes(size_t len);
std::vector<uint8_t> base64Decode(const std::string& input);

}

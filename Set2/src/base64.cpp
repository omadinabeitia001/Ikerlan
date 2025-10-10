// src/base64.cpp
#include "base64.hpp"
#include <vector>
#include <string>
#include <cstdint>
#include <iostream>
#include <algorithm>

static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static inline bool is_base64_char(unsigned char c) {
    return ( (c >= 'A' && c <= 'Z') ||
             (c >= 'a' && c <= 'z') ||
             (c >= '0' && c <= '9') ||
             c == '+' || c == '/' || c == '=' );
}

std::vector<uint8_t> base64Decode(const std::string& encoded_string) {
    std::cerr << "[base64Decode] called, input len=" << encoded_string.size() << "\n";
    // build a clean copy keeping only base64 chars (including '=')
    std::string clean;
    clean.reserve(encoded_string.size());
    for (unsigned char c : encoded_string) {
        if (is_base64_char(c)) clean.push_back(c);
    }
    std::cerr << "[base64Decode] clean len=" << clean.size() << "\n";

    int in_len = static_cast<int>(clean.size());
    int i = 0;
    int in_ = 0;
    uint8_t char_array_4[4], char_array_3[3];
    std::vector<uint8_t> ret;
    ret.reserve((clean.size()*3)/4);

    while (in_len-- && (clean[in_] != '=') && is_base64_char(clean[in_])) {
        char_array_4[i++] = clean[in_]; in_++;
        if (i == 4) {
            int vals[4];
            for (i = 0; i < 4; i++) vals[i] = static_cast<int>(base64_chars.find(char_array_4[i]));
            char_array_3[0] = ( vals[0] << 2 ) + ((vals[1] & 0x30) >> 4);
            char_array_3[1] = ((vals[1] & 0xf) << 4) + ((vals[2] & 0x3c) >> 2);
            char_array_3[2] = ((vals[2] & 0x3) << 6) + vals[3];

            for (i = 0; (i < 3); i++) ret.push_back(char_array_3[i]);
            i = 0;
        }
    }

    if (i) {
        for (int j = i; j < 4; j++) char_array_4[j] = 0;
        int vals[4];
        for (int j = 0; j < 4; j++) vals[j] = static_cast<int>(base64_chars.find(char_array_4[j]));
        char_array_3[0] = ( vals[0] << 2 ) + ((vals[1] & 0x30) >> 4);
        char_array_3[1] = ((vals[1] & 0xf) << 4) + ((vals[2] & 0x3c) >> 2);
        char_array_3[2] = ((vals[2] & 0x3) << 6) + vals[3];

        for (int j = 0; j < i - 1; j++) ret.push_back(char_array_3[j]);
    }

    std::cerr << "[base64Decode] returning len=" << ret.size() << "\n";
    return ret;
}

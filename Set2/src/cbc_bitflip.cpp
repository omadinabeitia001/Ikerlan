#include "cbc_bitflip.hpp"
#include "aes_cbc.hpp"
#include "pkcs7_val.hpp"
#include "pkcs7.hpp"
#include "utils.hpp"
#include <stdexcept>
#include <algorithm>
#include <iostream>

// Clave AES fija
static std::string globalKey = generateRandomAESKey();
static std::string globalIV = generateRandomAESKey(); // CBC necesita IV

std::string sanitizeInput(const std::string& input) {
    std::string result;
    for (char c : input) {
        if (c == ';') result += "%3B";
        else if (c == '=') result += "%3D";
        else result += c;
    }
    return result;
}

std::vector<uint8_t> cbcEncryptProfile(const std::string& userdata) {
    std::string prefix = "comment1=cooking%20MCs;userdata=";
    std::string suffix = ";comment2=%20like%20a%20pound%20of%20bacon";
    std::string full = prefix + sanitizeInput(userdata) + suffix;

    auto padded = pkcs7Pad(std::vector<uint8_t>(full.begin(), full.end()), 16);
    return aesCBCEncrypt(padded, globalKey, globalIV);
}

bool cbcDecryptAndCheck(const std::vector<uint8_t>& ciphertext) {
    auto decrypted = aesCBCDecrypt(ciphertext, globalKey, globalIV);
    auto unpadded = pkcs7ValidateAndStrip(decrypted);
    std::string result(unpadded.begin(), unpadded.end());
    return result.find(";admin=true;") != std::string::npos;
}

std::vector<uint8_t> performBitflipAttack(const std::vector<uint8_t>& ciphertext) {
    std::vector<uint8_t> modified = ciphertext;

    // Queremos inyectar ";admin=true;" en el bloque que contiene userdata
    // Localiza el bloque anterior y modifica sus bytes para forzar el XOR deseado

    std::string target = ";admin=true;";
    std::string injected = "%3Badmin%3Dtrue%3B"; // lo que se cifró originalmente

    size_t offset = 32; // suponiendo que userdata empieza en el tercer bloque

    for (size_t i = 0; i < target.size(); ++i) {
        modified[offset + i] ^= injected[i] ^ target[i];
    }

    return modified;
}

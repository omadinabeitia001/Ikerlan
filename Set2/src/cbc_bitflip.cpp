#include "cbc_bitflip.hpp"
#include "aes_cbc.hpp"
#include "aes_ecb.hpp"
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

// intenta todos los posibles bytes originales (0..255)
std::vector<uint8_t> performBitflipAttack(const std::vector<uint8_t>& ciphertext) {
    std::vector<uint8_t> modified = ciphertext;

    const size_t BLOCK = 16;
    const size_t prefix_len = 32; // como antes
    if (ciphertext.size() < prefix_len + BLOCK) {
        throw std::runtime_error("ciphertext demasiado corto para atacar");
    }

    const size_t target_block_start = prefix_len;
    const size_t prev_block_start   = target_block_start - BLOCK;
    const std::string target = ";admin=true;"; // 12 bytes

    if (prev_block_start + target.size() > modified.size()) {
        throw std::runtime_error("ciphertext demasiado corto para modificar los bytes requeridos");
    }

    // Copia original del bloque anterior para poder probar varios candidatos
    std::vector<uint8_t> original_prev_block(modified.begin() + prev_block_start,
                                             modified.begin() + prev_block_start + target.size());

    // Probar todos los posibles bytes originales (0..255)
    for (int candidate = 0; candidate <= 255; ++candidate) {
        // restaura estado original de los bytes que tocaremos
        for (size_t i = 0; i < target.size(); ++i) {
            modified[prev_block_start + i] = original_prev_block[i];
        }

        // aplica el flip asumiendo que el plaintext original en esas posiciones era 'candidate'
        for (size_t i = 0; i < target.size(); ++i) {
            modified[prev_block_start + i] ^= static_cast<uint8_t>(candidate) ^ static_cast<uint8_t>(target[i]);
        }

        // prueba si el cambio consigue el flag admin
        if (cbcDecryptAndCheck(modified)) {
            return modified; // éxito
        }
        // si no, seguimos con el siguiente candidate
    }

    // Si nada funciona, devolvemos la última modificación (sin éxito)
    return modified;
}
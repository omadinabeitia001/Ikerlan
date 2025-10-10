#include "ecb_cut.hpp"
#include "pkcs7.hpp"
#include "aes_ecb.hpp"
#include <sstream>
#include <map>

std::string sanitizeEmail(const std::string& email) {
    std::string clean;
    for (char c : email) {
        if (c != '&' && c != '=') clean += c;
    }
    return clean;
}

std::string profile_for(const std::string& email) {
    std::string cleanEmail = sanitizeEmail(email);
    return "email=" + cleanEmail + "&uid=10&role=user";
}

std::map<std::string, std::string> parseKV(const std::string& input) {
    std::map<std::string, std::string> result;
    std::stringstream ss(input);
    std::string pair;

    while (std::getline(ss, pair, '&')) {
        size_t pos = pair.find('=');
        if (pos != std::string::npos) {
            result[pair.substr(0, pos)] = pair.substr(pos + 1);
        }
    }
    return result;
}
std::string decryptProfile(const std::vector<uint8_t>& ciphertext, const std::string& key) {
    auto decrypted = aesECBDecrypt(ciphertext, key);
    auto unpadded = pkcs7Unpad(decrypted);
    return std::string(unpadded.begin(), unpadded.end());
}

std::vector<uint8_t> encryptProfile(const std::string& profile, const std::string& key) {
    auto padded = pkcs7Pad(std::vector<uint8_t>(profile.begin(), profile.end()), 16);
    return aesECBEncrypt(padded, key);
}

std::string generateAdminProfile(const std::string& key) {
    // 1️⃣ Crear bloque cifrado con "&role=admin"
    std::string adminText = "&role=admin";
    auto paddedAdmin = pkcs7Pad(std::vector<uint8_t>(adminText.begin(), adminText.end()), 16);
    auto adminBlock = aesECBEncrypt(paddedAdmin, key);

    // 2️⃣ Crear perfil donde 'role=' empiece al inicio de un bloque
    std::string email = "foooooooooooooo@x.c"; // 17 caracteres exactos
    std::string profile = profile_for(email);
    auto normalCipher = encryptProfile(profile, key);

    // 3️⃣ Mantener los dos primeros bloques (email + uid)
    std::vector<uint8_t> forged;
    forged.insert(forged.end(), normalCipher.begin(), normalCipher.begin() + 32);
    forged.insert(forged.end(), adminBlock.begin(), adminBlock.end());

    // 4️⃣ Devolver texto plano descifrado
    return decryptProfile(forged, key);
}

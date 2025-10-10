#include "byte_ecb.hpp"
#include "aes_ecb.hpp"
#include "pkcs7.hpp"
#include "base64.hpp"
#include "utils.hpp"
#include <map>
#include <string>
#include <vector>
#include <iostream>

static std::string globalKey = generateRandomAESKey();

static std::string base64Secret =
    "Um9sbGluJyBpbiBteSA1LjAKV2l0aCBteSByYWctdG9wIGRvd24gc28gbXkg"
    "aGFpciBjYW4gYmxvdwpUaGUgZ2lybGllcyBvbiBzdGFuZGJ5IHdhdmluZyBq"
    "dXN0IHRvIHNheSBoaQpEaWQgeW91IHN0b3A/IE5vLCBJIGp1c3QgZHJvdmUg"
    "YnkK";

std::vector<uint8_t> encryptionOracle(const std::string& input) {
    // 1) Limpiar la cadena base64 original: quedarnos solo con los caracteres válidos
    std::string clean;
    clean.reserve(base64Secret.size());
    for (unsigned char c : base64Secret) {
        if ((c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9') ||
            c == '+' || c == '/' || c == '=') {
            clean.push_back(c);
        }
    }

    // 2) Asegurar padding correcto (múltiplo de 4)
    size_t pad = (4 - (clean.size() % 4)) % 4;
    if (pad) clean.append(pad, '=');

    // 3) Depuración: imprimir la cadena que vamos a decodificar (porciones)
    std::cerr << "[DEBUG] clean base64 length: " << clean.size() << "\n";
    std::cerr << "[DEBUG] clean base64 (first 120 chars):\n"
              << clean.substr(0, std::min<size_t>(clean.size(), 120)) << "\n";

    // 4) Intentar decodificar con tu base64Decode robusto
    std::vector<uint8_t> unknownBytes;
    try {
        unknownBytes = base64Decode(clean);
    } catch (const std::exception& e) {
        std::cerr << "Error al decodificar base64: " << e.what() << std::endl;
        std::cerr << "[DEBUG] clean base64 (hex/len): len=" << clean.size() << "\n";
        std::cerr << "[DEBUG] clean base64 hex (first 80 chars): ";
        for (size_t i = 0; i < std::min<size_t>(clean.size(), 80); ++i) {
            unsigned char c = clean[i];
            char buf[8];
            snprintf(buf, sizeof(buf), "%02x", (unsigned)c);
            std::cerr << buf;
        }
        std::cerr << "\n";
        return {};
    }

    if (unknownBytes.empty()) {
        std::cerr << "Error: base64Decode devolvió vector vacío (length 0)\n";
        return {};
    }

    std::string unknown(unknownBytes.begin(), unknownBytes.end());
    // 5) Construir texto y cifrar
    std::string full = input + unknown;
    auto padded = pkcs7Pad(std::vector<uint8_t>(full.begin(), full.end()), 16);
    return aesECBEncrypt(padded, globalKey);
}
std::string decryptUnknownString() {
    const int blockSize = 16;
    std::vector<uint8_t> recovered; // recolectamos bytes aquí (no string)
    size_t total_bytes_found = 0;

    // límite razonable: por ejemplo 512 bytes (evita bucle infinito)
    for (size_t i = 0; i < 512; ++i) {
        int padLen = blockSize - (recovered.size() % blockSize) - 1;
        std::string prefix(padLen, 'A');

        auto target = encryptionOracle(prefix);
        if (target.size() < blockSize) break;

        size_t blockIndex = recovered.size() / blockSize;

        // obtener bloque objetivo
        if (target.size() < (blockIndex + 1) * blockSize) break;
        std::vector<uint8_t> targetBlock(target.begin() + blockIndex * blockSize,
                                         target.begin() + (blockIndex + 1) * blockSize);

        // construir diccionario
        std::map<std::vector<uint8_t>, uint8_t> dict;
        for (int b = 0; b < 256; ++b) {
            std::string probe = prefix;
            // añadir los bytes ya conocidos
            probe.append(reinterpret_cast<const char*>(recovered.data()), recovered.size());
            probe.push_back(static_cast<char>(b));

            auto probeCt = encryptionOracle(probe);
            if (probeCt.size() < (blockIndex + 1) * blockSize) continue;
            std::vector<uint8_t> probeBlock(probeCt.begin() + blockIndex * blockSize,
                                            probeCt.begin() + (blockIndex + 1) * blockSize);
            dict[probeBlock] = static_cast<uint8_t>(b);
        }

        auto it = dict.find(targetBlock);
        if (it != dict.end()) {
            recovered.push_back(it->second);
            ++total_bytes_found;
            if (total_bytes_found % 8 == 0) {
                std::cout << "[PROGRESS] bytes recovered: " << total_bytes_found << "\n";
            }
        } else {
            // no encontrado → final del secreto
            break;
        }
    }

    // Intentar unpad PKCS#7 si existe
    try {
        auto unpadded = pkcs7Unpad(recovered); // devuelve vector<uint8_t>
        return std::string(unpadded.begin(), unpadded.end());
    } catch (const std::exception& e) {
        // si el unpad falla, devolver lo recuperado como texto lo mejor posible
        std::cerr << "Warning: pkcs7Unpad falló: " << e.what() << ". Devolviendo bruto.\n";
        return std::string(recovered.begin(), recovered.end());
    }
}

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <iomanip>
#include <stdexcept>
#include "cbc.hpp"
#include "base64.hpp"
#include "pkcs7.hpp"
#include <openssl/evp.h>


int main() {
    // Abrir archivo
    std::ifstream file("../data/10.txt");
    if (!file.is_open()) {
        std::cerr << "❌ Error: no se pudo abrir el archivo 10.txt\n";
        return 1;
    }

    // Leer contenido Base64
    std::string base64Data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    if (base64Data.empty()) {
        std::cerr << "❌ Error: el archivo está vacío o no se leyó correctamente\n";
        return 1;
    }

    // Decodificar Base64
    std::vector<uint8_t> ciphertext;
    try {
        ciphertext = base64Decode(base64Data);
        if (ciphertext.empty()) {
            std::cerr << "❌ Error: el resultado de base64Decode está vacío\n";
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "❌ Error al decodificar Base64: " << e.what() << "\n";
        return 1;
    }

    // Verificar tamaño del ciphertext
    if (ciphertext.size() % 16 != 0) {
        std::cerr << "❌ Error: el tamaño del ciphertext no es múltiplo de 16\n";
        return 1;
    }

    // Clave y IV
    std::string key = "YELLOW SUBMARINE";
    std::vector<uint8_t> iv(16, 0x00);  // IV de ceros

    // Descifrar CBC
    std::vector<uint8_t> plaintext;
    try {
        plaintext = aesCBCDecrypt(ciphertext, key, iv);
        if (plaintext.empty()) {
            std::cerr << "❌ Error: el texto descifrado está vacío\n";
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "❌ Error al descifrar CBC: " << e.what() << "\n";
        return 1;
    }

    // Mostrar resultado
    std::cout << "\n✅ Texto descifrado:\n";
    for (uint8_t byte : plaintext) {
        std::cout << static_cast<char>(byte);
    }
    std::cout << std::endl;

    return 0;
}

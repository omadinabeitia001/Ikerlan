#include <iostream>
#include "cbc_bitflip.hpp"
#include "pkcs7_val.hpp"


int main() {
    std::string input = "XXXXXXXXXXXXXX"; // 16 bytes para controlar el bloque
    auto ciphertext = cbcEncryptProfile(input);

    auto hacked = performBitflipAttack(ciphertext);

    bool success = cbcDecryptAndCheck(hacked);
    std::cout << (success ? "✅ Admin acceso concedido" : "❌ Acceso denegado") << std::endl;

    return 0;
}

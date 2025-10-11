#include <iostream>
#include "cbc_bitflip.hpp"
#include "pkcs7_val.hpp"


int main() {
    // Este userdata produce, en el bloque objetivo, ":admin<true:AAAA"
    // Los primeros 12 bytes serán ":admin<true:" que luego fliparemos a ";admin=true;"
    std::string input = "XXXXXXXXXXXXXX"; 
    auto ciphertext = cbcEncryptProfile(input);

    auto hacked = performBitflipAttack(ciphertext);

    bool success = cbcDecryptAndCheck(hacked);
    std::cout << (success ? "✅ Admin acceso concedido" : "❌ Acceso denegado") << std::endl;

    return 0;
}

#include <iostream>
#include "ecb_cut.hpp"

int main() {
    std::string key = "YELLOW SUBMARINE";

    std::string email = "foooooooo@bar.com"; // Alineado para que role= esté en bloque 3
    std::string profile = profile_for(email);
    auto encrypted = encryptProfile(profile, key);
    std::string decrypted = decryptProfile(encrypted, key);

    std::cout << " Perfil cifrado: " << profile << "\n";
    std::cout << " Perfil descifrado: " << decrypted << "\n";

    std::string forged = generateAdminProfile(key);
    std::cout << "\n Perfil forjado con role=admin:\n" << forged << "\n";

    return 0;
}

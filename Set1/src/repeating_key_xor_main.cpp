#include <iostream>
#include "repeating_key_xor.hpp"

int main() {
    std::string text =
        "Burning 'em, if you ain't quick and nimble\n"
        "I go crazy when I hear a cymbal";
    std::string key = "ICE";

    std::string encrypted = repeatingKeyXOR(text, key);
    std::cout << "Enkriptatua: " << encrypted << std::endl;

    return 0;
}

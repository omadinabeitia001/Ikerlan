#include "hex_to_base64.hpp"
#include <iostream>

int main() {
    std::string input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    auto bytes = hexToBytes(input);
    std::cout << bytesToBase64(bytes) << std::endl;
}

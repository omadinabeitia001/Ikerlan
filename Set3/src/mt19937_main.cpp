#include <iostream>
#include "mt19937.hpp"

int main() {
    MT19937 rng(5489); // Semilla por defecto del paper original

    for (int i = 0; i < 10; ++i) {
        std::cout << rng.extract_number() << std::endl;
    }

    return 0;
}

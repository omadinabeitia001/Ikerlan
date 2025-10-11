#include <iostream>
#include "mt_clone.hpp"

// Si compilas untemper.cpp como fuente aparte en CMake, no lo incluyas aquí.
// #include "untemper.cpp"
uint32_t untemper(uint32_t); // declaración para usar la función

int main() {
    MTClone original; // constructor por defecto usa semilla 5489

    std::array<uint32_t, 624> outputs;
    for (int i = 0; i < 624; i++) {
        outputs[i] = original.extract_number();
    }

    std::array<uint32_t, 624> state;
    for (int i = 0; i < 624; i++) {
        state[i] = untemper(outputs[i]);
    }

    MTClone clone;
    clone.set_state(state);

    for (int i = 0; i < 10; i++) {
        uint32_t orig_val = original.extract_number();
        uint32_t clone_val = clone.extract_number();
        std::cout << "Original: " << orig_val << " | Clone: " << clone_val
                  << (orig_val == clone_val ? " ✅" : " ❌") << "\n";
    }

    return 0;
}

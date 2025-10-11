#include <gtest/gtest.h>
#include "mt19937.hpp"
#include "untemper.hpp"

TEST(MTCloneTest, ProducesSameSequenceAfterCloning) {
    MT19937 original(4321);

    std::vector<uint32_t> outputs;
    for (int i = 0; i < 624; ++i) {
        outputs.push_back(original.extract_number());
    }

    std::vector<uint32_t> state;
    for (uint32_t y : outputs) {
        state.push_back(untemper(y));
    }

    MT19937 clone(0);
    clone.set_state(state);

    // Ahora ambos deben dar la misma secuencia
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(original.extract_number(), clone.extract_number());
    }
}

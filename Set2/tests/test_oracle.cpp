#include <gtest/gtest.h>
#include "oracle.hpp"

TEST(OracleDetectionTest, DetectsECBvsCBC) {
    srand(time(nullptr)); // Semilla aleatoria

    std::vector<uint8_t> input(64, 'A'); // Bloques repetidos

    int correctDetections = 0;
    int totalTests = 20;

    for (int i = 0; i < totalTests; ++i) {
        auto [ciphertext, actualMode] = test_encryption_oracle(input);
        std::string detectedMode = detectEncryptionMode(ciphertext);

        if (detectedMode == actualMode) {
            ++correctDetections;
        }
    }

    std::cout << "✅ Detecciones correctas: " << correctDetections << " de " << totalTests << "\n";
    ASSERT_GT(correctDetections, totalTests * 0.8); // Al menos 80% de aciertos
}

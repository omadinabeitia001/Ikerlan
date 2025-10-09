#include "detect_single_byte_xor.hpp"
#include <vector>  // ← necesario para std::vector

DetectionResult detectSingleByteXOR(const std::vector<std::string>& lines) {
    double bestScore = -1.0;
    DetectionResult bestResult;

    for (const auto& line : lines) {
        auto result = breakSingleByteXOR(line);
        double score = scoreEnglish(result.plaintext);
        if (score > bestScore) {
            bestScore = score;
            // bestResult = {line, result.key, result.plaintext}; ← esto da error si no tienes constructor
            bestResult.original_hex = line;
            bestResult.key = result.key;
            bestResult.plaintext = result.plaintext;
        }
    }

    return bestResult;
}

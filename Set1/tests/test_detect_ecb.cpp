#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>

int countRepeatedBlocks(const std::string& hexLine);

TEST(DetectECBTest, FindsECBEncryptedLine) {
    std::ifstream file("../data/8.txt");
    ASSERT_TRUE(file.is_open());

    std::string line;
    int maxRepeats = 0;
    std::string ecbCandidate;

    while (std::getline(file, line)) {
        int repeats = countRepeatedBlocks(line);
        if (repeats > maxRepeats) {
            maxRepeats = repeats;
            ecbCandidate = line;
        }
    }

    EXPECT_GT(maxRepeats, 0);
    EXPECT_FALSE(ecbCandidate.empty());
}

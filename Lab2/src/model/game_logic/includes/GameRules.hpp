#pragma once

#include <bitset>
#include <vector>

using Point = struct Point {
    int x;
    int y;
};

class GameRules {
private:
    std::bitset<8> m_cellForBirth;
    std::bitset<8> m_cellForSurvive;

public:
    GameRules();
    GameRules(std::bitset<8> cellForBirth, std::bitset<8> cellForSurive);
    ~GameRules();
    std::bitset<8> GetRuleAboutBirth() const;
    std::bitset<8> GetRuleAboutSurvive() const;
};

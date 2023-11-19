#include "../includes/GameRules.hpp"

GameRules::GameRules() : m_cellForBirth{0b00000101}, m_cellForSurvive{0b00000101} {}
GameRules::GameRules(std::bitset<8> cellForBirth,
                     std::bitset<8> cellForSurive)
    : m_cellForBirth{cellForBirth}, m_cellForSurvive{cellForSurive} {
}

GameRules::~GameRules() {}

std::bitset<8> GameRules::GetRuleAboutBirth() const { return m_cellForBirth; }
std::bitset<8> GameRules::GetRuleAboutSurvive() const {
    return m_cellForSurvive;
}

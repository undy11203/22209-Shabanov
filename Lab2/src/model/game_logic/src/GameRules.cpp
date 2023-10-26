#include "../includes/GameRules.hpp"

GameRules::GameRules() : m_cellForBirth{1, 3}, m_cellForSurvive{1, 3} {}
GameRules::GameRules(std::vector<int> cellForBirth,
                     std::vector<int> cellForSurive)
    : m_cellForBirth{cellForBirth}, m_cellForSurvive{cellForSurive} {
}

GameRules::~GameRules() {}

std::vector<int> GameRules::GetRuleAboutBirth() const { return m_cellForBirth; }
std::vector<int> GameRules::GetRuleAboutSurvive() const {
    return m_cellForSurvive;
}
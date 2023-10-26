#include "GameModel.hpp"

#include <utility>

GameModel::GameModel() : m_board{}, m_rules{} {}

GameModel::GameModel(std::vector<std::pair<int, int>> alive,
                     std::pair<int, int> size,
                     std::pair<std::vector<int>, std::vector<int>> rules,
                     std::string name)
    : m_board{alive, size.first, size.second},
      m_rules(rules.first, rules.second),
      m_name{name} {}

std::vector<std::vector<bool>> GameModel::GetMap() {
    return m_board.GetField();
}

void GameModel::Update() {
    m_board.Evolve(m_rules);
}

std::string GameModel::GetName() { return m_name; }

std::pair<std::vector<int>, std::vector<int>> GameModel::GetRules() {
    return std::pair<std::vector<int>, std::vector<int>>(
        m_rules.GetRuleAboutBirth(), m_rules.GetRuleAboutSurvive());
}

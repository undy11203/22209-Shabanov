#include "GameModel.hpp"

#include <iostream>
#include <utility>

GameModel::GameModel() : m_board{}, m_rules{}, m_type{"online"} {}

GameModel::GameModel(std::vector<std::pair<int, int>> alive, std::pair<int, int> size,
           std::pair<std::vector<int>, std::vector<int>> rules, std::string type, std::string name)
    : m_board{alive, size.first, size.second},
      m_rules(rules.first, rules.second), m_type{type}, m_name{name} {
      }

std::vector<std::vector<bool>> GameModel::GetMap() {
  return m_board.GetField();
}

void GameModel::Update() {
    try
    {
        m_board.Evolve(m_rules);
    }
    catch(const std::exception& e)
    {
        std::cout << e.what();
    }
}

std::string GameModel::GetName() {
  return m_name;
}

std::pair<std::vector<int>, std::vector<int>> GameModel::GetRules() {
  return std::pair<std::vector<int>, std::vector<int>>(m_rules.GetRuleAboutBirth(), m_rules.GetRuleAboutSurvive());
}

std::string GameModel::GetType() {
  return m_type;
}

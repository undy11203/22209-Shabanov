#pragma once

#include "includes/GameRules.hpp"
#include "includes/GameBoard.hpp"

#include <string>
#include <utility>

class GameModel {
private:
  GameBoard m_board;
  GameRules m_rules;
  std::string m_name;

public:
  GameModel();
  GameModel(std::vector<std::pair<int, int>> alive, std::pair<int, int> size,
       std::pair<std::vector<int>, std::vector<int>> rules, std::string name);
  ~GameModel() = default;
  void Update();
  std::string GetName();
  std::pair<std::vector<int>, std::vector<int>> GetRules();
  std::vector<std::vector<bool>> GetMap();
};

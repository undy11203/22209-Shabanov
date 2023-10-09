#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include "includes/GameRules.hpp"
#include "includes/GameBoard.hpp"

#include <string>
#include <utility>

class GameModel {
private:
  GameBoard m_board;
  GameRules m_rules;
  std::string m_type;
  std::string m_name;

public:
  GameModel();
  GameModel(std::vector<std::pair<int, int>> alive, std::pair<int, int> size,
       std::pair<std::vector<int>, std::vector<int>> rules, std::string type, std::string name);
  ~GameModel() = default;
  void Update();
  std::string GetName();
  std::pair<std::vector<int>, std::vector<int>> GetRules();
  std::string GetType();
  std::vector<std::vector<bool>> GetMap();
};


#endif
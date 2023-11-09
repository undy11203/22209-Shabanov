#pragma once

#include "includes/GameBoard.hpp"
#include "includes/GameRules.hpp"


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
              std::pair<std::bitset<8>, std::bitset<8>> rules, std::string name);
    ~GameModel() = default;
    void Update();
    std::string GetName();
    std::pair<std::bitset<8>, std::bitset<8>> GetRules();
    std::vector<std::vector<bool>> GetMap();
};

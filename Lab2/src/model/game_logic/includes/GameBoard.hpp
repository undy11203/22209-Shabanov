#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>

#include "Cell.hpp"
#include "GameRules.hpp"

class GameBoard {
private:
  std::vector<std::vector<Cell>> m_field;
  int m_width;
  int m_height;

public:
  GameBoard();
  GameBoard(std::vector<std::pair<int, int>> alive, int width, int height);
  ~GameBoard();
  void Evolve(const GameRules& rules);
  std::vector<std::vector<bool>> GetField();
};

#endif
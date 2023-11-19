#pragma once

#include <vector>

#include "GameRules.hpp"

class GameBoard {
private:
    enum StateCell {
        Dead,
        Alive
    };

    std::vector<StateCell> m_field;
    int m_width;
    int m_height;

public:
    GameBoard();
    GameBoard(std::vector<Point> aliveCells, int width, int height);
    ~GameBoard();
    std::vector<std::vector<bool>> GetField();
    int GetHeight();
    int GetWidth();
    bool GetState(int x, int y);
    void SetState(int x, int y);
};

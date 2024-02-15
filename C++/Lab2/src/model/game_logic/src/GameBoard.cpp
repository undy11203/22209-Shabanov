#include "../includes/GameBoard.hpp"

namespace {
    int mod(int a, int b) { return (a % b + b) % b; }
} // namespace

GameBoard::GameBoard() : m_width{3}, m_height{5} {
    m_field =
        std::vector<StateCell>(m_width * m_height);
}

GameBoard::GameBoard(std::vector<Point> aliveCells, int width,
                     int height)
    : m_width{width}, m_height{height} {
    m_field =
        std::vector<StateCell>(m_width * m_height);
    for (const auto &cell : aliveCells) {
        m_field[cell.x * m_width + cell.y] = Alive;
    }
}

GameBoard::~GameBoard() {}

int GameBoard::GetHeight() {
    return m_height;
}
int GameBoard::GetWidth() {
    return m_width;
}

bool GameBoard::GetState(int x, int y) {
    return m_field[mod(x, m_width) * m_width + mod(y, m_height)];
}

void GameBoard::SetState(int x, int y) {
    m_field[mod(x, m_width) * m_width + mod(y, m_height)] = (m_field[mod(x, m_width) * m_width + mod(y, m_height)] == Dead ? Alive : Dead);
}

std::vector<std::vector<bool>> GameBoard::GetField() {
    std::vector<std::vector<bool>> map(m_width, std::vector<bool>(m_height));
    for (size_t i = 0; i < m_width; i++) {
        for (size_t j = 0; j < m_height; j++) {
            map[i][j] = m_field[i * m_width + j];
        }
    }
    return map;
}
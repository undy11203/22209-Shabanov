#include "../includes/GameBoard.hpp"

namespace {
    int mod(int a, int b) { return (a % b + b) % b; }
} // namespace

GameBoard::GameBoard() : m_width{3}, m_height{5} {
    m_field =
        std::vector<std::vector<Cell>>(m_width, std::vector<Cell>(m_height));
}

GameBoard::GameBoard(std::vector<std::pair<int, int>> alive, int width,
                     int height)
    : m_width{width}, m_height{height} {
    m_field =
        std::vector<std::vector<Cell>>(m_width, std::vector<Cell>(m_height));
    for (const auto &cell : alive) {
        m_field[cell.first][cell.second].ChangeState();
    }
}

GameBoard::~GameBoard() {}

void GameBoard::Evolve(const GameRules &rules) {
    for (int x = 0; x < m_width; x++) {
        for (int y = 0; y < m_height; y++) {
            if (m_field[x][y].GetState() == true) {
                int countForSurvive = 0;
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (j == 0 && i == 0)
                            continue;
                        countForSurvive =
                            m_field[mod(x + i, m_width)][mod(y + j, m_height)]
                                        .GetState() == true
                                ? countForSurvive + 1
                                : countForSurvive;
                    }
                }
                for (const auto &survive : rules.GetRuleAboutSurvive()) {
                    if (countForSurvive == survive) {
                        m_field[x][y].RequestToChange();
                        break;
                    }
                }
                m_field[x][y].RequestToChange();
            } else {
                int countForBirth = 0;
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (j == 0 && i == 0)
                            continue;
                        countForBirth =
                            m_field[mod(x + i, m_width)][mod(y + j, m_height)]
                                        .GetState() == true
                                ? countForBirth + 1
                                : countForBirth;
                    }
                }
                for (const auto &birth : rules.GetRuleAboutBirth()) {
                    if (countForBirth == birth) {
                        m_field[x][y].RequestToChange();
                        break;
                    }
                }
            }
        }
    }

    for (int x = 0; x < m_width; x++) {
        for (int y = 0; y < m_height; y++) {
            if (m_field[x][y].ExistedRequest())
                m_field[x][y].ChangeState();
        }
    }
}

std::vector<std::vector<bool>> GameBoard::GetField() {
    std::vector<std::vector<bool>> map(m_width, std::vector<bool>(m_height));
    for (size_t i = 0; i < m_width; i++) {
        for (size_t j = 0; j < m_height; j++) {
            map[i][j] = m_field[i][j].GetState();
        }
    }
    return map;
}

#include "GameModel.hpp"

#include <iostream>
#include <utility>

namespace {
    int mod(int a, int b) { return (a % b + b) % b; }
} // namespace

GameModel::GameModel() : m_board{}, m_rules{} {}

GameModel::GameModel(std::vector<std::pair<int, int>> alive,
                     std::pair<int, int> size,
                     std::pair<std::bitset<8>, std::bitset<8>> rules,
                     std::string name)
    : m_rules(rules.first, rules.second),
      m_name{name} {
    std::vector<Point> aliveCells;
    for (const auto &cell : alive) {
        aliveCells.push_back(Point{.x = cell.first, .y = cell.second});
    }
    m_board = GameBoard(aliveCells, size.first, size.second);
}

std::vector<std::vector<bool>> GameModel::GetMap() {
    return m_board.GetField();
}

void GameModel::Update() {
    int width = m_board.GetWidth();
    int height = m_board.GetHeight();
    for (size_t x = 0; x < width; x++) {
        for (size_t y = 0; y < height; y++) {
            if (m_board.GetState(x, y) == true) {
                int countForSurvive = 0;
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (j == 0 && i == 0)
                            continue;
                        countForSurvive = m_board.GetState(mod(x + i, width), mod(y + j, height)) == true
                                              ? countForSurvive + 1
                                              : countForSurvive;
                    }
                }

                std::bitset<8> survive = m_rules.GetRuleAboutSurvive();
                for (int i = 0; i < survive.size(); i++) {
                    if (survive.test(i) && countForSurvive == i + 1) {
                        std::cout << "X: " << x << " Y: " << y << " " << m_board.GetState(x, y);
                        m_board.SetState(x, y);
                        std::cout << m_board.GetState(x, y);
                        break;
                    }
                }
                std::cout << m_board.GetState(x, y);
                m_board.SetState(x, y);
                std::cout << m_board.GetState(x, y) << std::endl;
            } else {
                int countForBirth = 0;
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (j == 0 && i == 0)
                            continue;
                        countForBirth =
                            m_board.GetState(mod(x + i, width), mod(y + j, height)) == true
                                ? countForBirth + 1
                                : countForBirth;
                    }
                }
                std::bitset<8> birth = m_rules.GetRuleAboutBirth();
                for (int i = 0; i < birth.size(); i++) {
                    if (birth.test(i) && countForBirth == i + 1) {
                        m_board.SetState(x, y);
                        break;
                    }
                }
            }
        }
    }

    m_board.SwapField();
}

std::string GameModel::GetName() { return m_name; }

std::pair<std::bitset<8>, std::bitset<8>> GameModel::GetRules() {
    return std::pair<std::bitset<8>, std::bitset<8>>(
        m_rules.GetRuleAboutBirth(), m_rules.GetRuleAboutSurvive());
}

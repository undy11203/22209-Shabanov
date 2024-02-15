#include "GameModel.hpp"

#include <utility>

GameModel::GameModel() : m_board1{}, m_board2{}, m_rules{} {}

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
    m_board1 = GameBoard(aliveCells, size.first, size.second);
    m_board2 = m_board1;
}

std::vector<std::vector<bool>> GameModel::GetMap() {
    return m_board1.GetField();
}

void GameModel::Update() {
    int width = m_board1.GetWidth();
    int height = m_board1.GetHeight();
    for (size_t x = 0; x < width; x++) {
        for (size_t y = 0; y < height; y++) {
            if (m_board1.GetState(x, y) == true) {
                int countForSurvive = 0;
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (j == 0 && i == 0)
                            continue;
                        countForSurvive = m_board1.GetState(x + i, y + j) == true
                                              ? countForSurvive + 1
                                              : countForSurvive;
                    }
                }

                std::bitset<8> survive = m_rules.GetRuleAboutSurvive();
                for (int i = 0; i < survive.size(); i++) {
                    if (survive.test(i) && countForSurvive == i + 1) {
                        m_board2.SetState(x, y);
                        break;
                    }
                }
                m_board2.SetState(x, y);
            } else {
                int countForBirth = 0;
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (j == 0 && i == 0)
                            continue;
                        countForBirth =
                            m_board1.GetState(x + i, y + j) == true
                                ? countForBirth + 1
                                : countForBirth;
                    }
                }
                std::bitset<8> birth = m_rules.GetRuleAboutBirth();
                for (int i = 0; i < birth.size(); i++) {
                    if (birth.test(i) && countForBirth == i + 1) {
                        m_board2.SetState(x, y);
                        break;
                    }
                }
            }
        }
    }

    m_board1 = m_board2;
}

std::string GameModel::GetName() { return m_name; }

std::pair<std::bitset<8>, std::bitset<8>> GameModel::GetRules() {
    return std::pair<std::bitset<8>, std::bitset<8>>(
        m_rules.GetRuleAboutBirth(), m_rules.GetRuleAboutSurvive());
}

#include <GameModel.hpp>
#include <includes/GameBoard.hpp>
#include <includes/GameRules.hpp>

#include <gtest/gtest.h>

#include <bitset>

TEST(Rule, RuleTest) {
    GameRules rules1{};
    EXPECT_EQ(rules1.GetRuleAboutBirth(), 0b00000101);
    GameRules rules2(std::bitset<8>(10), std::bitset<8>(7));
    EXPECT_EQ(rules2.GetRuleAboutBirth(), 0b00001010);
    EXPECT_EQ(rules2.GetRuleAboutSurvive(), 0b00000111);
}

TEST(Board, BoardTest) {
    GameBoard board1;
    EXPECT_EQ(board1.GetHeight(), 5);
    EXPECT_EQ(board1.GetWidth(), 3);

    std::vector<Point> points{{1, 1}, {1, 2}, {1, 3}, {2, 2}};
    GameBoard board2(points, 4, 4);
    std::vector<std::vector<bool>> map = {
        {false, false, false, false},
        {false, true, true, true},
        {false, false, true, false},
        {false, false, false, false},
    };
    EXPECT_EQ(board2.GetField(), map);

    board2.SetState(0, 0);
    EXPECT_FALSE(board2.GetState(0, 0));

    board2.SwapField();
    EXPECT_TRUE(board2.GetState(0, 0));
}

TEST(GameModel, GameModelTest) {
    GameModel model1;

    std::vector<std::pair<int, int>> alive = {{1, 1},
                                              {1, 2},
                                              {1, 3},
                                              {2, 2}};
    GameModel model2(alive, std::pair<int, int>(4, 4), std::pair<std::bitset<8>, std::bitset<8>>(std::bitset<8>(4), std::bitset<8>(6)), "Name");

    EXPECT_EQ(model2.GetName(), "Name");
    EXPECT_EQ(model2.GetRules().first, 4);
    EXPECT_EQ(model2.GetRules().second, 6);

    std::vector<std::vector<bool>> map = {
        {false, false, false, false},
        {false, true, true, true},
        {false, false, true, false},
        {false, false, false, false},
    };
    EXPECT_EQ(model2.GetMap(), map);

    model2.Update();
    map = {
        {false, false, true, false},
        {false, true, true, true},
        {false, true, true, true},
        {false, false, false, false},
    };
    EXPECT_EQ(model2.GetMap(), map);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
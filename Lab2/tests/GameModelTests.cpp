#include <GameModel.hpp>
#include <includes/Cell.hpp>
#include <includes/GameBoard.hpp>
#include <includes/GameRules.hpp>

#include <gtest/gtest.h>

TEST(Cell, CellTest) {
    Cell cell1;
    Cell cell2(false);
    Cell cell3(true);

    EXPECT_FALSE(cell2.GetState());
    EXPECT_TRUE(cell3.GetState());

    cell2.ChangeState();
    cell3.ChangeState();
    EXPECT_TRUE(cell2.GetState());
    EXPECT_FALSE(cell3.GetState());

    EXPECT_FALSE(cell2.ExistedRequest());
    cell2.RequestToChange();
    EXPECT_TRUE(cell2.ExistedRequest());
}

TEST(Rule, RuleTest) {
    GameRules rules1{};
    std::vector<int> vect = {1, 3};
    EXPECT_EQ(rules1.GetRuleAboutBirth(), vect);
    vect = {1, 2, 3};
    GameRules rules2({1, 2, 3}, {1, 2, 3});
    EXPECT_EQ(rules2.GetRuleAboutBirth(), vect);
    EXPECT_EQ(rules2.GetRuleAboutBirth(), vect);
}

TEST(Board, BoardTest) {
    GameRules rules2 = {{3}, {2, 3}};

    GameBoard board1;
    std::vector<std::pair<int, int>> vect = {{1, 1}, {1, 2}, {2, 2}, {1, 3}};
    GameBoard board2(vect, 4, 4);

    std::vector<std::vector<bool>> map = {{false, false, false, false},
                                          {false, true, true, true},
                                          {false, false, true, false},
                                          {false, false, false, false}};
    EXPECT_EQ(board2.GetField(), map);
    board2.Evolve(rules2);
    map = {{false, false, true, false},
           {false, true, true, true},
           {false, true, true, true},
           {false, false, false, false}};
    EXPECT_EQ(board2.GetField(), map);
}

TEST(GameModel, GameModelTest) {
    GameModel model1;
    GameModel model2{{{1, 1}, {1, 2}, {2, 2}, {1, 3}}, {4, 4}, {{3}, {2, 3}}, "Name"};
    std::vector<std::vector<bool>> map = {{false, false, false, false},
                                          {false, true, true, true},
                                          {false, false, true, false},
                                          {false, false, false, false}};
    std::pair<std::vector<int>, std::vector<int>> rules = {{3}, {2, 3}};
    EXPECT_EQ(model2.GetMap(), map);
    EXPECT_EQ(model2.GetName(), "Name");
    EXPECT_EQ(model2.GetRules(), rules);

    model2.Update();
    map = {{false, false, true, false},
           {false, true, true, true},
           {false, true, true, true},
           {false, false, false, false}};
    EXPECT_EQ(model2.GetMap(), map);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
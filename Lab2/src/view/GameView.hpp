#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <utility>
#include <string>
#include <vector>

class GameView
{
public:
    GameView() = default;
    ~GameView() = default;
    std::pair<std::string, std::string> GetInput();
    void Clear();
    void PrintInfo(std::string name, std::pair<std::vector<int>, std::vector<int>> rules, std::string typeGame);
    void PrintMap(std::vector<std::vector<bool>> map);
    void PrintSuccessMessage();
    void PrintHelp();
    void GetReturnCommand();
};

#endif
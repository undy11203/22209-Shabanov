#pragma once

#include <utility>
#include <string>
#include <vector>

class ConsoleView
{
public:
    ConsoleView() = default;
    ~ConsoleView() = default;
    std::pair<std::string, std::string> GetInput();
    void Clear();
    void PrintInfo(std::string name, std::pair<std::vector<int>, std::vector<int>> rules);
    void PrintMap(std::vector<std::vector<bool>> map);
    void PrintCompletedMessage(std::string message);
    void PrintHelp();
    void PrintReturnCommand();
    void PrintErrorCommand(std::string command);
    void PrintError(std::string error);
    void Sleep(int i);
};

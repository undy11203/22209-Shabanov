#pragma once

#include <bitset>
#include <string>
#include <utility>
#include <vector>


class ConsoleView {
public:
    ConsoleView() = default;
    ~ConsoleView() = default;
    std::pair<std::string, std::string> GetInput();
    void Clear();
    void PrintInfo(std::string name, std::pair<std::bitset<8>, std::bitset<8>> rules);
    void PrintMap(std::vector<std::vector<bool>> map);
    void PrintCompletedMessage(std::string message);
    void PrintHelp();
    void PrintReturnCommand();
    void PrintErrorCommand(std::string command);
    void PrintError(std::string error);
    void Delay(int i);
};

#pragma once

#include <IView.hpp>

#include <bitset>
#include <string>
#include <utility>
#include <vector>

class ConsoleView : public IView {
public:
    void Update() override;
    void Render() override;
    std::pair<std::string, std::string> GetInput() override;
    void PrintInfo(std::string name,
                   std::pair<std::bitset<8>, std::bitset<8>> rules) override;
    void PrintMap(std::vector<std::vector<bool>> map) override;
    void PrintCompletedMessage(std::string message) override;
    void PrintError(std::string error) override;
    void PrintHelp() override;
    void PrintErrorCommand(std::string command) override;
    void PrintReturnCommand() override;
    bool PrintStop() override;
    void Delay(int i) override;
    int ShouldClose() override;
    bool IterationsCorrect(int number) override;
};

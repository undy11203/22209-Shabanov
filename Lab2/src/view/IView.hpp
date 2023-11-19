#pragma once

#include <bitset>
#include <string>
#include <utility>
#include <vector>

class IView {
public:
    virtual void Update() = 0;
    virtual void Render() = 0;
    std::pair<std::string, std::string> virtual GetInput() = 0;
    virtual void PrintInfo(std::string name,
                           std::pair<std::bitset<8>, std::bitset<8>> rules) = 0;
    virtual void PrintMap(std::vector<std::vector<bool>> map) = 0;
    virtual void PrintCompletedMessage(std::string message) = 0;
    virtual void PrintError(std::string error){};
    virtual void PrintHelp(){};
    virtual void PrintErrorCommand(std::string command){};
    virtual void PrintReturnCommand(){};
    virtual bool PrintStop() = 0;
    virtual void Delay(int i) = 0;
    virtual int ShouldClose() = 0;
    virtual bool IterationsCorrect(int number) = 0;
};

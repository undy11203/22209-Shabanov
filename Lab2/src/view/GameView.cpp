#include "GameView.hpp"

#include <iostream>
#include <sstream>

std::pair<std::string, std::string> GameView::GetInput() {
    std::cout << "If you don't know command, input help" << std::endl;
    std::cout << "Input command: ";
    
    std::string input;
    std::getline(std::cin, input);
    std::cout << std::endl;

    std::stringstream ss(input);
    std::string command;
    std::string value;
    ss >> command >> value;

    return std::pair<std::string, std::string>(command, value);
}

void GameView::Clear() {
    for (size_t i = 0; i < 200; i++)
    {
        std::cout << std::endl;
    }   
}

void GameView::PrintInfo(std::string name, std::pair<std::vector<int>, std::vector<int>> rules, std::string typeGame) {
    std::cout << "Name University: " << name << std::endl;
    std::cout << "Rules: B";
    for (size_t i = 0; i < rules.first.size(); i++)
    {
        std::cout << rules.first.at(i);
    }
    std::cout << " / S";
    for (size_t i = 0; i < rules.second.size(); i++)
    {
        std::cout << rules.second.at(i);
    }
    std::cout << std::endl;
    std::cout << "Type:" << typeGame << std::endl;
}

void GameView::PrintMap(std::vector<std::vector<bool>> map) {
    for (size_t i = 0; i < map[0].size()+1; i++) {
        std::cout << "--";
    }
    std::cout << std::endl;

    for (const auto& row : map)
    {
        std::cout << "|";
        for (const auto & cell : row)
        {
            std::cout << (cell == true ? "()" : "  ");
        }
        std::cout << "|";
        std::cout << std::endl;
    } 

    for (size_t i = 0; i < map[0].size()+1; i++) {
        std::cout << "--";
    }
    std::cout << std::endl;
}

void GameView::PrintSuccessMessage() {
    std::cout << "Success" << std::endl;
}

void GameView::PrintHelp() {
    std::cout << "   - dump <filename> - сохранить вселенную в файл"
              << std::endl
              << "   - tick <n=1> (и сокращенно t <n=1>) - рассчитать n (по "
                 "умолчанию 1) "
              << std::endl
              << "итераций и напечатать результат. На экране перед "
              << std::endl
              << "распечатанным полем должно отображаться имя вселенной, "
              << std::endl
              << "правило перехода и номер текущей итерации." << std::endl
              << "   - exit – завершить игру" << std::endl
              << "   - help – распечатать справку о командах" << std::endl;
}

void GameView::GetReturnCommand() {
    std::string input;
    std::cout << "Print enter or any button" << std::endl;
    std::cin >> input;
    std::cout << std::endl;
}
#include "ConsoleView.hpp"

#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>

int ConsoleView::ShouldClose() {
    return 0;
}

std::pair<std::string, std::string> ConsoleView::GetInput() {
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

void ConsoleView::PrintInfo(
    std::string name, std::pair<std::bitset<8>, std::bitset<8>> rules) {
    std::cout << "Name University: " << name << std::endl;
    std::cout << "Rules: B";
    for (size_t i = 0; i < rules.first.size(); i++) {
        std::cout << (rules.first.test(i) ? std::to_string(i + 1) : "");
    }
    std::cout << " / S";
    for (size_t i = 0; i < rules.second.size(); i++) {
        std::cout << (rules.second.test(i) ? std::to_string(i + 1) : "");
    }
    std::cout << std::endl;
}

void ConsoleView::PrintMap(std::vector<std::vector<bool>> map) {
    for (size_t i = 0; i < map[0].size() + 1; i++) {
        std::cout << "--";
    }
    std::cout << std::endl;

    for (const auto &row : map) {
        std::cout << "|";
        for (const auto &cell : row) {
            std::cout << (cell == true ? "()" : "  ");
        }
        std::cout << "|";
        std::cout << std::endl;
    }

    for (size_t i = 0; i < map[0].size() + 1; i++) {
        std::cout << "--";
    }
    std::cout << std::endl;
}

void ConsoleView::PrintCompletedMessage(std::string message) {
    std::cout << "Success! " << message << std::endl;
}

bool ConsoleView::IterationsCorrect(int number) {
    if (number > 0) {
        return true;
    }
    return false;
}

void ConsoleView::Render() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void ConsoleView::Delay(int i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(i));
}

bool ConsoleView::PrintStop() {
    return false;
}

void ConsoleView::Update() {
    for (size_t i = 0; i < 200; i++) {
        std::cout << std::endl;
    }
}

void ConsoleView::PrintHelp() {
    std::cout << "   - dump <filename> - save university in file" << std::endl
              << "   - tick <n=1> (t <n=1>) - make n iterations (default 1 "
                 "iteration) "
              << std::endl
              << "   - exit - exit this game" << std::endl
              << "   - help - list of commands" << std::endl;
}

void ConsoleView::PrintReturnCommand() {
    std::string input;
    std::cout << "Print enter or any button" << std::endl;
    std::getline(std::cin, input);
    std::cout << std::endl;
}

void ConsoleView::PrintErrorCommand(std::string command) {
    std::cout << "Uncorrect this command: \"" << command << "\"" << std::endl;
}

void ConsoleView::PrintError(std::string error) {
    std::cout << error << std::endl;
}
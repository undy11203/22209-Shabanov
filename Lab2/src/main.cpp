#include <iostream>
#include <string>
#include <vector>

#include "controller/GameController.hpp"
#include <config.hpp>

void ConfigGame(TypeView &typeView, TypeGame &typeGame, std::vector<std::string> &args) {
    typeView = Console;
    typeGame = Online;

    for (size_t i = 1; i < args.size(); i++) {
        if (args[i] == "-o" || args[i].find("--output") != std::string::npos) {
            typeGame = Offline;
        } else if (args[i] == "--gui") {
            typeView = Gui;
            args.erase(args.begin() + i);
        }
    }
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args(argv, argv + argc);

    TypeView typeView;
    TypeGame typeGame;

    ConfigGame(typeView, typeGame, args);

    GameController gameController(args);

    if (typeGame == Online) {
        gameController.RunApp(typeView);
    } else if (typeGame == Offline) {
        gameController.RunOfflineApp();
    }

    return 0;
}
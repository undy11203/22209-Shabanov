#include <string>
#include <vector>
#include <iostream>

#include <controller/GameController.hpp>

enum TypeView{
    Console,
    Gui
};
enum TypeGame {
    Offline,
    Online
};

void ConfigGame(TypeView& typeView, TypeGame& typeGame, std::vector<std::string>& args) {
    typeView = Console;
    typeGame = Online;

    for (size_t i = 1; i < args.size(); i++)
    {
        if (args[i] == "-o" || args[i].find("--output") != std::string::npos) {
            typeGame = Offline;
        } else if(args[i] == "--gui") {
            typeView = Gui;
            args.erase(args.begin()+i);
        }
    }      
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args(argv, argv + argc);

    TypeView typeView;
    TypeGame typeGame;

    ConfigGame(typeView, typeGame, args);

    GameController gameController(args);

    if(typeGame == Online && typeView == Gui){
        gameController.RunAppInImGui();
    }else if(typeGame == Online && typeView == Console) {
        gameController.RunAppInConsole();
    }else if(typeGame == Offline) {
        gameController.RunOfflineApp();
    }

    return 0;
}
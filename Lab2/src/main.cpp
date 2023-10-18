#include <string>
#include <vector>

#include <controller/GameController.hpp>

enum TypeView{
    Console,
    Gui
};
enum TypeGame {
    Offline,
    Online
};

void ConfigGame(TypeView& typeView, TypeGame& typeGame, int argc, std::vector<std::string> args) {
    typeView = Console;
    typeGame = Online;

    for (size_t i = 1; i < argc; i++)
    {
        if (args[i] == "-o" || args[i].find("--output") != std::string::npos) {
            typeGame = Offline;
        } else if(args[i] == "--gui") {
            typeView = Gui;
        }
    }
    
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args(argv, argv + argc);

    TypeView typeView;
    TypeGame typeGame;

    ConfigGame(typeView, typeGame, argc, args);

    GameController gameController(argc, args);

    if(typeGame == Online && typeView == Gui){
        gameController.RunAppInImGui();
    }else if(typeGame == Online && typeView == Console) {
        gameController.RunAppInConsole();
    }else if(typeGame == Offline) {
        gameController.RunOfflineApp();
    }

    return 0;
}
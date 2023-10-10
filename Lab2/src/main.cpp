#include <iostream>
#include <string>
#include <vector>

#include <view/console/ConsoleView.hpp>
#include <model/game_logic/GameModel.hpp>
#include <model/file/FileModel.hpp>
#include <controller/GameController.hpp>

void Init(FileModel& fileModel, int& iterations, GameModel& gameModel, int argc, std::vector<std::string> args) {
    std::string inputPath = "";
    std::string outputPath = "";
    for (int i = 1; i < argc; ++i) {
        if (args[i] == "-i") {
            if (i + 1 < argc) {
                iterations = std::stoi(args[i + 1]);
                i++;
            } else {
                std::cerr << "Ошибка: Ожидалось значение для -i" << std::endl;
            }
        } else if(args[i].find("--iterations") != std::string::npos) {
            iterations = stoi(args[i].substr(13));
        } else if (args[i] == "-o") {
            if (i + 1 < argc) {
                outputPath = args[i + 1];
                i++;
            } else {
                std::cerr << "Ошибка: Ожидалось значение для -o" << std::endl;
            }
        }else if(args[i].find("--output") != std::string::npos) {
            outputPath = args[i].substr(9);
        } else {
            inputPath = args[i];
        }
    }

    if(outputPath != ""){
        fileModel = FileModel(inputPath, outputPath);
        gameModel = GameModel(fileModel.GetAliveFromFile(), fileModel.GetSizeFromFile(), fileModel.GetRulesFromFile(), "offline", fileModel.GetNameUniveristyFromFile());
    }else {
        gameModel = GameModel(fileModel.GetAliveFromFile(), fileModel.GetSizeFromFile(), fileModel.GetRulesFromFile(), "online", fileModel.GetNameUniveristyFromFile());
    }
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args(argv, argv + argc);

    int iterators = 0;
    FileModel fileModel;
    GameModel gameModel;
    ConsoleView consoleView;
    Init(fileModel, iterators, gameModel, argc, args);

    GameController gameController(gameModel, consoleView, fileModel);

    if(gameModel.GetType() == "online") { //online
        while(true){
            if(gameController.RunApp()) break;
        }
    }else { //offline
        gameController.RunOfflineApp(iterators);
    }

    return 0;
}
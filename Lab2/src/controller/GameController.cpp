#include "GameController.hpp"

#include <bitset>
#include <cstring>
#include <memory>

#include <iostream>

#include <ConsoleView.hpp>
#include <IView.hpp>
#include <ImGuiView.hpp>

GameController::GameController(std::vector<std::string> &args) {
    std::string inputPath = "";
    std::string outputPath = "";

    std::unique_ptr<IView> view = std::make_unique<ConsoleView>();

    for (int i = 1; i < args.size(); ++i) {
        if (args[i] == "-i") {
            if (i + 1 < args.size()) {
                m_offlineIteratins = std::stoi(args[i + 1]);
                i++;
            } else {
                view->PrintError(
                    "Warning: no value after -i\nUsed default");
                view->Delay(500);
            }
        } else if (args[i].find("--iterations") != std::string::npos) {
            if (stoi(args[i].substr(13)) != std::string::npos) {
                m_offlineIteratins = stoi(args[i].substr(13));
            } else {
                view->PrintError(
                    "Warning: no value after --iterations\nUsed default");
                view->Delay(500);
            }
        } else if (args[i] == "-o") {
            if (i + 1 < args.size()) {
                if (m_fileModel.isFileExists(args[i + 1])) {
                    outputPath = args[i + 1];
                } else {
                    view->PrintError(
                        "Warning: path dont exists\nUsed default");
                    view->Delay(500);
                }
                i++;
            } else {
                view->PrintError(
                    "Warning: no value after -o\nUsed default");
                view->Delay(500);
            }
        } else if (args[i].find("--output") != std::string::npos) {
            if (stoi(args[i].substr(9)) != std::string::npos) {
                std::string path = args[i].substr(9);
                if (m_fileModel.isFileExists(path)) {
                    outputPath = path;
                } else {
                    view->PrintError(
                        "Warning: path dont exists\nUsed default");
                    view->Delay(500);
                }
            } else {
                view->PrintError(
                    "Warning: no value after --output\nUsed default");
                view->Delay(500);
            }
        } else {
            inputPath = args[i];
        }
    }

    m_fileModel = FileModel(inputPath, outputPath);
    std::pair<int, int> size = m_fileModel.GetSizeFromFile();
    std::pair<std::bitset<8>, std::bitset<8>> rules = m_fileModel.GetRulesFromFile();
    std::string name = m_fileModel.GetNameUniveristyFromFile();
    std::vector<std::string>
        noExistLine = m_fileModel.ErrorInPoint();
    if (!noExistLine.empty()) {
        for (size_t i = 0; i < noExistLine.size(); i++) {
            if (noExistLine[i] == "#N") {
                name = "Default name";
            } else if (noExistLine[i] == "#R") {
                rules = {0b00111111, 0b00111111};
            } else if (noExistLine[i] == "#S") {
                size = {100, 200};
            }
        }
    }

    m_gameModel =
        GameModel(m_fileModel.GetAliveFromFile(), size,
                  rules, name);

    std::string error = "";
    noExistLine = m_fileModel.ErrorInPoint();
    if (!noExistLine.empty()) {
        for (size_t i = 0; i < noExistLine.size(); i++) {
            error +=
                "Warning: error in point " + noExistLine[i] + "\n";
        }
    }
    if (error != "") {
        view->PrintError(error);
        view->Delay(500);
    }
}

void GameController::RunApp(TypeView type) {
    std::unique_ptr<IView> view;
    if (type == Console) {
        view = std::make_unique<ConsoleView>();
    } else if (type == Gui) {
        view = std::make_unique<ImGuiView>();
    }

    while (!view->ShouldClose()) {
        view->Update();
        view->PrintInfo(m_gameModel.GetName(), m_gameModel.GetRules());
        view->PrintMap(m_gameModel.GetMap());
        std::pair<std::string, std::string> command = view->GetInput();
        if (command.first == "dump") {
            m_fileModel.SaveToFile(m_gameModel.GetName(),
                                   m_gameModel.GetRules(),
                                   m_gameModel.GetMap());
            view->PrintCompletedMessage("Save complete!");
        } else if (command.first == "tick" || command.first == "t") {
            int ticks = 0;
            try {
                ticks = std::stoi(command.second);

            } catch (const std::exception &e) {
                view->PrintError(
                    "Warning: it is only positive integer");
            }

            for (int i = 0; ticks < 0 ? !view->ShouldClose() && view->IterationsCorrect(ticks) : i < ticks && !view->ShouldClose(); i++) {
                m_gameModel.Update();

                view->Update();
                view->PrintInfo(m_gameModel.GetName(),
                                m_gameModel.GetRules());
                view->PrintMap(m_gameModel.GetMap());
                if (view->PrintStop()) {
                    break;
                }
                view->Render();
            }
        } else if (command.first == "exit") {
            break;
        } else if (command.first == "help") {
            view->Update();
            view->PrintHelp();
            view->PrintReturnCommand();
        } else if (command.first != "\0") {
            view->Update();
            view->PrintErrorCommand(command.first);
            view->PrintHelp();
            view->PrintReturnCommand();
        }

        view->Render();
    }
}

void GameController::RunOfflineApp() {
    for (size_t i = 0; i < m_offlineIteratins; i++) {
        m_gameModel.Update();
    }
    m_fileModel.SaveToFile(m_gameModel.GetName(), m_gameModel.GetRules(),
                           m_gameModel.GetMap());
}
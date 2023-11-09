#include "GameController.hpp"

#include <bitset>
#include <cstring>

GameController::GameController(std::vector<std::string> &args)
    : m_consoleView{}, m_imGuiView{} {
    std::string inputPath = "";
    std::string outputPath = "";

    for (int i = 1; i < args.size(); ++i) {
        if (args[i] == "-i") {
            if (i + 1 < args.size()) {
                m_offlineIteratins = std::stoi(args[i + 1]);
                i++;
            } else {
                m_consoleView.PrintError(
                    "Warning: no value after -i\nUsed default");
                m_consoleView.Delay(500);
            }
        } else if (args[i].find("--iterations") != std::string::npos) {
            if (stoi(args[i].substr(13)) != std::string::npos) {
                m_offlineIteratins = stoi(args[i].substr(13));
            } else {
                m_consoleView.PrintError(
                    "Warning: no value after --iterations\nUsed default");
                m_consoleView.Delay(500);
            }
        } else if (args[i] == "-o") {
            if (i + 1 < args.size()) {
                if (m_fileModel.isFileExists(args[i + 1])) {
                    outputPath = args[i + 1];
                } else {
                    m_consoleView.PrintError(
                        "Warning: path dont exists\nUsed default");
                    m_consoleView.Delay(500);
                }
                i++;
            } else {
                m_consoleView.PrintError(
                    "Warning: no value after -o\nUsed default");
                m_consoleView.Delay(500);
            }
        } else if (args[i].find("--output") != std::string::npos) {
            if (stoi(args[i].substr(9)) != std::string::npos) {
                std::string path = args[i].substr(9);
                if (m_fileModel.isFileExists(path)) {
                    outputPath = path;
                } else {
                    m_consoleView.PrintError(
                        "Warning: path dont exists\nUsed default");
                    m_consoleView.Delay(500);
                }
            } else {
                m_consoleView.PrintError(
                    "Warning: no value after --output\nUsed default");
                m_consoleView.Delay(500);
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
        m_consoleView.PrintError(error);
        m_consoleView.Delay(500);
    }
}

void GameController::RunAppInConsole() {
    while (true) {
        m_consoleView.Clear();
        m_consoleView.PrintInfo(m_gameModel.GetName(), m_gameModel.GetRules());
        m_consoleView.PrintMap(m_gameModel.GetMap());
        std::pair<std::string, std::string> command = m_consoleView.GetInput();
        if (command.first == "dump") {
            m_fileModel.SaveToFile(m_gameModel.GetName(),
                                   m_gameModel.GetRules(),
                                   m_gameModel.GetMap());
        } else if (command.first == "tick" || command.first == "t") {
            int ticks = 1;
            try {
                ticks = std::stoi(command.second);

            } catch (const std::exception &e) {
                m_consoleView.PrintError(
                    "Warning: it is only positive integer");
            }
            for (int i = 0; i < ticks; i++) {
                m_gameModel.Update();

                m_consoleView.Clear();
                m_consoleView.PrintInfo(m_gameModel.GetName(),
                                        m_gameModel.GetRules());
                m_consoleView.PrintMap(m_gameModel.GetMap());
                m_consoleView.Delay(1000);
            }
        } else if (command.first == "exit") {
            break;
        } else if (command.first == "help") {
            m_consoleView.Clear();
            m_consoleView.PrintHelp();
            m_consoleView.PrintReturnCommand();
        } else {
            m_consoleView.Clear();
            m_consoleView.PrintErrorCommand(command.first);
            m_consoleView.PrintHelp();
            m_consoleView.PrintReturnCommand();
        }
    }
}

void GameController::RunAppInImGui() {
    m_imGuiView.Start();
    while (!m_imGuiView.ShouldClose()) {
        m_imGuiView.Update();
        m_imGuiView.PrintInfo(m_gameModel.GetName(), m_gameModel.GetRules());
        m_imGuiView.PrintMap(m_gameModel.GetMap());
        std::pair<bool, int> commands =
            m_imGuiView.PrintGetInputBar();
        if (commands.first == true) {
            m_fileModel.SaveToFile(m_gameModel.GetName(),
                                   m_gameModel.GetRules(),
                                   m_gameModel.GetMap());
            m_imGuiView.Render();
            m_imGuiView.PrintCompletedMessage("Save complete!");
        } else if (commands.second != -1 && commands.second != 0) {
            m_imGuiView.Render();
            for (size_t j = 0; j < commands.second &&
                               !m_imGuiView.ShouldClose();
                 j++) {
                m_gameModel.Update();

                m_imGuiView.Update();
                m_imGuiView.PrintInfo(m_gameModel.GetName(),
                                      m_gameModel.GetRules());
                m_imGuiView.PrintMap(m_gameModel.GetMap());
                if (m_imGuiView.PrintGetInputClose()) {
                    break;
                }
                m_imGuiView.Render();
                m_imGuiView.Delay(100);
            }
        } else if (commands.second == -1) {
            m_imGuiView.Render();
            while (!m_imGuiView.ShouldClose()) {
                m_gameModel.Update();

                m_imGuiView.Update();
                m_imGuiView.PrintInfo(m_gameModel.GetName(),
                                      m_gameModel.GetRules());
                m_imGuiView.PrintMap(m_gameModel.GetMap());
                if (m_imGuiView.PrintGetInputClose()) {
                    break;
                }
                m_imGuiView.Render();
                m_imGuiView.Delay(100);
            }
        }
        m_imGuiView.Render();
    }
}

void GameController::RunOfflineApp() {
    for (size_t i = 0; i < m_offlineIteratins; i++) {
        m_gameModel.Update();
    }
    m_fileModel.SaveToFile(m_gameModel.GetName(), m_gameModel.GetRules(),
                           m_gameModel.GetMap());
    m_consoleView.PrintCompletedMessage("Game save");
}
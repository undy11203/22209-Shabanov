#include "GameController.hpp"

#include <iostream>
#include <cstring>

GameController::GameController(std::vector<std::string>& args) : m_consoleView{}, m_imGuiView{} {
    std::string inputPath = "";
    std::string outputPath = "";

    for (int i = 1; i < args.size(); ++i) {
        if (args[i] == "-i") {
            if (i + 1 < args.size()) {
                m_offlineIteratins = std::stoi(args[i + 1]);
                i++;
            } else {
                m_consoleView.PrintError("Warning: no value after -i\nUsed default");
                m_consoleView.Delay(500);
            }
        } else if(args[i].find("--iterations") != std::string::npos) {
            if(stoi(args[i].substr(13)) != std::string::npos) {
                m_offlineIteratins = stoi(args[i].substr(13));
            }else {
                m_consoleView.PrintError("Warning: no value after --iterations\nUsed default");
                m_consoleView.Delay(500);
            }
        } else if (args[i] == "-o") {
            if (i + 1 < args.size()) {
                if (m_fileModel.isFileExists(args[i+1]))
                {
                    outputPath = args[i + 1];
                }else {
                    m_consoleView.PrintError("Warning: path dont exists\nUsed default");
                    m_consoleView.Delay(500);
                }
                i++;
            } else {
                m_consoleView.PrintError("Warning: no value after -o\nUsed default");
                m_consoleView.Delay(500);
            }
        }else if(args[i].find("--output") != std::string::npos) {
            if(stoi(args[i].substr(9)) != std::string::npos) {
                std::string path = args[i].substr(9);
                if (m_fileModel.isFileExists(path))
                {
                    outputPath = path;
                }else {
                    m_consoleView.PrintError("Warning: path dont exists\nUsed default");
                    m_consoleView.Delay(500);
                }
            }else {
                m_consoleView.PrintError("Warning: no value after --output\nUsed default");
                m_consoleView.Delay(500);
            }
        } else {
            inputPath = args[i];
        }
    }

    m_fileModel = FileModel(inputPath, outputPath);
    m_gameModel = GameModel(m_fileModel.GetAliveFromFile(), m_fileModel.GetSizeFromFile(), m_fileModel.GetRulesFromFile(), m_fileModel.GetNameUniveristyFromFile());
}

void GameController::RunAppInConsole() {
    while (true)
    {
        m_consoleView.Clear();
        m_consoleView.PrintInfo(m_gameModel.GetName(), m_gameModel.GetRules());
        m_consoleView.PrintMap(m_gameModel.GetMap());
        std::pair<std::string, std::string> command = m_consoleView.GetInput();
        if (command.first == "dump") {
            m_fileModel.SaveToFile(m_gameModel.GetMap());
        } else if (command.first == "tick" || command.first == "t") {
            int ticks = 1;
            try
            {
                ticks = std::stoi(command.second);

            }
            catch(const std::exception& e)
            {
                m_consoleView.PrintError("Ошибка: у данной команды аргумент целое положительное число");
            }
            for (int i = 0; i < ticks; i++) {
                m_gameModel.Update();
                
                m_consoleView.Clear();
                m_consoleView.PrintInfo(m_gameModel.GetName(), m_gameModel.GetRules());
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
    while (!m_imGuiView.ShouldClose())
    {
        m_imGuiView.Update();
        m_imGuiView.PrintInfo(m_gameModel.GetName(), m_gameModel.GetRules());
        m_imGuiView.PrintMap(m_gameModel.GetMap());
        std::vector<std::pair<std::string, std::string>> commandArray = m_imGuiView.PrintGetInputBar();
        for (size_t i = 0; i < commandArray.size(); i++)
        {
            if (commandArray[i].first == "dump")
            {
                m_fileModel.SaveToFile(m_gameModel.GetMap());
                m_imGuiView.PrintCompletedMessage("Save complete!");
            } else if(commandArray[i].first == "tick") {
                for (size_t j = 0; j < stoi(commandArray[i].second) && !m_imGuiView.ShouldClose(); j++)
                {
                    m_gameModel.Update();

                    m_imGuiView.Update();
                    m_imGuiView.PrintInfo(m_gameModel.GetName(), m_gameModel.GetRules());
                    m_imGuiView.PrintMap(m_gameModel.GetMap());
                    m_imGuiView.Render();
                    m_imGuiView.Delay(500);
                }
            }
        }
        m_imGuiView.Render();
    }
}

void GameController::RunOfflineApp() {
    for (size_t i = 0; i < m_offlineIteratins; i++)
    {
        m_gameModel.Update();
    }
    m_fileModel.SaveToFile(m_gameModel.GetMap());
    m_consoleView.PrintCompletedMessage("Game save");    
}
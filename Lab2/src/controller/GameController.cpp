#include <thread>
#include <chrono>

#include <iostream> 

#include "GameController.hpp"

GameController::GameController(GameModel &gameModel, ConsoleView &consoleView, FileModel& fileModel)
    : m_gameModel{gameModel}, m_consoleView{consoleView}, m_fileModel{fileModel} {}

bool GameController::RunApp() {
    m_consoleView.Clear();
    m_consoleView.PrintInfo(m_gameModel.GetName(), m_gameModel.GetRules(), m_gameModel.GetType());
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
        }
        for (int i = 0; i < ticks; i++) {
            m_consoleView.Clear();
            m_gameModel.Update();
            m_consoleView.PrintMap(m_gameModel.GetMap());
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } else if (command.first == "exit") {
        return true;
    } else if (command.first == "help") {
        m_consoleView.Clear();
        m_consoleView.PrintHelp();
        m_consoleView.GetReturnCommand();
    } else {
        m_consoleView.Clear();
        m_consoleView.PrintErrorCommand(command.first);
        m_consoleView.PrintHelp();
        m_consoleView.GetReturnCommand();
    }

    return false;
}

void GameController::RunOfflineApp(int iterators) {
    for (size_t i = 0; i < iterators; i++)
    {
        m_gameModel.Update();
    }
    m_fileModel.SaveToFile(m_gameModel.GetMap());
    m_consoleView.PrintSuccessMessage();    
}
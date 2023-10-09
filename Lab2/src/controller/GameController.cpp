#include <thread>
#include <chrono>

#include <iostream> 

#include "GameController.hpp"

GameController::GameController(GameModel &gameModel, GameView &gameView, FileModel& fileModel)
    : m_gameModel{gameModel}, m_gameView{gameView}, m_fileModel{fileModel} {}

bool GameController::RunApp() {
    m_gameView.Clear();
    m_gameView.PrintInfo(m_gameModel.GetName(), m_gameModel.GetRules(), m_gameModel.GetType());
    m_gameView.PrintMap(m_gameModel.GetMap());
    std::pair<std::string, std::string> command = m_gameView.GetInput();
    if (command.first == "dump") {
        m_fileModel.SaveToFile(m_gameModel.GetMap());
    } else if (command.first == "tick") {
        int ticks = std::stoi(command.second);
        for (int i = 0; i < ticks; i++) {
            m_gameView.Clear();
            m_gameModel.Update();
            m_gameView.PrintMap(m_gameModel.GetMap());
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } else if (command.first == "exit") {
        return true;
    } else if (command.first == "help") {
        m_gameView.Clear();
        m_gameView.PrintHelp();
        m_gameView.GetReturnCommand();
    }

    return false;
}

void GameController::RunOfflineApp(int iterators) {
    for (size_t i = 0; i < iterators; i++)
    {
        m_gameModel.Update();
    }
    m_fileModel.SaveToFile(m_gameModel.GetMap());
    m_gameView.PrintSuccessMessage();    
}
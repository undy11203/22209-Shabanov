#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <console/ConsoleView.hpp>
#include <file/FileModel.hpp>
#include <game_logic/GameModel.hpp>

class GameController
{
private:
    GameModel m_gameModel;
    ConsoleView m_consoleView;
    FileModel m_fileModel;
public:
    GameController();
    GameController(GameModel& gameModel, ConsoleView& consoleView, FileModel& fileModel);
    ~GameController() = default;
    bool RunApp();
    void RunOfflineApp(int iterators);
};

#endif
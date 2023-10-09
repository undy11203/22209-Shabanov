#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <GameView.hpp>
#include <file/FileModel.hpp>
#include <game_logic/GameModel.hpp>

class GameController
{
private:
    GameModel m_gameModel;
    GameView m_gameView;
    FileModel m_fileModel;
public:
    GameController();
    GameController(GameModel& gameModel, GameView& gameView, FileModel& fileModel);
    ~GameController() = default;
    bool RunApp();
    void RunOfflineApp(int iterators);
};

#endif
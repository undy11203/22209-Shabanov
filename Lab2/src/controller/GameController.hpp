#pragma once

#include <FileModel.hpp>
#include <GameModel.hpp>
#include <config.hpp>

class GameController {
private:
    GameModel m_gameModel;
    FileModel m_fileModel;
    int m_offlineIteratins = 0;

public:
    GameController();
    GameController(std::vector<std::string> &args);
    void RunApp(TypeView type);
    ~GameController() = default;
    void RunOfflineApp();
};

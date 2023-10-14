#pragma once

#include <console/ConsoleView.hpp>
#include <gui/GuiView.hpp>
#include <file/FileModel.hpp>
#include <game_logic/GameModel.hpp>

class GameController
{
private:
    GameModel m_gameModel;
    ConsoleView m_consoleView;
    GuiView m_guiView;
    FileModel m_fileModel;
    int m_offlineIteratins = 0;
public:
    GameController();
    GameController(int argc, std::vector<std::string>& args);
    ~GameController() = default;
    bool RunAppInConsole();
    void RunAppInGui();
    void RunOfflineApp();
};


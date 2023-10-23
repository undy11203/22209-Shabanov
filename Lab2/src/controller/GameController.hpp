#pragma once

#include <ConsoleView.hpp>
#include <FileModel.hpp>
#include <GameModel.hpp>
#include <ImGuiView.hpp>


class GameController {
private:
  GameModel m_gameModel;
  ConsoleView m_consoleView;
  ImGuiView m_imGuiView;
  FileModel m_fileModel;
  int m_offlineIteratins = 0;

public:
  GameController();
  GameController(std::vector<std::string> &args);
  ~GameController() = default;
  void RunAppInConsole();
  void RunAppInImGui();
  void RunOfflineApp();
};

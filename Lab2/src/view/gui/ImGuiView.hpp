#pragma once

#include <string>
#include <utility>
#include <vector>

struct GLFWwindow;

class ImGuiView {
private:
    int m_width = 1280;
    int m_height = 720;
    GLFWwindow *m_window;
    bool m_mapCheckbox;
    bool m_inputCheckbox;
    bool m_infoCheckbox;

public:
    ImGuiView(/* args */);
    ~ImGuiView();

    void Start();
    void Update();
    void Render();
    int ShouldClose();
    std::pair<bool, int> PrintGetInputBar();
    void PrintInfo(std::string name,
                   std::pair<std::vector<int>, std::vector<int>> rules);
    void PrintMap(std::vector<std::vector<bool>> map);
    void PrintCompletedMessage(std::string message);
    void Delay(int i);
    bool PrintGetInputClose();
};

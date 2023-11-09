#pragma once

#include <bitset>
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
                   std::pair<std::bitset<8>, std::bitset<8>> rules);
    void PrintMap(std::vector<std::vector<bool>> map);
    void PrintCompletedMessage(std::string message);
    void Delay(int i);
    bool PrintGetInputClose();
};

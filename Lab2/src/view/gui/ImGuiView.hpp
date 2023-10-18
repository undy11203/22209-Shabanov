#pragma once

#include <vector>
#include <string>
#include <utility>

struct GLFWwindow;

class ImGuiView
{
private:
    GLFWwindow* m_window;
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
    std::vector<std::pair<std::string, std::string>> PrintGetInputBar();
    void PrintInfo(std::string name, std::pair<std::vector<int>, std::vector<int>> rules);
    void PrintMap(std::vector<std::vector<bool>> map);
    void PrintCompletedMessage(std::string message);
};



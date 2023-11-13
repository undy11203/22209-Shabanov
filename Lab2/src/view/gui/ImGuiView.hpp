#pragma once

#include <IView.hpp>

#include <bitset>
#include <string>
#include <utility>
#include <vector>

struct GLFWwindow;

class ImGuiView : public IView {
private:
    int m_width = 1280;
    int m_height = 720;
    GLFWwindow *m_window;
    bool m_mapCheckbox;
    bool m_inputCheckbox;
    bool m_infoCheckbox;

    void Start();

public:
    ImGuiView(/* args */);
    ~ImGuiView();
    void Update() override;
    void Render() override;
    std::pair<std::string, std::string> GetInput() override;
    int ShouldClose() override;
    void PrintInfo(std::string name,
                   std::pair<std::bitset<8>, std::bitset<8>> rules) override;
    void PrintMap(std::vector<std::vector<bool>> map) override;
    void PrintCompletedMessage(std::string message) override;
    bool PrintStop() override;
    void Delay(int i) override;
    bool IterationsCorrect(int number) override;
};

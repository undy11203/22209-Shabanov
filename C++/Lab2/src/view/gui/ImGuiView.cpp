#include "ImGuiView.hpp"

#include <glad.h>

#include <GLFW/glfw3.h>
#include <imgui.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <chrono>
#include <iostream>
#include <thread>

namespace {
    void DrawCell(int x, int y, bool filled, int verticalSize, int horizontalSize,
                  int windowPosX, int windowPosY) {
        ImVec2 topLeft =
            ImVec2(x * horizontalSize + windowPosX, y * verticalSize + windowPosY);
        ImVec2 bottomRight = ImVec2((x + 1) * horizontalSize + windowPosX,
                                    (y + 1) * verticalSize + windowPosY);

        ImDrawList *draw = ImGui::GetBackgroundDrawList();
        if (filled) {
            draw->AddRectFilled(topLeft, bottomRight,
                                ImColor(ImVec4(1.0, 1.0, 1.0, 1.0)));
        } else {
            draw->AddRectFilled(topLeft, bottomRight,
                                ImColor(ImVec4(0.0, 0.0, 0.0, 1.0)));
        }
    }
} // namespace

ImGuiView::ImGuiView(/* args */)
    : m_window{nullptr},
      m_mapCheckbox{false},
      m_inputCheckbox{false},
      m_infoCheckbox{false} {
    Start();
}

ImGuiView::~ImGuiView() {
}

void ImGuiView::Start() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_window =
        glfwCreateWindow(m_width, m_height, "Game of Life", nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return;
    }
    const char *glsl_version = "#version 130";
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

    // Setup Dear ImGui style
    io.FontDefault =
        io.Fonts->AddFontFromFileTTF("../assets/fonts/FRM325x8.ttf", 18.0f);
    IM_ASSERT(io.FontDefault);
    ImGui::GetStyle().WindowBorderSize = 0.0f;
    auto &colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4{0.1f, 0.105f, 0.11f, 1.0f};

    // Headers
    colors[ImGuiCol_Header] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
    colors[ImGuiCol_HeaderHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
    colors[ImGuiCol_HeaderActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

    // Buttons
    colors[ImGuiCol_Button] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
    colors[ImGuiCol_ButtonHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
    colors[ImGuiCol_ButtonActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

    // Frame BG
    colors[ImGuiCol_FrameBg] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
    colors[ImGuiCol_FrameBgHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
    colors[ImGuiCol_FrameBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    colors[ImGuiCol_TabHovered] = ImVec4{0.38f, 0.3805f, 0.381f, 1.0f};
    colors[ImGuiCol_TabActive] = ImVec4{0.28f, 0.2805f, 0.281f, 1.0f};
    colors[ImGuiCol_TabUnfocused] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};

    // Title
    colors[ImGuiCol_TitleBg] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    colors[ImGuiCol_TitleBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    // ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    glfwMakeContextCurrent(m_window);
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void ImGuiView::Update() {
    glClearColor(0.1f, 0.105f, 0.11f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiView::Render() {
    float startTime = ImGui::GetTime();
    float duration = 0.5f;

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(m_window);

    Delay(100);
}

std::pair<std::string, std::string> ImGuiView::GetInput() {
    std::pair<std::string, std::string> input{"\0", "\0"};
    int tickInput = 0;

    ImGui::SetNextWindowPos(ImVec2(0, 150));
    ImGui::SetNextWindowSize(ImVec2(350, 570));

    ImGui::Begin("Input bar", nullptr, ImGuiWindowFlags_NoCollapse);

    if (ImGui::Button("Dump university")) {
        input.first = "dump";
        input.second = "\0";
        return input;
    }

    ImGui::SetNextItemWidth(150);
    if (ImGui::InputInt("Tick iterations", &tickInput, 0)) {
        if (ImGui::IsItemDeactivatedAfterEdit() && tickInput > -2) {
            input.first = "tick";
            input.second = std::to_string(tickInput);
        }
    }

    ImGui::SetNextItemWidth(150);
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
    ImGui::Text("Input -1 if want infinity loop");
    ImGui::PopStyleColor();

    ImGui::End();

    return input;
}

int ImGuiView::ShouldClose() { return glfwWindowShouldClose(m_window); }

void ImGuiView::PrintInfo(std::string name,
                          std::pair<std::bitset<8>, std::bitset<8>> rules) {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(350, 150));

    ImGui::Begin("Info current game", nullptr, ImGuiWindowFlags_NoCollapse);

    ImGui::Text("Name: %s", name.data());
    ImGui::Text("Rules: B");
    ImGui::SameLine();
    for (size_t i = 0; i < rules.first.size(); i++) {
        if (rules.first.test(i)) {
            ImGui::Text(std::to_string(i + 1).data());
            ImGui::SameLine();
        }
    }
    ImGui::Text(" / S");
    ImGui::SameLine();
    for (size_t i = 0; i < rules.second.size(); i++) {
        if (rules.second.test(i)) {
            ImGui::Text(std::to_string(i + 1).data());
            ImGui::SameLine();
        }
    }
    ImGui::Text("\n");

    ImGui::End();
}

void ImGuiView::PrintMap(std::vector<std::vector<bool>> map) {
    int windowPosX = 350 + (m_width - 350 - map[0].size() * map[0].size()) / 2;
    int windowPosY = (m_height - map.size() * map.size()) / 2;

    for (size_t y = 0; y < map.size(); y++) {
        for (size_t x = 0; x < map[0].size(); x++) {
            DrawCell(x, y, map[y][x], map.size(), map[0].size(), windowPosX,
                     windowPosY);
        }
    }
}

void ImGuiView::PrintCompletedMessage(std::string message) {
    float popupStartTime = ImGui::GetTime();
    float popupDuration = 0.5f;

    while (ImGui::GetTime() - popupStartTime < popupDuration) {
        Update();
        ImGui::OpenPopup("Complete");
        ImGui::SetNextWindowSize(ImVec2(1280 / 2, 720 / 2));
        if (ImGui::BeginPopupModal(
                "Complete", nullptr,
                ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize)) {
            ImVec2 windowSize = ImGui::GetWindowSize();
            ImVec2 textSize = ImGui::CalcTextSize(message.data());

            ImGui::SetCursorPosX((windowSize.x - textSize.x) / 2);
            ImGui::SetCursorPosY((windowSize.y - textSize.y) / 2);
            ImGui::Text(message.data());

            ImGui::EndPopup();
        }
        Render();
    }
}

bool ImGuiView::IterationsCorrect(int number) {
    if (number > 0 || number == -1) {
        return true;
    }
    return false;
}

bool ImGuiView::PrintStop() {
    ImGui::SetNextWindowPos(ImVec2(0, 150));
    ImGui::SetNextWindowSize(ImVec2(350, 570));

    ImGui::Begin("Input bar", nullptr, ImGuiWindowFlags_NoCollapse);

    if (ImGui::Button("Stop")) {
        ImGui::End();
        return true;
    }

    ImGui::End();
    return false;
}

void ImGuiView::Delay(int i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(i));
}
#include "ImGuiView.hpp"

#include <thread>
#include <chrono>

#include "../../vendor/glad/glad.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <iostream>

namespace 
{
    void DrawCell(int x, int y, bool filled, int verticalSize, int horizontalSize, int windowPosX, int windowPosY) {
        ImVec2 topLeft = ImVec2(x*horizontalSize + windowPosX, y*verticalSize + windowPosY);
        ImVec2 bottomRight = ImVec2((x+1)*horizontalSize + windowPosX, (y+1)*verticalSize + windowPosY);

        ImDrawList* draw = ImGui::GetBackgroundDrawList();
        if(filled){
            draw->AddRectFilled(topLeft, bottomRight, ImColor(ImVec4(1.0, 1.0, 1.0, 1.0)));
        }else {
            draw->AddRectFilled(topLeft, bottomRight, ImColor(ImVec4(0.0, 0.0, 0.0, 1.0)));
        }
    }
} // namespace 


ImGuiView::ImGuiView(/* args */) : m_window{nullptr}, m_mapCheckbox{false}, m_inputCheckbox{false}, m_infoCheckbox{false}
{
}

ImGuiView::~ImGuiView()
{
}

void ImGuiView::Start() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_window = glfwCreateWindow(1280, 720, "Game of Life", nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        return;
    }
    const char* glsl_version = "#version 130";
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    io.FontDefault = io.Fonts->AddFontFromFileTTF("../assets/fonts/FRM325x8.ttf", 18.0f);
    IM_ASSERT(io.FontDefault);
    ImGui::GetStyle().WindowBorderSize = 0.0f;
    auto& colors                       = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg]          = ImVec4{0.1f, 0.105f, 0.11f, 1.0f};

    // Headers
    colors[ImGuiCol_Header]        = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
    colors[ImGuiCol_HeaderHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
    colors[ImGuiCol_HeaderActive]  = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

    // Buttons
    colors[ImGuiCol_Button]        = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
    colors[ImGuiCol_ButtonHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
    colors[ImGuiCol_ButtonActive]  = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

    // Frame BG
    colors[ImGuiCol_FrameBg]        = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
    colors[ImGuiCol_FrameBgHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
    colors[ImGuiCol_FrameBgActive]  = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

    // Tabs
    colors[ImGuiCol_Tab]                = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    colors[ImGuiCol_TabHovered]         = ImVec4{0.38f, 0.3805f, 0.381f, 1.0f};
    colors[ImGuiCol_TabActive]          = ImVec4{0.28f, 0.2805f, 0.281f, 1.0f};
    colors[ImGuiCol_TabUnfocused]       = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};

    // Title
    colors[ImGuiCol_TitleBg]          = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    colors[ImGuiCol_TitleBgActive]    = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    // ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    glfwMakeContextCurrent(m_window);
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void ImGuiView::Update(){
    glClearColor(0.1f, 0.105f, 0.11f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiView::Render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(m_window);
}

int ImGuiView::ShouldClose() {
    return glfwWindowShouldClose(m_window);
}

void ImGuiView::PrintInfo(std::string name, std::pair<std::vector<int>, std::vector<int>> rules) {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(350, 150)); 

    ImGui::Begin("Info current game", nullptr, ImGuiWindowFlags_NoCollapse);

    ImGui::Text("Name: %s", name.data());
    ImGui::Text("Rules: B"); ImGui::SameLine();
    for (size_t i = 0; i < rules.first.size(); i++)
    {
        ImGui::Text(std::to_string(rules.first[i]).data());
        ImGui::SameLine();
    }
    ImGui::Text(" / S"); ImGui::SameLine();
    for (size_t i = 0; i < rules.second.size(); i++)
    {
        ImGui::Text(std::to_string(rules.second[i]).data());
        ImGui::SameLine();
    }
    ImGui::Text("\n");

    ImGui::End();
}

std::vector<std::pair<std::string, std::string>> ImGuiView::PrintGetInputBar() {
    std::vector<std::pair<std::string, std::string>> input;
    int tickInput = -1;

    ImGui::SetNextWindowPos(ImVec2(0, 150));
    ImGui::SetNextWindowSize(ImVec2(350, 570));

    ImGui::Begin("Input bar", nullptr, ImGuiWindowFlags_NoCollapse);

    if(ImGui::Button("Dump university")) {
        input.push_back(std::pair<std::string, std::string>{"dump", "\0"});
    }

    ImGui::SetNextItemWidth(150);
    if(ImGui::InputInt("Tick iterations", &tickInput)) {
        if (ImGui::IsItemDeactivatedAfterEdit() && tickInput > 0) {
            input.push_back(std::pair<std::string, std::string>{"tick",std::to_string(tickInput)});
        }
    }
    ImGui::End();
    
    return input;
}

void ImGuiView::PrintMap(std::vector<std::vector<bool>> map) {
    int windowPosX = 350 + 100;
    int windowPosY = 100;

    for (size_t y = 0; y < map.size(); y++)
    {
        for (size_t x = 0; x < map[0].size(); x++)
        {
            DrawCell(x, y, map[y][x], map.size(), map[0].size(), windowPosX, windowPosY);
        }
        
    } 
}
void ImGuiView::PrintCompletedMessage(std::string message) {
    float popupStartTime = ImGui::GetTime();
    float popupDuration = 0.5f; 

    while(ImGui::GetTime() - popupStartTime < popupDuration)    
    {
        Update();
        ImGui::OpenPopup("Complete");
        ImGui::SetNextWindowSize(ImVec2(1280/2, 720/2));
        if (ImGui::BeginPopupModal("Complete", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize)) {
            ImGui::Text(message.data());

            ImGui::EndPopup();
        }
        Render();
    }
}

void ImGuiView::Delay(int i){
    std::this_thread::sleep_for(std::chrono::milliseconds(i));
}

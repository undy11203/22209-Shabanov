#include <iostream>
#include <string>
#include <vector>

#include <view/console/ConsoleView.hpp>
#include <model/game_logic/GameModel.hpp>
#include <model/file/FileModel.hpp>
#include <controller/GameController.hpp>

#include <imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

namespace 
{
    enum TypeView{
        Console,
        Gui
    };
    enum TypeGame {
        Offline,
        Online
    };
} // namespace 

void ConfigGame(TypeView& typeView, TypeGame& typeGame, int argc, std::vector<std::string> args) {
    typeView = Console;
    typeGame = Online;

    for (size_t i = 1; i < argc; i++)
    {
        if (args[i] == "-o") {
            typeGame = Offline;
        }else if(args[i].find("--output") != std::string::npos) {
            typeGame = Offline;
        } else if(args[i] == "--gui") {
            typeView = Gui;
        }
    }
    
}

int main(int argc, char* argv[]) {
    // glfwInit();
    // GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    // if (window == nullptr)
    //     return 1;
    // glfwMakeContextCurrent(window);
    // glfwSwapInterval(1); // Enable vsync
    // const char* glsl_version = "#version 130";
    // // Setup Dear ImGui context
    // IMGUI_CHECKVERSION();
    // ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO(); (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // // Setup Dear ImGui style
    // ImGui::StyleColorsDark();
    // //ImGui::StyleColorsLight();

    // // Setup Platform/Renderer backends
    // ImGui_ImplGlfw_InitForOpenGL(window, true);
    // ImGui_ImplOpenGL3_Init(glsl_version);

    // while(!glfwWindowShouldClose(window)) {
    //     glfwPollEvents();

    //     // Start the Dear ImGui frame
    //     ImGui_ImplOpenGL3_NewFrame();
    //     ImGui_ImplGlfw_NewFrame();
    //     ImGui::NewFrame();
    // }
    std::vector<std::string> args(argv, argv + argc);

    TypeView typeView;
    TypeGame typeGame;

    ConfigGame(typeView, typeGame, argc, args);

    GameController gameController(argc, args);

    if(typeGame == Online) { //online
        if (typeView == Gui) //gui
        {
            gameController.RunAppInGui();
        }else { //console
            while(true){
                if(gameController.RunAppInConsole()) break;
            }
        }
    }else { //offline
        gameController.RunOfflineApp();
    }

    return 0;
}
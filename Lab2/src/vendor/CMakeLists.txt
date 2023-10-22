cmake_minimum_required(VERSION 3.20)

add_library(glad STATIC
    "glad/glad.c"
    "glad/glad.h"
    "glad/khrplatform.h"
)

target_include_directories(glad PUBLIC glad)

set(IMGUI_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

add_library(imgui STATIC
"${IMGUI_SOURCE_DIR}/imgui.h"
"${IMGUI_SOURCE_DIR}/imgui.cpp"
"${IMGUI_SOURCE_DIR}/imgui_demo.cpp"
"${IMGUI_SOURCE_DIR}/imgui_draw.cpp"
"${IMGUI_SOURCE_DIR}/imgui_widgets.cpp"
"${IMGUI_SOURCE_DIR}/imgui_tables.cpp"
"${IMGUI_SOURCE_DIR}/backends/imgui_impl_glfw.h"
"${IMGUI_SOURCE_DIR}/backends/imgui_impl_glfw.cpp"
"${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.h"
"${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
)

target_include_directories(imgui PUBLIC ${IMGUI_SOURCE_DIR})

add_subdirectory(glfw)
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)

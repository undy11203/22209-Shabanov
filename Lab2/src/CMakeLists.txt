cmake_minimum_required(VERSION 3.20)

Project(Game)

add_subdirectory(model)
add_subdirectory(view)
add_subdirectory(controller)

add_subdirectory(vendor/glfw)

add_executable(${PROJECT_NAME} "main.cpp")

set(IMGUI_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)

include_directories("${IMGUI_SOURCE_DIR}")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include)

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

target_link_libraries(${PROJECT_NAME} PRIVATE model view controller)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw imgui)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

cmake_minimum_required(VERSION 3.20)

set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/console/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/console/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/gui/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/gui/*.cpp"
        )
add_library(view STATIC ${SOURCE_FILES})

target_include_directories(view PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/console)
target_include_directories(view PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/gui)

target_link_libraries(view PUBLIC glad glfw imgui)
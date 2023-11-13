cmake_minimum_required(VERSION 3.20)

set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCE_FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/game_logic/includes/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/game_logic/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/game_logic/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/game_logic/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/file/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/file/*.cpp"
        )
        
add_library(model STATIC ${SOURCE_FILES})

# target_compile_options(model PUBLIC --coverage)
# target_compile_options(model PUBLIC -fprofile-arcs)
# target_compile_options(model PUBLIC -ftest-coverage)

target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/file)
target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/game_logic)
target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/game_logic/include)

target_link_libraries(model PUBLIC config)
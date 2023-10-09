cmake_minimum_required(VERSION 3.20)

Project(Game)

add_subdirectory(model)
add_subdirectory(view)
add_subdirectory(controller)

add_executable(Game "main.cpp")

target_link_libraries(Game PRIVATE model view controller)

target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

add_custom_target(crutch
    COMMAND my_program ../assets/1.txt --iterations=10 ../out/1.txt 
    DEPENDS my_program 
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}  
)

add_dependencies(crutch Game) 
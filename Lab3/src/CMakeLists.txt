cmake_minimum_required(VERSION 3.20)

set (CMAKE_CXX_STANDARD 20)

project(sound_processor)

add_subdirectory(factory)
add_subdirectory(model)
add_subdirectory(controller)

file(GLOB SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
        )
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE controller)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")
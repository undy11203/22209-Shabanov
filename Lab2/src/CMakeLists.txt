cmake_minimum_required(VERSION 3.20)

set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

Project(Game)

add_subdirectory(vendor)
add_subdirectory(view)
add_subdirectory(model)
add_subdirectory(controller)

add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE controller)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
   set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")
endif()

if (MINGW)
   set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")
endif()

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
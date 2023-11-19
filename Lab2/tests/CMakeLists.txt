cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

project(GameModelTests)

set(SOURCE_FILES GameModelTests.cpp)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_executable(GameModelTests ${SOURCE_FILES})

add_subdirectory(../src/model model)
add_subdirectory(googletest)

target_link_libraries(GameModelTests PRIVATE model gcov gtest)

find_program(GCOVR_PYTHON gcovr)
if(GCOVR_PYTHON)
    add_custom_target(coverage
        COMMAND ${CMAKE_COMMAND} -E make_directory coverage
        COMMAND ${GCOVR_PYTHON} --root=${CMAKE_SOURCE_DIR}/.. --exclude=${CMAKE_SOURCE_DIR}/.. --html --html-details -o coverage/coverage_report.html
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating code coverage report"
    )
    add_dependencies(GameModelTests coverage)
else()
    message(WARNING "gcovr not found! It is python library for html coverage report")
endif()

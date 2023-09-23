project(CircleBufferTests)

set(SOURCE_FILES CircleBufferTests.cpp)
set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")

add_executable(CircleBufferTests ${SOURCE_FILES})

target_include_directories(CircleBufferTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)

target_link_libraries(CircleBufferTests PRIVATE CircleBufferLib gtest)

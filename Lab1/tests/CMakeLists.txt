project(CircleBufferTests)

set(SOURCE_FILES CircleBufferTests.cpp)

add_executable(CircleBufferTests ${SOURCE_FILES})

target_include_directories(CircleBufferTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)

target_link_libraries(CircleBufferTests PRIVATE CircleBufferLib gtest)

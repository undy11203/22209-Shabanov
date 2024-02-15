project(CircleBufferLib)

file(GLOB SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/includes/*.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/includes/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
        )

add_library(CircleBufferLib ${SOURCE_FILES})
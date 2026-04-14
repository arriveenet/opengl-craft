cmake_minimum_required(VERSION 3.20)
project(opengl-craft LANGUAGES CXX)

set(TARGET opengl-craft)

# ==================================================================================================
# Sources and headers
# ==================================================================================================
set(HDRS
    Application.h
)

set(SRCS
    Application.cpp
    main.cpp
)

# ==================================================================================================
#  Includes & target definition
# ==================================================================================================
add_executable(${TARGET} ${HDRS} ${SRCS})

target_link_libraries(${TARGET} PRIVATE glfw)
target_link_libraries(${TARGET} PRIVATE glad)
target_link_libraries(${TARGET} PRIVATE glm)

# ==================================================================================================
# Compiler flags
# ==================================================================================================
if (MSVC)
    set(COMPILER_FLAGS /W3)
else()
    set(COMPILER_FLAGS -Wall)
endif()

target_compile_options(${TARGET} PRIVATE ${COMPILER_FLAGS})


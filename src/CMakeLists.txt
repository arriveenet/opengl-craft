cmake_minimum_required(VERSION 3.20)
project(opengl-craft LANGUAGES CXX)

set(TARGET opengl-craft)

# ==================================================================================================
# Sources and headers
# ==================================================================================================
set(HDRS
    Application.h
    Camera.h
    Chunk.h
    Engine.h
    FileSystem.h
    Mesh.h
    Shader.h
    ShaderManager.h
    Texture.h
    TextureManager.h
    Window.h
)

set(SRCS
    Application.cpp
    Camera.cpp
    Chunk.cpp
    Engine.cpp
    FileSystem.cpp
    Mesh.cpp
    Shader.cpp
    ShaderManager.cpp
    Texture.cpp
    TextureManager.cpp
    Window.cpp
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


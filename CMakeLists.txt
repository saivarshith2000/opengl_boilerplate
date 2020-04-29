cmake_minimum_required(VERSION 3.1)

project(
    opengl_boilerplate
    VERSION 1.0
    DESCRIPTION "Boilerplate repository for OpenGL Projects"
    LANGUAGES CXX C
    )

# For ccls auto-completion and intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Shader Library
add_library(Shader src/Shader.cpp src/glad.c)
target_include_directories(Shader PUBLIC include)
target_link_libraries(Shader glfw)

# Mesh Library
add_library(Mesh src/Mesh.cpp src/glad.c)
target_include_directories(Mesh PUBLIC include)
target_link_libraries(Mesh Shader)

# Camera Library
add_library(Camera src/Camera.cpp src/glad.c)
target_include_directories(Camera PUBLIC include)
target_link_libraries(Camera glfw)

# Main
add_executable(main src/main.cpp src/glad.c)
target_include_directories(main PUBLIC include)
target_link_libraries(main Shader Mesh Camera glfw dl)
cmake_minimum_required(VERSION 3.1)

project(
    opengl_boilerplate
    VERSION 1.0
    DESCRIPTION "Boilerplate repository for OpenGL Projects"
    LANGUAGES CXX C
    )

set(CMAKE_CXX_FLAGS "-Wall -ldl -lglfw")

add_library(Shader src/Shader.cpp src/glad.c)
target_include_directories(Shader PUBLIC include)

add_executable(main src/main.cpp src/glad.c)
target_include_directories(main PUBLIC include)
target_link_libraries(main Shader)

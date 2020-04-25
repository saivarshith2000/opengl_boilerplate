### OpenGL Boiler Plate
This repository is intended to be a cross-platform boiler plate code for OpenGl Projects.

#### Dependencies
1. GLFW - for window handling, input event handling.
2. GLM - for matrix math
3. GLAD - for loading GL functions independent of the platform
4. CMake - Build system

#### What's in the code
1. OpenGL - basic code for initialisation and window management
2. Buffers - VAO, VBO, EBOs
3. Shader - load and use shaders

#### How to run
1. `mkdir build && cd build/`
2. `cmake ../`
3. `make`
3. `./main`

#### Structure
src - C++ code
include - external header files and project header files
shaders - vertex and fragment shaders


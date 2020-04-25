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
1. Use the utility script. `chmod +x util.sh` to make the script executable.
2. `sh util.sh` to clean build.
3. `sh util.sh run` to the run the application.
4. `sh util.sh build` to build with existing build files.
5. `sh utils.sh clean` to remove the build directory.

#### Structure
src - C++ source
include - external header files and project header files
shaders - vertex and fragment shaders
build - contains build files and main executable.

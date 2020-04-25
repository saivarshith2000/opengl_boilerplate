#include <assert.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.h>

const int SCRHEIGHT = 600;
const int SCRWIDTH = 800;

void resize_callback(GLFWwindow *window, int width, int height);
void process_input(GLFWwindow *window);

int main()
{
    /* OpenGL Initialisation */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(SCRWIDTH, SCRHEIGHT, "OpenGL", 0, 0);
    assert(window != NULL);
    glfwMakeContextCurrent(window);

    /* Load OS-specific function pointers with GLAD */
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    /* viewport settings and callback */
    glViewport(0, 0, SCRWIDTH, SCRHEIGHT);
    glfwSetWindowSizeCallback(window, resize_callback);

    /* Data to render */
    float points[] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.5f, 0.0f, 0.0f
    };

    /* VAO AND VBO */
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /* Shaders */
    Shader shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    /* Render Loop */
    while(!glfwWindowShouldClose(window)) {
        /* Process user input */
        process_input(window);

        /* Draw background color */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Draw triangles */
        shader.useShader();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap buffers and poll for events */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void resize_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
    return ;
}

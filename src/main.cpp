#include <iostream>
#include <assert.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vertexData.h>
#include <Shader.hpp>
#include <Camera.hpp>
#include <Mesh.hpp>

#define SCRWIDTH 800
#define SCRHEIGHT 600

void process_input(GLFWwindow *window);
void resize_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

/* Global variables */
/* Camera Object */
Camera camera(
    glm::vec3(0.0f, 1.0f, 2.0f), 
    glm::vec3(0.0f, 0.0f, 1.0f), 
    glm::vec3(0.0f, 1.0f, 0.0f), 
    3.0f, 2.0f, (1.0f * SCRWIDTH)/SCRHEIGHT
);

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

    /* capture cursor */
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /* Load OS-specific function pointers with GLAD */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return 1;
    }

    /* viewport settings and callbacks */
    glViewport(0, 0, SCRWIDTH, SCRHEIGHT);
    glEnable(GL_DEPTH_TEST);
    glfwSetWindowSizeCallback(window, resize_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    /* Cube Data for rendering -> imported from vertexData.h */
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    /* co-ordinates */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    /* normals */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    Shader cubeShader("./shaders/vertex.glsl", "./shaders/fragment.glsl");

    /* lamp data */
    unsigned int lampVAO;
    glGenVertexArrays(1, &lampVAO);
    glBindVertexArray(lampVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    Shader lampShader("./shaders/vertex.glsl", "./shaders/lamp_fragment.glsl");


    /* mvp matrices */
    glm::mat4 model, view, projection, mvp, vp;
    glm::vec3 cameraDir;

    /* scene settings */
    glm::vec3 lampPos(1.0f, 1.0f, 0.0f);
    glm::vec3 cubePos(0.0f);
    glm::vec3 lightColor(1.0f);
    glm::vec3 objectColor(0.7f, 0.2f, 0.3f);
    cubeShader.setUniformVec3("lightColor", lightColor);
    cubeShader.setUniformVec3("objectColor", objectColor);
    /* Golden cube settings */

    cubeShader.setUniformVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
    cubeShader.setUniformVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
    cubeShader.setUniformVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    cubeShader.setUniformFloat("material.shininess", 32.0f);

    /* Lamp properties */
    cubeShader.setUniformVec3("light.position", lampPos);
    cubeShader.setUniformVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    cubeShader.setUniformVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    cubeShader.setUniformVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

    /* Render Loop */
    float lastFrame = 0.0f, currentFrame, deltaTime;
    while(!glfwWindowShouldClose(window)) {
        /* Frame times */
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        camera.setDelta(deltaTime);

        /* Process user input */
        process_input(window);

        /* Background color */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* view and projection matrices are common for both lamp and cube*/
        view = camera.getViewMatrix();
        projection = camera.getProjectionMatrix();
        vp = projection * view;

        /* Fun stuff */
        glm::vec3 lightColor;
        lightColor.x = sin(currentFrame * 2.0f);
        lightColor.y = sin(currentFrame * 0.7f);
        lightColor.z = sin(currentFrame * 1.3f);
        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); 
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); 
        cubeShader.setUniformVec3("light.ambient", ambientColor);
        cubeShader.setUniformVec3("light.diffuse", diffuseColor);

        /* Draw lamp */
        model = glm::mat4(1.0f);
        model = glm::translate(model, lampPos);
        model = glm::scale(model, glm::vec3(0.2));
        mvp = vp * model;
        lampShader.setUniformMat4f("mvp", mvp);
        glBindVertexArray(lampVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        /* Draw cube */
        /* Calculate MVP */
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubePos);
        mvp = vp * model;
        cameraDir = camera.getCameraDir();
        cubeShader.setUniformMat4f("mvp", mvp);
        cubeShader.setUniformVec3("viewDir", cameraDir);
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        /* swap buffer and poll */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /* Cleanup */
    glfwTerminate();
    return 0;
}


/* Process user input */
void process_input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.handleKeyboard(FORWARD);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.handleKeyboard(BACKWARD);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.handleKeyboard(LEFT);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.handleKeyboard(RIGHT);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.handleKeyboard(ROTATE_CLOCK);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.handleKeyboard(ROTATE_ANTICLOCK);
    return ;
}

/* Callbacks */
void resize_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    camera.handleMouse(xpos, ypos);
    return ;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.handleScroll(yoffset);
    return ;
}
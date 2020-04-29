#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

enum movementDirection {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    ROTATE_CLOCK,
    ROTATE_ANTICLOCK
};

class Camera{
public:
    glm::vec3 cameraPos;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;
    glm::quat cameraQuat;
    glm::vec3 worldUp;
    float fov;
    Camera(glm::vec3 cameraPos, glm::vec3 cameraDir, glm::vec3 worldUp, 
                float movementSens, float mouseSens, float aspect);
    void setDelta(float deltaTime);
    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();
    void handleKeyboard(enum movementDirection dir);
    void handleMouse(double xpos, double ypos);
    void handleScroll(double yoffset);
    glm::vec3 getCameraDir();

private:
    float deltaTime;
    float movementSens;
    float mouseSens;
    float aspect;
    float lastX,lastY,xoffset, yoffset;
    bool firstCapture;
    void updateCameraVectors();
};


#endif // CAMERA_H_
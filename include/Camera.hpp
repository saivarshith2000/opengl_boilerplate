#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

/* Camera movement directions */
enum CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT };

class Camera {
public:
    float movementSens;
    float lookSens;
    float deltaTime;
    glm::vec3 cameraDirection;
    glm::vec3 cameraTarget;
    glm::vec3 cameraPos;
    glm::vec3 globalUp;
    Camera(float movementSens, float lookSens, float initX, float initY);
    glm::mat4 lookAt();
    void setDelta(float deltaTime);
    void handleKeyboard(enum CameraMovement dir);
    void handleMouse(float xpos, float ypos);

private:
    float xoffset;
    float yoffset;
    float lastX;
    float lastY;
    float firstCapture;
    float yaw;
    float pitch;
};

#endif // CAMERA_H
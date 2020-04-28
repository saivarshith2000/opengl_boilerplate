#include <Camera.hpp>

/* Constructor to initiate default values */
Camera::Camera(float movementSens, float lookSens, float initX, float initY)
{
    cameraPos = glm::vec3(0.0f, 2.5f, 2.0f);
    globalUp = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    this->movementSens = movementSens;
    this->lookSens = lookSens;
    firstCapture = 0;
    lastX = initX;
    lastY = initY;
    xoffset = yoffset = 0;
    yaw = -90.0f;
    pitch = 0.0f;
}

/* Sets the frame time */
void Camera::setDelta(float deltaTime)
{
    this->deltaTime = deltaTime;
}


/* returns the lookat matrix */
glm::mat4 Camera::lookAt() {
    // cameraDirection = glm::normalize(cameraTarget - cameraPos);
    return glm::lookAt(cameraPos, cameraPos + cameraDirection, globalUp);
}

/* Handles keyboard input and moves camera accordingly */
void Camera::handleKeyboard(enum CameraMovement dir) {
    float sens = movementSens * deltaTime;
    switch (dir) {
    case FORWARD:
        cameraPos += cameraDirection * sens;
        break;
    case BACKWARD:
        cameraPos -= cameraDirection * sens;
        break;
    case LEFT:
        cameraPos -= glm::normalize(glm::cross(cameraDirection, globalUp)) * sens;
        break;
    case RIGHT:
        cameraPos += glm::normalize(glm::cross(cameraDirection, globalUp)) * sens;
    }
    return;
}

/* Handles mouse input */
void Camera::handleMouse(float xpos, float ypos)
{
    if(firstCapture) {
        lastX = xpos;
        lastY = xpos;
        firstCapture = 0;
    }
    float sens = lookSens * deltaTime;
    xoffset = xpos - lastX;
    yoffset = -ypos + lastY;
    xoffset *= sens;
    yoffset *= sens;
    lastX = xpos;
    lastY = ypos;
    yaw += xoffset;
    pitch += yoffset;
    pitch = (pitch > 89.0f) ? 89.0f : pitch;
    cameraDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraDirection.y = sin(glm::radians(pitch));
    cameraDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraDirection = glm::normalize(cameraDirection);
    return ;
}
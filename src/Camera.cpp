#include <Camera.hpp>
#include <iostream>

/* Constructor for the camera class */
Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraDir, glm::vec3 worldUp,
                float movementSens, float mouseSens, float aspect)
{
    this->cameraPos = cameraPos;
    this->worldUp = worldUp;
    this->cameraUp = worldUp;
    this->movementSens = movementSens;
    this->mouseSens = mouseSens;
    this->aspect = aspect;
    cameraQuat = glm::angleAxis(glm::radians(180.0f), cameraDir);
    fov = 45.0f;
    firstCapture = false;
    updateCameraVectors();
}

/* Keyboard movement handling */
void Camera::handleKeyboard(enum movementDirection dir)
{
    float sens = movementSens * deltaTime;
    glm::vec3 cameraDir = getCameraDir();
    switch(dir){
        case FORWARD:
            cameraPos += cameraDir * sens;
            break;
        case BACKWARD:
            cameraPos -= cameraDir * sens;
            break;
        case LEFT:
            cameraPos -= cameraRight * sens;
            break;
        case RIGHT:
            cameraPos += cameraRight * sens;
            break;
        // case ROTATE_CLOCK:
        //     cameraQuat = glm::angleAxis(glm::radians(0.003f), cameraDir);
        //     updateCameraVectors();
        //     break;
        // case ROTATE_ANTICLOCK:
        //     cameraQuat = glm::angleAxis(glm::radians(0.003f), -cameraDir);
        //     updateCameraVectors();
            break;
    }
}

/* Handle Mouse movement */
void Camera::handleMouse(double xpos, double ypos)
{
    if(firstCapture) {
        firstCapture = false;
        lastX = xpos;
        lastY = ypos;
    }
    float sens = mouseSens * deltaTime;
    xoffset = (xpos - lastX) * sens;
    yoffset = (lastY - ypos) * sens;
    lastX = xpos;
    lastY = ypos;
    glm::quat pitchQuat = glm::quat(glm::radians(-yoffset), cameraRight);
    glm::quat yawQuat = glm::quat(glm::radians(-xoffset), cameraUp);
    cameraQuat = glm::conjugate(glm::normalize(pitchQuat * yawQuat));
    updateCameraVectors();
}

/* Handles scroll input */
void Camera::handleScroll(double yoffset)
{
    if(yoffset > 0 && fov == 90)return ;
    if(yoffset < 0 && fov == 10)return ;
    fov -= yoffset;
}

/* Returns the projection matrix */
glm::mat4 Camera::getProjectionMatrix()
{
    return glm::perspective(glm::radians(fov), aspect, 0.1f, 100.f);
}

/* Returns the view matrix */
glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(cameraPos, cameraPos + getCameraDir(), cameraUp);
}

/* Returns the camera direction vector */
glm::vec3 Camera::getCameraDir() 
{
    return glm::normalize(glm::axis(cameraQuat));
}

/* set the deltaTime for smoothing movement */
void Camera::setDelta(float deltaTime)
{
    this->deltaTime = deltaTime;
}

void Camera::updateCameraVectors()
{
    glm::vec3 cameraDir = glm::normalize(glm::axis(cameraQuat));
    cameraRight = glm::normalize(glm::cross(cameraDir, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraDir));
}
#include <Camera.hpp>

Camera::Camera()
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    worldUp = up;
    yaw = YAW;
    pitch = PITCH;
    movementSens = MOVEMENT_SENS;
    cameraSens = CAMERA_SENS;
    fov = FOV;
    return ;
}

/* Returns the view matrix w.r.t the camera */
glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

/* Update euler angles and front vector */
void Camera::updateCameraVectors()
{
    glm::vec3 new_front;
    new_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    new_front.y = sin(glm::radians(pitch));
    new_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(new_front);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

/* proces input from keyboard */
void Camera::processKeyboardInput(CameraMovement direction, float deltaTime)
{
    float speed = deltaTime * movementSens;
    if (direction == FORWARD)
        position += front * speed;
    if (direction == BACKWARD)
        position -= front * speed;
    if (direction == LEFT)
        position -= right * speed;
    if (direction == RIGHT)
        position += right * speed;
    return ;
}

/* process mouse input */
void Camera::processMouseInput(float xoffset, float yoffset, GLboolean constrainPitch = true)
{
    xoffset *= cameraSens;
    yoffset *= cameraSens;
    yaw += xoffset;
    pitch += yoffset;
    if(constrainPitch) {
        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;
    }
    updateCameraVectors();
}

/* Process mouse scroll */
void Camera::processMouseScroll(float yoffset)
{
    if(fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    else if(fov < 1.0f)
        fov = 1.0f;
    else if(fov > 45.0f)
        fov = 45.0f;
    return ;
}

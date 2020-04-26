#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/* Camera movement directions */
enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

/* Default values */
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float MOVEMENT_SENS = 2.5f;
const float CAMERA_SENS = 0.1f;
const float FOV = 60.0f;

class Camera{
public:
    // Camera vectors
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    // Euler angles for look around
    float yaw;
    float pitch;
    // Instance attributes
    float movementSens;
    float cameraSens;
    float fov;
    /* Public functions */
    glm::mat4 getViewMatrix();
    void updateCameraVectors();
    void processKeyboardInput(CameraMovement direction, float deltaTime);
    void processMouseInput(float xoffset, float yoffset, GLboolean constrainPitch);
    void processMouseScroll(float yoffset);
    /* Constructor */
    Camera();
private:

};

#endif // CAMERA_H

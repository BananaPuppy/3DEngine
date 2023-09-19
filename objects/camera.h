#pragma once
#include <glm/glm.hpp>
class Camera
{
public:
    
    GLFWwindow* window;
    bool firstMouse = true;

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float lastX = 400.0f, lastY = 400.0f; //TODO: Fix initial camera jump
    float rot_sensitivity = 0.1f;
    float pitch = 0, yaw = 0; glm::vec3 direction;
    float pitchMin = -89.9f, pitchMax = 89.9f;

    Camera(GLFWwindow* w) { window = w; }

    void Rotate(double xpos, double ypos)
    {
        if (firstMouse) { lastX = xpos; lastY = ypos; firstMouse = false; }

        float xOffset = xpos - lastX; lastX = xpos;
        float yOffset = lastY - ypos; lastY = ypos;

        xOffset *= rot_sensitivity; yaw += xOffset;
        yOffset *= rot_sensitivity; pitch += yOffset;
        pitch = std::clamp(pitch, pitchMin, pitchMax);

        direction.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
        direction.y = glm::sin(glm::radians(pitch));
        direction.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);
    }

    void Move(glm::vec4 movement, float deltaTime)
    {
        float cameraSpeed = 3.0f * deltaTime;
        if (movement.w) { cameraSpeed *= 1.75f; }
        glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
        cameraPos += (cameraSpeed * cameraFront) * movement.z; // W+S
        cameraPos += (cameraSpeed * cameraRight) * movement.x; // A+D
    }
};
#include <WillowVox/rendering/Camera.h>

#include <WillowVox/core/Logger.h>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace WillowVox
{
    Camera::Camera(Window* window, glm::vec3 position, glm::vec3 direction) : _window(window), position(position), direction(direction)
    {

    }

    // constructor with scalar values
    Camera::Camera(Window* window, float posX, float posY, float posZ, float roll, float pitch, float yaw)
        : _window(window)
    {
        position = glm::vec3(posX, posY, posZ);
        direction = glm::vec3(pitch, yaw, roll);
    }

    glm::vec3 Camera::Front()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(direction.y)) * cos(glm::radians(direction.x));
        front.y = sin(glm::radians(direction.x));
        front.z = sin(glm::radians(direction.y)) * cos(glm::radians(direction.x));
        return glm::normalize(front);
    }

    glm::vec3 Camera::Right()
    {
        return glm::normalize(glm::cross(Front(), glm::vec3(0, 1, 0)));
    }

    glm::vec3 Camera::Up()
    {
        return glm::normalize(glm::cross(Right(), Front()));
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 Camera::GetViewMatrix()
    {
        return glm::lookAt(position, position + Front(), Up());
    }

    glm::mat4 Camera::GetProjectionMatrix()
    {
        glm::ivec2 w = _window->GetWindowSize();
        return glm::perspective(glm::radians(fov), (float)w.x / (float)w.y, 0.1f, 1000.0f);
    }
}
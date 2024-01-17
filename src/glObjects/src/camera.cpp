#include "camera.h"

#include <iostream>
namespace Real
{
Camera& Camera::getInstace()
{
    static Camera instance;
    return instance;
}


Camera& Camera::setSize(csize size)
{
    this->size = size;
    return *this;
}

Camera& Camera::setSpeed(float speed)
{
    this->speed = speed;
    return *this;
}

Camera& Camera::setSensitivity(float sensitivity)
{
    this->sensitivity = sensitivity;
    return *this;
}

Camera& Camera::setFov(float fov)
{
    this->fov = fov;
    return *this;
}

Camera& Camera::setNear(float near)
{
    this->near = near;
    return *this;
}

Camera& Camera::setFar(float far)
{
    this->far = far;
    return *this;
}

Camera& Camera::setPosition(glm::vec3 position)
{
    this->position = position;
    return *this;
}


void Camera::project(Shader& shader, const std::string& uniform)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(this->position, this->position + this->orientation, this->up);
    projection = glm::perspective(
        glm::radians(this->fov),
        (float)(this->size.first / this->size.second),
        this->near,
        this->far);

    shader.setUniformMatrix(glUniformMatrix4fv, uniform, 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::handleInput(Window& window)
{
    if (glfwGetKey(&window, GLFW_KEY_W) == GLFW_PRESS)
    {
        position += speed * orientation;
    }
    if (glfwGetKey(&window, GLFW_KEY_A) == GLFW_PRESS)
    {
        position += speed * -glm::normalize(glm::cross(orientation, up));
    }
    if (glfwGetKey(&window, GLFW_KEY_S) == GLFW_PRESS)
    {
        position += speed * -orientation;
    }
    if (glfwGetKey(&window, GLFW_KEY_D) == GLFW_PRESS)
    {
        position += speed * glm::normalize(glm::cross(orientation, up));
    }
    if (glfwGetKey(&window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        position += speed * up;
    }
    if (glfwGetKey(&window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        position += speed * -up;
    }

    if (glfwGetMouseButton(&window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        glfwSetInputMode(&window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (firstClick)
        {
            glfwSetCursorPos(&window, size.first / 2, size.second / 2);
            firstClick = false;
        }

        double mouseX;
        double mouseY;
        glfwGetCursorPos(&window, &mouseX, &mouseY);

        float rotX = sensitivity * static_cast<float>((mouseY - (size.second / 2)) / size.second);
        float rotY = sensitivity * static_cast<float>((mouseX - (size.first / 2)) / size.first);

        glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

        if (std::abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
        {
            std::cout << "Allowed";
            orientation = newOrientation;
        }

        orientation = glm::rotate(orientation, glm::radians(-rotY), up);

        glfwSetCursorPos(&window, size.first / 2, size.second / 2);
    }
    else if (glfwGetMouseButton(&window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
    {
        glfwSetInputMode(&window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}
}
#include "camera.h"

#include "uniforms.h"

#include <functional>

using namespace std::placeholders;
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

Camera& Camera::setScrollSpeed(float scroll)
{
    this->scroll = scroll;
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

Camera& Camera::setWindow(Window& window)
{
    this->window = &window;
    glfwSetScrollCallback(this->window, &Camera::scrollHandler);
    return *this;
}

glm::vec3 Camera::getPosition()
{
    return position;
}
glm::vec3 Camera::getOrientation()
{
    return orientation;
}

void Camera::scrollHandler(GLFWwindow* window, double xdelta, double ydelta)
{
    Camera& instance = Camera::getInstace();
    instance.position += instance.scroll * static_cast<float>(ydelta) * instance.orientation;
}

void Camera::project(Shader& shader)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(this->position, this->position + this->orientation, this->up);
    projection = glm::perspective(
        glm::radians(this->fov),
        (float)(this->size.first / this->size.second),
        this->near,
        this->far);

    shader.setUniformMatrix(glUniformMatrix4fv, Uniform::CAMERA, 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::handleInput()
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (firstClick)
        {
            glfwSetCursorPos(window, size.first / 2, size.second / 2);
            firstClick = false;
        }

        double mouseX;
        double mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float moveX = static_cast<float>((mouseX - (size.first / 2)) / size.first);
        float moveY = static_cast<float>((mouseY - (size.second / 2)) / size.second);

        glm::vec3 right = glm::normalize(glm::cross(orientation, up));

        position += speed * (moveY * glm::rotate(orientation, glm::radians(90.0f), right)
            - moveX * right);

        glfwSetCursorPos(window, size.first / 2, size.second / 2);
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (firstClick)
        {
            glfwSetCursorPos(window, size.first / 2, size.second / 2);
            firstClick = false;
        }

        double mouseX;
        double mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float rotX = sensitivity * static_cast<float>((mouseY - (size.second / 2)) / size.second);
        float rotY = sensitivity * static_cast<float>((mouseX - (size.first / 2)) / size.first);

        glm::vec3 rightVector = glm::normalize(glm::cross(orientation, up));
        glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), rightVector);

        if (std::abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
            orientation = newOrientation;


        orientation = glm::rotate(orientation, glm::radians(-rotY), up);
        upOrientation = glm::rotate(glm::rotate(upOrientation, glm::radians(-rotX), rightVector), glm::radians(-rotY), up);
        glfwSetCursorPos(window, size.first / 2, size.second / 2);
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE &&
        glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}
}
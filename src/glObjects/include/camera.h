#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <memory>

#include "shader.h"
#include "window.h"

namespace Real
{
class Camera
{
public:
    using csize = std::pair<unsigned int, unsigned int>;

private:
    csize size = { 800, 800 };
    float speed = 2.0f;
    float sensitivity = 100.0f;
    float scroll = 0.08f;
    float fov = 90.0f;
    float near = 0.1f;
    float far = 100.0f;

    glm::vec3 position;
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 upOrientation = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    GLFWwindow* window = nullptr;

    bool firstClick = true;

    Camera() = default;
    ~Camera() = default;
    Camera(const Camera&) = delete;
    Camera& operator= (const Camera) = delete;

    static void scrollHandler(GLFWwindow* window, double xdelta, double ydelta);

public:
    static Camera& getInstace();

    Camera& setSize(csize size);
    Camera& setSpeed(float speed);
    Camera& setSensitivity(float sensitivity);
    Camera& setScrollSpeed(float scroll);
    Camera& setFov(float fov);
    Camera& setNear(float near);
    Camera& setFar(float far);
    Camera& setPosition(glm::vec3 position);
    Camera& setWindow(Window& window);

    glm::vec3 getPosition();
    glm::vec3 getOrientation();

    void project(Shader& shader);

    void handleInput();
};
}
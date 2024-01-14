#include "window.h"

namespace Real
{
Window::Window(std::pair<unsigned int, unsigned int> windowSize, const std::string& windowName)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(
        windowSize.first,
        windowSize.second,
        windowName.c_str(), NULL, NULL);

    if (window == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
}

Window::~Window()
{
    glfwDestroyWindow(window);
}
}

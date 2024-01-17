#include "window.h"

namespace Real
{
Window::Window(Window::wsize windowSize, const std::string& windowName)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    size = windowSize;
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

    glViewport(0, 0, size.first, size.second);
}

Window::~Window()
{
    glfwDestroyWindow(window);
}

unsigned int Window::getWidth()
{
    return size.first;
}

unsigned int Window::getHeight()
{
    return size.second;
}

Window::wsize Window::getSize()
{
    return size;
}

float Window::getAspect()
{
    return static_cast<float>(size.first / size.second);
}
}

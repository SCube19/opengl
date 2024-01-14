#pragma once

#include<memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Real
{
class Window
{
private:
    GLFWwindow* window;

public:
    Window(std::pair<unsigned int, unsigned int> windowSize, const std::string& windowName);
    ~Window();

    GLFWwindow* operator&()
    {
        return window;
    }
};
} // namespace Real

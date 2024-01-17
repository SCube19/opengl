#pragma once

#include<memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Real
{
class Window
{
public:
    using wsize = std::pair<unsigned int, unsigned int>;

private:
    GLFWwindow* window;
    wsize size;

public:
    Window(wsize windowSize, const std::string& windowName);
    ~Window();

    GLFWwindow* operator&()
    {
        return window;
    }

    unsigned int getWidth();
    unsigned int getHeight();
    wsize getSize();
    float getAspect();
};
} // namespace Real

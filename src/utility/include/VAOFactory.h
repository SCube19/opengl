#pragma once

#include "VAO.h"
#include <GLFW/glfw3.h>
#include "shapes.h"
#include <memory>

namespace Real
{
class VAOFactory
{
public:
    enum class Shape : int
    {
        CUBE = 0,
        SMALL_CUBE = 1,
        D8 = 2,
        PLANE = 3,
        PYRAMID = 4
    };
    static std::shared_ptr<VAO> get(Shape shape);
};
}

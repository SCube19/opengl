#pragma once

#include "VAO.h"
#include <GLFW/glfw3.h>
#include "shapes.h"
#include <memory>

namespace Real
{
class VAOFactory
{
private:
    inline static const std::array<std::shared_ptr<VAO>, 5> models = {
         std::shared_ptr<VAO>{new VAO(Shapes::CUBE.first, Shapes::CUBE.second)},
         std::shared_ptr<VAO>{new VAO(Shapes::SMALL_CUBE.first, Shapes::SMALL_CUBE.second)},
         std::shared_ptr<VAO>{new VAO(Shapes::D8.first, Shapes::D8.second)},
         std::shared_ptr<VAO>{new VAO(Shapes::PLANE.first, Shapes::PLANE.second)},
         std::shared_ptr<VAO>{new VAO(Shapes::PYRAMID.first, Shapes::PYRAMID.second)}
    };

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

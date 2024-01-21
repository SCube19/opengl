#include "VAOFactory.h"

namespace Real
{
std::shared_ptr<VAO> VAOFactory::get(VAOFactory::Shape shape)
{
    static const std::array<std::shared_ptr<VAO>, 5> models = {
        std::shared_ptr<VAO>{new VAO(Shapes::CUBE.first, Shapes::CUBE.second)},
        std::shared_ptr<VAO>{new VAO(Shapes::SMALL_CUBE.first, Shapes::SMALL_CUBE.second)},
        std::shared_ptr<VAO>{new VAO(Shapes::D8.first, Shapes::D8.second)},
        std::shared_ptr<VAO>{new VAO(Shapes::PLANE.first, Shapes::PLANE.second)},
        std::shared_ptr<VAO>{new VAO(Shapes::PYRAMID.first, Shapes::PYRAMID.second)}
    };

    return models[static_cast<int>(shape)];
}
}

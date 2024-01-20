#include "VAOFactory.h"

namespace Real
{
namespace
{
std::unique_ptr<VAO> createCube()
{
    return std::unique_ptr<VAO>(new VAO(Shapes::CUBE.first,
        Shapes::CUBE.second,
        { 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0 },
        GL_STATIC_DRAW));
}

std::unique_ptr<VAO> createD8()
{
    std::unique_ptr<VAO> vao(new VAO());

    vao->fromVectors(Shapes::D8.first, Shapes::D8.second, {
        0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0
        });
    vao->linkAttrib({
        1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float))
        });
    vao->linkAttrib({
        2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float))
        });
    vao->linkAttrib({
        3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float))
        });

    return std::move(vao);
}

std::unique_ptr<VAO> createPlane()
{
    std::unique_ptr<VAO> vao(new VAO());

    vao->fromVectors(Shapes::PLANE.first, Shapes::PLANE.second, {
        0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0
        });
    vao->linkAttrib({
        1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float))
        });
    vao->linkAttrib({
        2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float))
        });
    vao->linkAttrib({
        3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float))
        });

    return std::move(vao);
}

std::unique_ptr<VAO> createPyramid()
{
    std::unique_ptr<VAO> vao(new VAO());

    vao->fromVectors(Shapes::PYRAMID.first, Shapes::PYRAMID.second, {
        0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0
        });
    vao->linkAttrib({
        1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float))
        });
    vao->linkAttrib({
        2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float))
        });
    vao->linkAttrib({
        3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float))
        });

    return std::move(vao);
}
}

std::unique_ptr<VAO> VAOFactory::get(VAOFactory::Shape shape)
{
    switch (shape)
    {
    case VAOFactory::Shape::CUBE:
        return createCube();
    case VAOFactory::Shape::D8:
        return createD8();
    case VAOFactory::Shape::PLANE:
        return createPlane();
    case VAOFactory::Shape::PYRAMID:
        return createPyramid();
    default:
        return createCube();
    }
}
}

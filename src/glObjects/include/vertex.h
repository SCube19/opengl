#pragma once

#include "glm/glm.hpp"

namespace Real
{
struct Vertex
{
    using Position = glm::vec3;
    using Color = glm::vec3;
    using UV = glm::vec2;
    using Normal = glm::vec3;

    Position position;
    Color color;
    UV textureUV;
    Normal normal;
};
}
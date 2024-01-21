#pragma once

#include "glm/glm.hpp"

namespace Real
{
struct Vertex
{
    using Position = glm::vec3;
    using Color = glm::vec4;
    using UV = glm::vec2;
    using Normal = glm::vec3;

    Position position = glm::vec3(0.0f);
    Color color = glm::vec4(1.0f);
    UV textureUV = glm::vec2(0.0f);
    Normal normal = glm::vec3(0.0f);
};
}
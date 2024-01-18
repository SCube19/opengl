#pragma once

#include "worldObject.h"

namespace Real
{
class Light : public WorldObject
{

private:
    glm::vec4 color;

    void updateColorUniform();

public:
    template<class T1, class T2>
    Light(T1&& position, T2&& vao, Shader& shader, const glm::vec4& color)
        : WorldObject(position, vao, shader),
        color(color)
    {
        this->updateColorUniform();
    }

    glm::vec4 getColor();
    void setColor(const glm::vec4& texture);

    void draw() override;
};
}
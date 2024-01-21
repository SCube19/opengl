#pragma once

#include <memory>
#include "shader.h"

namespace Real
{
class Drawable
{
protected:
    virtual void _updateUniforms(Shader& shader) = 0;

public:

    virtual void draw(Shader& shader) = 0;
    virtual void updateUniforms(Shader& shader) = 0;
    virtual void rotate(float degree, const glm::vec3& direction) = 0;
    virtual void translate(const glm::vec3& translate) = 0;
    virtual void scale(float scale) = 0;
};
}
#include "light.h"
#include "camera.h"

#include <uniforms/uniforms.h>

namespace Real
{
void Light::updateColorUniform()
{
    shader.setUniform(Uniform::COLOR, color.x, color.y, color.z, color.w);
}

glm::vec4 Light::getColor()
{
    return color;
}

void Light::setColor(const glm::vec4& color)
{
    this->color = color;
    this->updateColorUniform();
}

void Light::draw()
{
    shader.use();
    Real::Camera::getInstace().project(shader);
    vao.draw();
}
}
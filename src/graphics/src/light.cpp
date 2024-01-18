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

void Light::setIntensity(float intensity)
{
    this->intensity = intensity;
}

void Light::applyLight(Model& model)
{
    Shader& shader = model.getShader();
    shader.setUniform(Uniform::LIGHT_TYPE, static_cast<unsigned int>(type));
    shader.setUniform(Uniform::LIGHT_COLOR, color.x, color.y, color.z, color.w);
    shader.setUniform(Uniform::LIGHT_POSITION, position.x, position.y, position.z);
    shader.setUniform(Uniform::LIGHT_INTENSITY, intensity);
    if (type == Light::Type::DIRECTIONAL)
    {
        auto parameters = std::get<DirectionalParameters>(this->parameters);
        shader.setUniform(Uniform::LIGHT_FALLOFF, parameters.falloff.x, parameters.falloff.y);

    }
    else if (type == Light::Type::SPOTLIGHT)
    {
        auto parameters = std::get<SpotlightParameters>(this->parameters);
        shader.setUniform(Uniform::LIGHT_DIRECTION, parameters.direction.x, parameters.direction.y, parameters.direction.z);
        shader.setUniform(Uniform::LIGHT_OUTER, parameters.outer);
        shader.setUniform(Uniform::LIGHT_INNER, parameters.inner);

    }
    else if (type == Light::Type::POINT)
    {
        auto parameters = std::get<PointParameters>(this->parameters);
        shader.setUniform(Uniform::LIGHT_DIRECTION, parameters.direction.x, parameters.direction.y, parameters.direction.z);
    }
}

void Light::draw()
{
    shader.use();
    Real::Camera::getInstace().project(shader);
    vao->draw();
}
}
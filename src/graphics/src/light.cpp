#include "light.h"
#include "camera.h"

#include <uniforms/uniforms.h>

namespace Real
{
void Light::updateColorUniform()
{
    if (shader == nullptr)
        return;
    shader->setUniform(Uniform::COLOR, color.x, color.y, color.z, color.w);
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

Light::ParameterPack Light::getParameterPack()
{
    if (type == Light::Type::DIRECTIONAL)
    {
        auto parameters = std::get<DirectionalParameters>(this->parameters);
        return ParameterPack{
            type: static_cast<GLuint>(type),
            position : {position.x, position.y, position.z},
            color : {color.x, color.y, color.z, color.w},
            intensity : intensity,
            direction : {parameters.direction.x, parameters.direction.y, parameters.direction.z},
            falloff : {.0f, .0f},
            inner : .0f,
            outer : .0f
        };
    }
    else if (type == Light::Type::SPOTLIGHT)
    {
        auto parameters = std::get<SpotlightParameters>(this->parameters);
        return ParameterPack{
            type: static_cast<GLuint>(type),
            position : {position.x, position.y, position.z},
            color : {color.x, color.y, color.z, color.w},
            intensity : intensity,
            direction : {parameters.direction.x, parameters.direction.y, parameters.direction.z},
            falloff : {.0f, .0f},
            inner : parameters.inner,
            outer : parameters.outer
        };
    }
    else// if (type == Light::Type::POINT)
    {
        auto parameters = std::get<PointParameters>(this->parameters);
        return ParameterPack{
            type: static_cast<GLuint>(type),
            position : {position.x, position.y, position.z},
            color : {color.x, color.y, color.z, color.w},
            intensity : intensity,
            direction : {.0f, .0f, .0f},
            falloff : {parameters.falloff.x, parameters.falloff.y},
            inner : .0f,
            outer : .0f
        };
    }
}

void Light::draw()
{
    if (shader == nullptr)
        return;
    shader->use();
    Real::Camera::getInstace().project(*shader);
    vao->draw();
}
}
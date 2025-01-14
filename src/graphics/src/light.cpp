#include "light.h"
#include "camera.h"

#include "uniforms.h"

namespace Real
{
void Light::updateColorUniform(Shader& shader)
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
}

void Light::setIntensity(float intensity)
{
    this->intensity = intensity;
}

glm::vec3 Light::getPosition()
{
    static const float bias = 0.0000001f;
    if (const auto* parameters = std::get_if<DirectionalParameters>(&this->parameters))
    {
        return bias + -5.0f * glm::normalize(parameters->direction);
    }
    return bias + position;
}

Light::Type Light::getType()
{
    return type;
}

void Light::translate(const glm::vec3& translate)
{
    position += translate;
    WorldObject::translate(translate);
}

void Light::rotate(float degree, const glm::vec3& direction)
{
    if (auto* val = std::get_if<DirectionalParameters>(&this->parameters))
    {
        val->direction = glm::rotate(val->direction, degree, direction);
    }
    else if (auto* val = std::get_if<SpotlightParameters>(&this->parameters))
    {
        val->direction = glm::rotate(val->direction, degree, direction);
    }
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

void Light::draw(Shader& shader)
{
    shader.use();
    Real::Camera::getInstace().project(shader);
    updateUniforms(shader);

    vao->draw();
}
}
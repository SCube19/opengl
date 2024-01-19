#pragma once

#include "worldObject.h"
#include "model.h"
#include "VAOFactory.h"

#include <variant>

namespace Real
{
class Light : public WorldObject
{
public:
    enum class Type : unsigned int
    {
        DIRECTIONAL = 0,
        SPOTLIGHT = 1,
        POINT = 2
    };

    struct DirectionalParameters
    {
        glm::vec3 direction;
    };
    struct SpotlightParameters
    {
        glm::vec3 direction;
        float inner;
        float outer;
    };
    struct PointParameters
    {
        glm::vec2 falloff;
    };

    using Parameters = std::variant<DirectionalParameters, SpotlightParameters, PointParameters>;

private:
    Type type;

    glm::vec4 color;

    float intensity;

    Parameters parameters;

    void updateColorUniform();

public:
    Light(Type type, const glm::vec3& position, std::unique_ptr<Shader>&& shader, const glm::vec4& color, float intensity, Parameters parameters)
        : WorldObject(position, VAOFactory::get(VAOFactory::Shape::CUBE), std::move(shader)),
        type(type),
        color(color),
        intensity(intensity),
        parameters(parameters)
    {
        this->updateColorUniform();
    }

    glm::vec4 getColor();
    void setColor(const glm::vec4& texture);

    void setIntensity(float intensity);

    struct ParameterPack
    {
        GLuint  type;
        GLfloat position[3];
        GLfloat color[4];
        GLfloat intensity;
        GLfloat direction[3];
        GLfloat falloff[2];
        GLfloat inner;
        GLfloat outer;
    };

    ParameterPack getParameterPack();

    void draw() override;
};
}
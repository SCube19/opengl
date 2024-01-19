#pragma once

#include "light.h"

#include <memory.h>

namespace Real
{

constexpr unsigned int MAX_LIGHTS = 20;

class LightManager
{
private:
    LightManager() = default;

    std::vector<std::unique_ptr<Light>> lights;

    struct ShaderLightParameters
    {
        GLuint  type[MAX_LIGHTS];
        GLfloat position[3 * MAX_LIGHTS];
        GLfloat color[4 * MAX_LIGHTS];
        GLfloat intensity[MAX_LIGHTS];
        GLfloat direction[3 * MAX_LIGHTS];
        GLfloat falloff[2 * MAX_LIGHTS];
        GLfloat inner[MAX_LIGHTS];
        GLfloat outer[MAX_LIGHTS];
    };

public:
    static LightManager& getInstance();

    void applyLight(Shader& shader);

    void addLight(std::unique_ptr<Light>&& light);

    void removeLight(int index);

    void draw();
};
}
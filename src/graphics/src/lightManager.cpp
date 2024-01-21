#include "lightManager.h"

#include "uniforms.h"
#include "shaderFactory.h"

namespace Real
{
LightManager& LightManager::getInstance()
{
    static LightManager instance;
    return instance;
}

void LightManager::addLight(std::unique_ptr<Light>&& light)
{
    if (lights.size() < MAX_LIGHTS)
        lights.push_back(std::move(light));
}

void LightManager::removeLight(int index)
{
    if (lights.size() > index)
        lights.erase(lights.begin() + index);
}

void LightManager::applyLight(Shader& shader)
{
    ShaderLightParameters parameters = { 0 };
    for (int i = 0; i < lights.size(); i++)
    {
        auto pack = lights[i]->getParameterPack();
        parameters.type[i] = pack.type;
        parameters.position[3 * i] = pack.position[0];
        parameters.position[3 * i + 1] = pack.position[1];
        parameters.position[3 * i + 2] = pack.position[2];
        parameters.color[4 * i] = pack.color[0];
        parameters.color[4 * i + 1] = pack.color[1];
        parameters.color[4 * i + 2] = pack.color[2];
        parameters.color[4 * i + 3] = pack.color[3];
        parameters.intensity[i] = pack.intensity;
        parameters.direction[3 * i] = pack.direction[0];
        parameters.direction[3 * i + 1] = pack.direction[1];
        parameters.direction[3 * i + 2] = pack.direction[2];
        parameters.falloff[2 * i] = pack.falloff[0];
        parameters.falloff[2 * i + 1] = pack.falloff[1];
        parameters.inner[i] = pack.inner;
        parameters.outer[i] = pack.outer;

    }

    shader.setUniformVector<GLuint>(glUniform1uiv, Uniform::LIGHT_TYPE, MAX_LIGHTS, parameters.type);
    shader.setUniformVector<GLfloat>(glUniform4fv, Uniform::LIGHT_COLOR, 4 * MAX_LIGHTS, parameters.color);
    shader.setUniformVector<GLfloat>(glUniform3fv, Uniform::LIGHT_POSITION, 3 * MAX_LIGHTS, parameters.position);
    shader.setUniformVector<GLfloat>(glUniform1fv, Uniform::LIGHT_INTENSITY, MAX_LIGHTS, parameters.intensity);
    shader.setUniformVector<GLfloat>(glUniform3fv, Uniform::LIGHT_DIRECTION, 3 * MAX_LIGHTS, parameters.direction);
    shader.setUniformVector<GLfloat>(glUniform1fv, Uniform::LIGHT_OUTER, MAX_LIGHTS, parameters.outer);
    shader.setUniformVector<GLfloat>(glUniform1fv, Uniform::LIGHT_INNER, MAX_LIGHTS, parameters.inner);
    shader.setUniformVector<GLfloat>(glUniform2fv, Uniform::LIGHT_FALLOFF, 2 * MAX_LIGHTS, parameters.falloff);
}

void LightManager::translateLight(int index, const glm::vec3& translate)
{
    if (lights.size() > index)
        lights[index]->translate(translate);
}

void LightManager::rotateLight(int index, float angle, const glm::vec3& direction)
{
    if (lights.size() > index)
        lights[index]->rotate(angle, direction);
}


void LightManager::draw()
{
    std::shared_ptr<Shader> shader = ShaderFactory::get(ShaderFactory::LightModel::NONE);
    for (auto& light : lights)
        light->draw(*shader);
}
}
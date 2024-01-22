#pragma once

#include "light.h"

#include <memory.h>

namespace Real
{

constexpr unsigned int MAX_LIGHTS = 15;

class LightManager
{
private:
    LightManager();

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

    std::vector<GLuint> depthMapFBO, depthMap, depthCubemapFBO, depthCubemap;
    glm::mat4 pointProjection;
    glm::mat4 parallelProjection;

    std::shared_ptr<Shader> shadowShader;
    std::shared_ptr<Shader> shadowCubeShader;

public:
    static LightManager& getInstance();

    void applyLight(Shader& shader);

    void castShadows(Shader& shader, Window& window, const std::vector<std::shared_ptr<Drawable>>& models);

    void addLight(std::unique_ptr<Light>&& light);

    void removeLight(int index);

    void translateLight(int index, const glm::vec3& translate);

    void rotateLight(int index, float angle, const glm::vec3& direction);

    void draw();
};
}
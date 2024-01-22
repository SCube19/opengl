#include "lightManager.h"

#include "uniforms.h"
#include "shaderFactory.h"
#include <sstream>
#include <ranges>
namespace Real
{
namespace
{
constexpr unsigned int SHADOW_WIDTH = 4096, SHADOW_HEIGHT = 4096;
}

LightManager::LightManager()
{
    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        GLuint depthMapFBO, depthMap, depthCubemapFBO, depthCubemap;
        glGenFramebuffers(1, &depthMapFBO);
        // create depth texture
        glGenTextures(1, &depthMap);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        float clamp[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clamp);
        // attach depth texture as FBO's depth buffer
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);


        glGenFramebuffers(1, &depthCubemapFBO);
        // Texture for Cubemap Shadow Map FBO
        glGenTextures(1, &depthCubemap);

        glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
        for (unsigned int i = 0; i < 6; ++i)
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
                SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        glBindFramebuffer(GL_FRAMEBUFFER, depthCubemapFBO);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        this->depthMapFBO.push_back(depthMapFBO);
        this->depthMap.push_back(depthMap);
        this->depthCubemapFBO.push_back(depthCubemapFBO);
        this->depthCubemap.push_back(depthCubemap);
    }

    pointProjection = glm::perspective(glm::radians(90.0f), 1.0f, Camera::getInstace().getNear(), Camera::getInstace().getFar());
    parallelProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, Camera::getInstace().getNear(), Camera::getInstace().getFar());
    shadowShader = ShaderFactory::get(ShaderFactory::LightModel::SHADOWS);
    shadowCubeShader = ShaderFactory::get(ShaderFactory::LightModel::CUBE_MAP);
    shadowCubeShader->setUniform(Uniform::FAR, Camera::getInstace().getFar());
}

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

void LightManager::castShadows(Shader& shader, Window& window, const std::vector<std::shared_ptr<Drawable>>& drawables)
{
    static constexpr glm::vec3 pointCubelookAts[] = {
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(-1.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, -1.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0),
        glm::vec3(0.0, 0.0, -1.0)
    };

    static constexpr glm::vec3 pointCubeUps[] = {
        glm::vec3(0.0, -1.0, 0.0),
        glm::vec3(0.0, -1.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0),
        glm::vec3(0.0, 0.0, -1.0),
        glm::vec3(0.0, -1.0, 0.0),
        glm::vec3(0.0, -1.0, 0.0)
    };

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);

    for (int i = 0; i < lights.size(); i++)
    {

        glm::vec3 lightPos(lights[i]->getPosition());
        if (lights[i]->getType() == Light::Type::POINT)
        {
            glm::mat4 pointMatrices[6] = {
                pointProjection * glm::lookAt(lightPos, lightPos + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)),
                pointProjection * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)),
                pointProjection * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)),
                pointProjection * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)),
                pointProjection * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)),
                pointProjection * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0))
            };
            shadowCubeShader->setUniformMatrix(glUniformMatrix4fv, "real_shadowMatrices[0]", 1, GL_FALSE, glm::value_ptr(pointMatrices[0]));
            shadowCubeShader->setUniformMatrix(glUniformMatrix4fv, "real_shadowMatrices[1]", 1, GL_FALSE, glm::value_ptr(pointMatrices[1]));
            shadowCubeShader->setUniformMatrix(glUniformMatrix4fv, "real_shadowMatrices[2]", 1, GL_FALSE, glm::value_ptr(pointMatrices[2]));
            shadowCubeShader->setUniformMatrix(glUniformMatrix4fv, "real_shadowMatrices[3]", 1, GL_FALSE, glm::value_ptr(pointMatrices[3]));
            shadowCubeShader->setUniformMatrix(glUniformMatrix4fv, "real_shadowMatrices[4]", 1, GL_FALSE, glm::value_ptr(pointMatrices[4]));
            shadowCubeShader->setUniformMatrix(glUniformMatrix4fv, "real_shadowMatrices[5]", 1, GL_FALSE, glm::value_ptr(pointMatrices[5]));
            shadowCubeShader->setUniform(Uniform::LIGHT_POSITION, lightPos.x, lightPos.y, lightPos.z);

            glBindFramebuffer(GL_FRAMEBUFFER, depthCubemapFBO[i]);
        }
        else
        {
            glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 lightSpaceMatrix = parallelProjection * lightView;
            shadowShader->setUniformMatrix(glUniformMatrix4fv, Uniform::LIGHT_PROJECTION, 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

            std::ostringstream ss;
            ss << Uniform::LIGHT_PROJECTION << "[" << i << "]";
            shader.setUniformMatrix(glUniformMatrix4fv, ss.str(), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

            glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO[i]);
        }

        Shader& shading = lights[i]->getType() == Light::Type::POINT ? *shadowCubeShader : *shadowShader;
        glBindFramebuffer(GL_FRAMEBUFFER, depthCubemapFBO[i]);
        glClear(GL_DEPTH_BUFFER_BIT);
        glCullFace(GL_FRONT);
        for (auto& drawable : drawables)
            drawable->draw(shading);
        glCullFace(GL_BACK);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    glViewport(0, 0, window.getWidth(), window.getHeight());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.setUniform(Uniform::FAR, Camera::getInstace().getFar());
    for (int i = 0; i < lights.size(); i++)
    {
        if (lights[i]->getType() == Light::Type::POINT)
        {
            int slot = 2 * MAX_LIGHTS + i;
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap[i]);
            shader.setUniform("real_shadowCubeMap0", slot);
        }
        else
        {
            int slot = MAX_LIGHTS + i;
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, depthMap[i]);
            std::ostringstream ss;
            ss << Uniform::SHADOW_MAP << "[" << i << "]";
            shader.setUniform(ss.str(), slot);
        }
    }
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
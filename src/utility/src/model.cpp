#include "model.h"

#include <uniforms/uniforms.h>

#include "texture.h"
#include "camera.h"

namespace Real
{
void Model::updateTexturesUniform()
{
    this->textures.bindShader(this->shader);
}

void Model::setTextureSet(TextureSet& textures)
{
    this->textures = std::move(textures);
    this->updateTexturesUniform();
}

void Model::applyLight(Light& light, const std::string& positionUniform, const std::string& colorUniform)
{
    glm::vec3 lightPos = light.getPosition();
    glm::vec4 lightColor = light.getColor();
    shader.setUniform(colorUniform, lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    shader.setUniform(positionUniform, lightPos.x, lightPos.y, lightPos.z);
}

void Model::draw()
{
    shader.use();
    Real::Camera::getInstace().project(this->shader);

    glm::vec3 camPos = Real::Camera::getInstace().getPosition();
    shader.setUniform(Uniform::CAMERA_POSITION, camPos.x, camPos.y, camPos.z);

    textures.bind();
    vao.draw();
}
}

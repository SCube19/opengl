#include "model.h"

#include <uniforms/uniforms.h>

#include "texture.h"
#include "camera.h"

namespace Real
{
void Model::updateTexturesUniform()
{
    if (shader == nullptr)
        return;
    this->textures.bindShader(*shader);
}

void Model::setTextureSet(TextureSet& textures)
{
    this->textures = std::move(textures);
    this->updateTexturesUniform();
}

void Model::draw()
{
    if (shader == nullptr)
        return;

    shader->use();
    Real::Camera::getInstace().project(*shader);

    glm::vec3 camPos = Real::Camera::getInstace().getPosition();
    shader->setUniform(Uniform::CAMERA_POSITION, camPos.x, camPos.y, camPos.z);

    textures.bind();
    vao->draw();
}
}

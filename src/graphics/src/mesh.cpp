#include "mesh.h"

#include "uniforms.h"

namespace Real
{
void Mesh::updateTexturesUniform()
{
    if (shader == nullptr)
        return;

    for (auto& texture : textures)
        texture->bindShader(*shader);
}

void Mesh::updateTexturesUniform(int index)
{
    if (shader == nullptr)
        return;
    textures[index].bindShader(shader);
}

void Mesh::draw()
{
    if (shader == nullptr)
        return;

    //shader->use();
    Real::Camera::getInstace().project(shader);

    glm::vec3 camPos = Real::Camera::getInstace().getPosition();
    shader.setUniform(Uniform::CAMERA_POSITION, camPos.x, camPos.y, camPos.z);

    textures[0]->bind();

    vao->draw();
}
}
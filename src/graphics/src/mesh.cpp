#include "mesh.h"

#include "uniforms.h"

namespace Real
{
void Mesh::updateTexturesUniform()
{
    for (auto& texture : textures)
        texture->bindShader(shader);
}

void Mesh::updateTexturesUniform(int index)
{
    textures[index]->bindShader(shader);
}

void Mesh::draw()
{
    shader.use();
    Real::Camera::getInstace().project(shader);

    glm::vec3 camPos = Real::Camera::getInstace().getPosition();
    shader.setUniform(Uniform::CAMERA_POSITION, camPos.x, camPos.y, camPos.z);

    updateUniforms();

    for (auto& texture : textures)
        texture->bind();

    vao->draw();
}
}
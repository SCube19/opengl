#include "mesh.h"

#include "uniforms.h"

namespace Real
{
void Mesh::updateTexturesUniform(Shader& shader)
{
    if (textures.empty())
    {
        shader.setUniform(Uniform::TEXTURE_PRESENT, 0);
        return;
    }
    shader.setUniform(Uniform::TEXTURE_PRESENT, 1);

    int diffuseNr = 0;
    int specularNr = 0;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        int num;
        if (textures[i]->getType() == Texture::Type::DIFFUSE)
            num = diffuseNr++;
        else
            num = specularNr++;

        textures[i]->bindShader(shader, num);
    }
}

void Mesh::draw(Shader& shader)
{
    shader.use();
    Real::Camera::getInstace().project(shader);

    glm::vec3 camPos = Real::Camera::getInstace().getPosition();
    shader.setUniform(Uniform::CAMERA_POSITION, camPos.x, camPos.y, camPos.z);

    updateUniforms(shader);

    for (auto& texture : textures)
        texture->bind();

    vao->draw();
}
}
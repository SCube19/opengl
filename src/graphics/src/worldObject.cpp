#include "worldObject.h"

#include "uniforms.h"

#include "camera.h"

namespace Real
{
void WorldObject::updateModelUniform(Shader& shader)
{
    shader.setUniformMatrix(
        glUniformMatrix4fv,
        Uniform::MODEL,
        1, GL_FALSE, glm::value_ptr(this->model));
}

void WorldObject::rotate(float degree, const glm::vec3& direction)
{
    this->model = glm::rotate(this->model, glm::radians(degree), direction);
}

void WorldObject::translate(const glm::vec3& translate)
{
    this->model = glm::translate(this->model, translate);
}

void WorldObject::scale(float scale)
{
    this->model = glm::scale(this->model, glm::vec3(scale));
}


void WorldObject::updateUniforms(Shader& shader)
{
    updateModelUniform(shader);
    _updateUniforms(shader);
}
}
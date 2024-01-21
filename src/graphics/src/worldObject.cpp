#include "worldObject.h"

#include "uniforms.h"

#include "camera.h"

namespace Real
{
void WorldObject::updateModelUniform()
{
    shader->setUniformMatrix(
        glUniformMatrix4fv,
        Uniform::MODEL,
        1, GL_FALSE, glm::value_ptr(this->model));
}

void WorldObject::updatePositionUniform()
{
    shader->setUniform(
        Uniform::POSITION,
        this->position.x, this->position.y, this->position.z);
}

glm::vec3 WorldObject::getPosition()
{
    return position;
}

void WorldObject::setPosition(const glm::vec3& position)
{
    translate(position - this->position);
}

Shader& WorldObject::getShader()
{
    return *shader;
}

void WorldObject::setShader(std::unique_ptr<Shader>&& shader)
{
    this->shader = std::move(shader);
}

void WorldObject::rotate(float degree, const glm::vec3& direction)
{
    this->model = glm::rotate(this->model, glm::radians(degree), direction);
    this->updateModelUniform();
}

void WorldObject::translate(const glm::vec3& translate)
{
    position += translate;
    this->updatePositionUniform();
    this->model = glm::translate(this->model, translate);
    this->updateModelUniform();
}
}
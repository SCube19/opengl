#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <any>

#include "shader.h"
#include "VAO.h"

namespace Real
{
class WorldObject
{
private:
    void updateModelUniform();
    void updatePositionUniform();

protected:
    glm::vec3 position;
    glm::mat4 model;

    std::unique_ptr<VAO> vao;
    std::unique_ptr<Shader> shader;

public:
    using uniform = std::pair<std::string, std::any>;

    WorldObject(const glm::vec3& position, std::unique_ptr<VAO>&& vao, std::unique_ptr<Shader>&& shader)
        :position(position),
        model(glm::mat4(1.0f)),
        vao(std::move(vao)),
        shader(std::move(shader))
    {
        this->translate(position);
        this->updateModelUniform();
        this->updatePositionUniform();
    }

    glm::vec3 getPosition();
    void setPosition(const glm::vec3& position);

    Shader& getShader();
    void setShader(std::unique_ptr<Shader>&& shader);

    void rotate(float degree, const glm::vec3& direction);

    void translate(const glm::vec3& translate);

    virtual void draw() = 0;
};
}
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
#include "drawable.h"

namespace Real
{
class WorldObject : public Drawable
{
private:
    void updateModelUniform(Shader& shader);
    void updatePositionUniform(Shader& shader);

protected:
    glm::mat4 model;

    std::shared_ptr<VAO> vao;

public:
    WorldObject(const glm::vec3& position, const std::shared_ptr<VAO> vao)
        :model(glm::mat4(1.0f)),
        vao(vao)
    {
        this->translate(position);
    }

    WorldObject(const glm::vec3& position,
        const std::vector<Vertex>& vertices,
        const std::vector<GLuint>& indices)
        :
        model(glm::mat4(1.0f)),
        vao(new VAO(vertices, indices))
    {
        this->translate(position);
    }

    virtual void rotate(float degree, const glm::vec3& direction) override;

    virtual void translate(const glm::vec3& translate) override;

    virtual void scale(float scale) override;

    void updateUniforms(Shader& shader) override;
};
}
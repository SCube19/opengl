#pragma once

#include<glad/glad.h>
#include <vector>
#include <memory>

#include "glObject.h"
#include "VBO.h"
#include "EBO.h"

namespace Real
{
class VAO : public GLObject
{
private:
    GLuint id;
    bool isBound;

    std::unique_ptr<VBO> vbo;
    std::unique_ptr<EBO> ebo;

public:
    VAO();
    ~VAO();

    void bind();
    void unbind();

    void linkVBO(std::unique_ptr<VBO>&& vbo, GLuint layout);
    void linkEBO(std::unique_ptr<EBO>&& ebo);
    void fromVectors(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
};
}
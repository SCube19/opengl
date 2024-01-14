#include <memory.h>
#include <iostream>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

namespace Real
{
VAO::VAO() : vbo(nullptr), ebo(nullptr)
{
    glGenVertexArrays(1, &id);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &id);
}

void VAO::bind()
{
    glBindVertexArray(id);
    isBound = true;
}

void VAO::unbind()
{
    if (vbo != nullptr)
        vbo->unbind();
    if (isBound)
    {
        glBindVertexArray(0);
        isBound = false;
    }
    if (ebo != nullptr)
        ebo->unbind();
}

void VAO::linkVBO(std::unique_ptr<VBO>&& vbo, GLuint layout)
{
    this->bind();

    this->vbo = std::move(vbo);

    this->vbo->bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(layout);

    this->unbind();
}

void VAO::linkEBO(std::unique_ptr<EBO>&& ebo)
{
    this->ebo = std::move(ebo);
}

void VAO::fromVectors(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices)
{
    this->bind();
    std::unique_ptr<VBO> vbo = std::make_unique<VBO>(vertices, GL_STATIC_DRAW);
    std::unique_ptr<EBO> ebo = std::make_unique<EBO>(indices, GL_STATIC_DRAW);

    this->linkVBO(std::move(vbo), 0);
    this->linkEBO(std::move(ebo));
}
}
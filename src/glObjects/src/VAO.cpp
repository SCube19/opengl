#include <memory.h>
#include <iostream>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

namespace Real
{

VAO::VAO(const std::vector<GLfloat>& vertices,
    const std::vector<GLuint>& indices,
    const Config& config,
    int drawType) : VAO()

{
    this->fromVectors(vertices, indices, config, drawType);
}


VAO::VAO() : vbo(nullptr), ebo(nullptr), isBound(false)
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

void VAO::linkVBO(std::unique_ptr<VBO>&& vbo, const Config& config)
{
    bind();

    this->vbo = std::move(vbo);

    this->vbo->bind();
    glVertexAttribPointer(
        config.layout,
        config.numberOfComponents,
        config.type,
        GL_FALSE,
        config.stride,
        config.offset);
    glEnableVertexAttribArray(config.layout);

    unbind();
}

void VAO::linkEBO(std::unique_ptr<EBO>&& ebo)
{
    ebo = std::move(ebo);
    nVertices = ebo->getNumberOfIndices();
}

void VAO::linkAttrib(const Config& config)
{
    linkVBO(std::move(vbo), config);
}

void VAO::fromVectors(
    const std::vector<GLfloat>& vertices,
    const std::vector<GLuint>& indices,
    const Config& config,
    int drawType)
{
    this->bind();
    std::unique_ptr<VBO> vbo = std::make_unique<VBO>(vertices, drawType);
    std::unique_ptr<EBO> ebo = std::make_unique<EBO>(indices, drawType);

    linkVBO(std::move(vbo), config);
    linkEBO(std::move(ebo));
}

VBO& VAO::getVBO()
{
    return *vbo;
}

EBO& VAO::getEBO()
{
    return *ebo;
}

int VAO::getNumberOfVertices()
{
    return nVertices;
}

void VAO::draw()
{
    bind();
    glDrawElements(GL_TRIANGLES, getNumberOfVertices(), GL_UNSIGNED_INT, 0);
}

}
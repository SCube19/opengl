#include <memory.h>
#include <iostream>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

namespace Real
{

VAO::VAO(const std::vector<Vertex>& vertices,
    const std::vector<GLuint>& indices,
    int drawType) : VAO()
{
    this->bind();
    this->vbo = std::make_unique<VBO>(vertices, drawType);
    this->ebo = std::make_unique<EBO>(indices, drawType);

    linkAttrib({ 0, 3, GL_FLOAT, sizeof(Vertex), (void*)(0) });
    linkAttrib({ 1, 4, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)) });
    linkAttrib({ 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(7 * sizeof(float)) });
    linkAttrib({ 3, 3, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)) });
    nVertices = ebo->getNumberOfIndices();
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

void VAO::linkAttrib(const Config& config)
{
    bind();

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
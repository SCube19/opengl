#include "EBO.h"


namespace Real
{
EBO::EBO(const std::vector<GLuint>& indices, int drawType) : isBound(true), nIndices(indices.size())
{
    glGenBuffers(1, &id);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), drawType);
}

EBO::~EBO()
{
    glDeleteBuffers(1, &id);
}

void EBO::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    isBound = true;
}

void EBO::unbind()
{
    if (isBound)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        isBound = false;
    }
}

int EBO::getNumberOfIndices()
{
    return nIndices;
}
}
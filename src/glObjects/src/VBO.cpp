#include "VBO.h"


namespace Real
{
VBO::VBO(const std::vector<GLfloat>& vertices, int drawType) : isBound(true)
{
    glGenBuffers(1, &id);

    glBindBuffer(GL_ARRAY_BUFFER, id);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), drawType);
}

VBO::~VBO()
{
    glDeleteBuffers(1, &id);
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
    isBound = true;
}

void VBO::unbind()
{
    if (isBound)
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        isBound = false;
    }

}

}
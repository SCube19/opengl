#pragma once

#include<glad/glad.h>
#include <vector>

#include "glObject.h"

namespace Real
{
class VBO : public GLObject
{
private:
    GLuint id;
    bool isBound;

public:
    VBO(const std::vector<GLfloat>& vertices, int drawType);
    ~VBO();

    void bind();
    void unbind();
};
}
#pragma once

#include<glad/glad.h>
#include <vector>

#include "glObject.h"
#include "vertex.h"

namespace Real
{


class VBO : public GLObject
{
private:
    GLuint id;
    bool isBound;

public:
    VBO(const std::vector<Vertex>& vertices, int drawType);
    ~VBO();

    void bind();
    void unbind();
};
}
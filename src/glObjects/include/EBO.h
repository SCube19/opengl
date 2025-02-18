#pragma once

#include<glad/glad.h>
#include <vector>

#include "glObject.h"

namespace Real
{
class EBO : public GLObject
{
private:
    GLuint id;
    bool isBound;

    int nIndices;

public:
    EBO(const std::vector<GLuint>& indices, int drawType);
    ~EBO();

    void bind();
    void unbind();

    int getNumberOfIndices();
};
}
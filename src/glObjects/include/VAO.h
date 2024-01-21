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
    struct Config
    {
        GLuint layout;
        GLuint numberOfComponents;
        GLuint type;
        GLsizeiptr stride;
        void* offset;
    };

    GLuint id;
    bool isBound;

    std::unique_ptr<VBO> vbo;
    std::unique_ptr<EBO> ebo;

    int nVertices;

    void linkAttrib(const Config& config);


public:
    VAO(const std::vector<Vertex>& vertices,
        const std::vector<GLuint>& indices,
        int drawType = GL_STATIC_DRAW);
    VAO();

    ~VAO();

    void bind();
    void unbind();

    VBO& getVBO();
    EBO& getEBO();

    int getNumberOfVertices();

    void draw();
};
}
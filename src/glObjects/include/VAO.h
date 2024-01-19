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

    int nVertices;

public:
    struct Config
    {
        GLuint layout;
        GLuint numberOfComponents;
        GLenum type;
        GLsizeiptr stride;
        void* offset;
    };

    VAO(const std::vector<GLfloat>& vertices,
        const std::vector<GLuint>& indices,
        const Config& config,
        int drawType = GL_STATIC_DRAW);
    VAO();

    ~VAO();

    void bind();
    void unbind();

    void linkVBO(std::unique_ptr<VBO>&& vbo, const Config& config);
    void linkEBO(std::unique_ptr<EBO>&& ebo);
    void linkAttrib(const Config& config);

    void fromVectors(
        const std::vector<GLfloat>& vertices,
        const std::vector<GLuint>& indices,
        const Config& config,
        int drawType = GL_STATIC_DRAW);

    VBO& getVBO();
    EBO& getEBO();

    int getNumberOfVertices();

    void draw();
};
}
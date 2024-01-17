#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <optional>
#include "stb/stb_image.h"

#include "glObject.h"
#include "shader.h"

namespace Real
{
class Texture : public GLObject
{
private:
    GLuint id;
    GLenum type;
    GLuint slot;

public:
    Texture(
        const std::string& image,
        GLenum texType,
        GLuint slot,
        GLenum format,
        GLenum pixelType);

    ~Texture();


    void bind();
    void unbind();

    void bindShader(Shader& shader, const std::string& uniformName);
};
}
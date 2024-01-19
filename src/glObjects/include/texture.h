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
public:
    enum class Type
    {
        DIFFUSE,
        SPECULAR
    };
private:
    GLuint id;
    Type type;
    GLuint slot;

public:
    Texture(const std::string& image, Type texType, GLuint slot);

    ~Texture();

    void bind();
    void unbind();

    void bindShader(Shader& shader);
};
}
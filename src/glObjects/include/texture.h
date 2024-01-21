#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <optional>
#include "stb/stb_image.h"

#include "glObject.h"
#include "shader.h"
#include "uniforms.h"

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
    std::string path;

public:
    Texture(const std::string& image, Type texType, GLuint slot);

    ~Texture();

    void bind();
    void unbind();

    Type getType();

    void bindShader(Shader& shader, int index);

    friend inline bool operator==(const Texture& lhs, const Texture& rhs)
    {
        return lhs.path == rhs.path;
    }

    friend bool operator<(const Texture& lhs, const Texture& rhs)
    {
        return lhs.path < rhs.path;
    }
};
}
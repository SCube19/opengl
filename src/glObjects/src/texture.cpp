#include "texture.h"

namespace Real
{
Texture::Texture(const std::string& image, Texture::Type texType)
{
    path = image;
    stbi_set_flip_vertically_on_load(true);

    type = texType;
    this->slot = static_cast<GLuint>(type == Texture::Type::SPECULAR);

    int w, h, ch;
    unsigned char* bytes = stbi_load(image.c_str(), &w, &h, &ch, 0);

    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (type == Texture::Type::DIFFUSE)
    {
        try
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
        }
        catch (std::exception& e)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
        }
    }
    else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &id);
}

Texture::Type Texture::getType()
{
    return type;
}

void Texture::bind()
{
    glActiveTexture(GL_TEXTURE0 + this->slot);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bindShader(Shader& shader, int index)
{
    shader.setUniform<GLint>(type == Texture::Type::DIFFUSE ?
        Uniform::TEXTURES[index] : Uniform::SPECULAR[index], this->slot);
}
}

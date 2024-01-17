#include "texture.h"


namespace Real
{
Texture::Texture(
    const std::string& image,
    GLenum texType,
    GLuint slot,
    GLenum format,
    GLenum pixelType)
{
    stbi_set_flip_vertically_on_load(true);

    type = texType;
    this->slot = slot;

    int w, h, ch;
    unsigned char* bytes = stbi_load(image.c_str(), &w, &h, &ch, 0);

    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(texType, id);

    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(texType, 0, GL_RGBA, w, h, 0, format, pixelType, bytes);
    glGenerateMipmap(texType);

    stbi_image_free(bytes);

    glBindTexture(type, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &id);
}

void Texture::bind()
{
    glActiveTexture(GL_TEXTURE0 + this->slot);
    glBindTexture(type, id);
}

void Texture::unbind()
{
    glBindTexture(type, 0);
}

void Texture::bindShader(Shader& shader, const std::string& uniformName)
{
    shader.setUniform<GLint>(uniformName, this->slot);
}
}

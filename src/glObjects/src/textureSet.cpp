#include "textureSet.h"
#include <uniforms/uniforms.h>

namespace Real
{
TextureSet::TextureSet(std::unique_ptr<Texture> texture, std::unique_ptr<Texture> specular)
    : texture(std::move(texture)),
    specular(std::move(specular))
{
}

void TextureSet::bind()
{
    if (texture != nullptr)
        texture->bind();
    if (specular != nullptr)
        specular->bind();
}

void TextureSet::bindShader(Shader& shader)
{
    if (texture != nullptr)
        texture->bindShader(shader);
    if (specular != nullptr)
        specular->bindShader(shader);
}
}
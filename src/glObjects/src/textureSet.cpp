#include "textureSet.h"
#include <uniforms/uniforms.h>

namespace Real
{
TextureSet::TextureSet(std::unique_ptr<Texture> texture, std::unique_ptr<Texture> specular)
    : texture(std::move(texture)),
    specular(std::move(specular))
{
}

// Texture* TextureSet::getTexture()
// {
//     return *texture;
// }

// std::optional<Texture>& TextureSet::getSpecular()
// {
//     return specular;
// }

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
        texture->bindShader(shader, Uniform::TEXTURE);
    if (specular != nullptr)
        specular->bindShader(shader, Uniform::SPECULAR);
}
}
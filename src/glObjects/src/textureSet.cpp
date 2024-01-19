#include "textureSet.h"
#include <uniforms/uniforms.h>

namespace Real
{
TextureSet::TextureSet(const std::shared_ptr<Texture>& texture, const std::shared_ptr<Texture>& specular)
    : texture(texture),
    specular(specular)
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
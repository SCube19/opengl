#pragma once

#include "texture.h"

#include <memory>

namespace Real
{
class TextureSet
{
private:
    std::shared_ptr<Texture> texture;
    std::shared_ptr<Texture> specular;

public:
    TextureSet(const std::shared_ptr<Texture>& texture, const std::shared_ptr<Texture>& specular);

    // Texture& getTexture();
    // std::optional<Texture>& getSpecular();

    void bind();

    void bindShader(Shader& shader);
};
}
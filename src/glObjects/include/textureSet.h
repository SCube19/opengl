#pragma once

#include "texture.h"

#include <memory>

namespace Real
{
class TextureSet
{
private:
    std::unique_ptr<Texture> texture;
    std::unique_ptr<Texture> specular;

public:
    TextureSet(std::unique_ptr<Texture> texture, std::unique_ptr<Texture> specular);

    // Texture& getTexture();
    // std::optional<Texture>& getSpecular();

    void bind();

    void bindShader(Shader& shader);
};
}
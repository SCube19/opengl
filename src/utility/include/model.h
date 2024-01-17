#pragma once

#include "worldObject.h"
#include "texture.h"
#include "light.h"

namespace Real
{
class Model : public WorldObject
{
private:
    Texture& texture;

    std::string textureUniform;

    void updateTextureUniform();

public:
    template<class T1, class T2>
    Model(T1&& position, T2&& vao, Shader& shader,
        Texture& texture, const std::string& textureUniform)
        : WorldObject(position, vao, shader),
        texture(texture),
        textureUniform(textureUniform)
    {
        this->updateTextureUniform();
    }


    Texture& getTexture();
    void setTexture(const Texture& texture);

    void applyLight(Light& light, const std::string& positionUniform, const std::string& colorUniform);

    void draw() override;
};
}
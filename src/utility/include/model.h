#pragma once

#include "worldObject.h"
#include "textureSet.h"
#include "light.h"

namespace Real
{
class Model : public WorldObject
{
private:
    TextureSet& textures;

    void updateTexturesUniform();

public:
    template<class T1, class T2>
    Model(T1&& position, T2&& vao, Shader& shader,
        TextureSet& textures)
        : WorldObject(position, vao, shader),
        textures(textures)
    {
        this->updateTexturesUniform();
    }


    TextureSet& getTextureSet();
    void setTextureSet(TextureSet& textures);

    void applyLight(Light& light, const std::string& positionUniform, const std::string& colorUniform);

    void draw() override;
};
}
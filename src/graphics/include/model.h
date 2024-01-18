#pragma once

#include "worldObject.h"
#include "textureSet.h"

namespace Real
{
class Model : public WorldObject
{
private:
    TextureSet& textures;

    void updateTexturesUniform();

public:
    Model(const glm::vec3& position, std::unique_ptr<VAO>&& vao, Shader& shader,
        TextureSet& textures)
        : WorldObject(position, std::move(vao), shader),
        textures(textures)
    {
        this->updateTexturesUniform();
    }


    TextureSet& getTextureSet();
    void setTextureSet(TextureSet& textures);

    void draw() override;
};
}
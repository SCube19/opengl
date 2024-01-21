#pragma once


#include "texture.h"
#include "VAO.h"
#include "worldObject.h"
#include "camera.h"
#include "vertex.h"

#include <memory>

namespace Real
{
class Mesh : public WorldObject
{
private:
    std::vector<std::shared_ptr<Texture>> textures;

    void updateTexturesUniform();
    void updateTexturesUniform(int index);

    void _updateUniforms() override
    {
        updateTexturesUniform();
    }

public:
    Mesh(const glm::vec3& position, const std::shared_ptr<VAO>& vao, const std::shared_ptr<Shader> shader,
        std::vector<std::shared_ptr<Texture>> textures)
        : WorldObject(position, std::move(vao), std::move(shader)),
        textures(textures)
    {
    }

    Mesh(const glm::vec3& position,
        const std::vector<Vertex>& vertices,
        const std::vector<GLuint>& indices,
        const std::shared_ptr<Shader>& shader,
        std::vector<std::shared_ptr<Texture>> textures)
        : WorldObject(position, vertices, indices, std::move(shader)),
        textures(textures)
    {
    }

    void draw() override;
};
}

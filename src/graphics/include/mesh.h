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

    void updateTexturesUniform(Shader& shader);

    void _updateUniforms(Shader& shader) override
    {
        updateTexturesUniform(shader);
    }

public:
    Mesh(const glm::vec3& position, const std::shared_ptr<VAO>& vao,
        std::vector<std::shared_ptr<Texture>> textures)
        : WorldObject(position, std::move(vao)),
        textures(textures)
    {
    }

    Mesh(const glm::vec3& position,
        const std::vector<Vertex>& vertices,
        const std::vector<GLuint>& indices,
        std::vector<std::shared_ptr<Texture>> textures)
        : WorldObject(position, vertices, indices),
        textures(textures)
    {
    }

    void draw(Shader& shader) override;
};
}

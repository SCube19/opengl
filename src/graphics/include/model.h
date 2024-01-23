#pragma once

#include "worldObject.h"

#include "mesh.h"
#include "drawable.h"
#include "texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <memory>
#include <map>
namespace Real
{
class Model : public Drawable
{
private:
    std::vector<std::unique_ptr<Mesh>> meshes;

    std::map<std::string, std::shared_ptr<Texture>> loadedTextures;

    std::string directory;

    void _updateUniforms(Shader& shader)
    {

    }

    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    std::unique_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        Texture::Type typeName);

public:
    Model(const std::string& path)
    {
        loadModel(path);
    }

    void draw(Shader& shader) override;

    void draw(Shader& shader, Mesh& additional);

    void setDiffuse(const std::shared_ptr<Texture>& tex)
    {
        for (auto& mesh : meshes)
            mesh->setDiffuse(tex);
    }

    void updateUniforms(Shader& shader)
    {
        _updateUniforms(shader);
    }

    void rotate(float degree, const glm::vec3& direction)
    {
        for (auto& mesh : meshes)
            mesh->rotate(degree, direction);
    }

    void translate(const glm::vec3& translate)
    {
        for (auto& mesh : meshes)
            mesh->translate(translate);
    }

    void scale(float scale) override
    {
        for (auto& mesh : meshes)
            mesh->scale(scale);
    }
};
}
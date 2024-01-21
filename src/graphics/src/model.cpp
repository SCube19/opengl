#include "model.h"
#include <stdexcept>
#include <sstream>

namespace Real
{
void Model::loadModel(const std::string& path)
{
    Assimp::Importer import;
    //WARN: remeber bout the flip
    const aiScene * scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_OptimizeMeshes);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::ostringstream ss;
        ss << "ERROR::ASSIMP::" << import.GetErrorString();
        std::runtime_error(ss.str());
    }

    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

std::unique_ptr<Mesh> Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<std::shared_ptr<Texture>> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;
        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.textureUV = vec;
        }
        else
            vertex.textureUV = Vertex::UV(0.0f, 0.0f);
        vertex.color = Vertex::Color(1.0f);
        vertices.push_back(vertex);
    }
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<std::shared_ptr<Texture>> diffuseMaps = loadMaterialTextures(material,
            aiTextureType_DIFFUSE, Texture::Type::DIFFUSE, 0);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<std::shared_ptr<Texture>> specularMaps = loadMaterialTextures(material,
            aiTextureType_SPECULAR, Texture::Type::DIFFUSE, diffuseMaps.size());
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return std::unique_ptr<Mesh>(new Mesh(glm::vec3(0.0f), vertices, indices, textures));
}

std::vector<std::shared_ptr<Texture>> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type,
    Texture::Type typeName, int offset)
{
    std::vector<std::shared_ptr<Texture>> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::string path = str.C_Str();
        if (!loadedTextures.contains(path))
        {
            std::shared_ptr<Texture> texture(new Texture(std::string(path), typeName, i + offset));
            loadedTextures[path] = texture;
        }
        textures.push_back(loadedTextures[path]);
    }
    return textures;
}

void Model::draw(Shader& shader)
{
    shader.use();
    for (auto& mesh : meshes)
        mesh->draw(shader);
}

void Model::draw(Shader& shader, Mesh& additional)
{
    shader.use();
    //additional.draw(shader);
    for (auto& mesh : meshes)
        mesh->draw(shader);
}
}

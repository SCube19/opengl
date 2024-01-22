#include "shaderFactory.h"

#include <filesystem>

namespace Real
{
namespace
{
std::shared_ptr<Shader> createFlat()
{
    return std::shared_ptr<Shader>(new Shader(
        std::filesystem::absolute("shaders/flat.vert"),
        std::filesystem::absolute("shaders/flat.frag"),
        std::nullopt));
}

std::shared_ptr<Shader> createGourand()
{
    return std::shared_ptr<Shader>(new Shader(
        std::filesystem::absolute("shaders/gourand.vert"),
        std::filesystem::absolute("shaders/gourand.frag"),
        std::nullopt));
}

std::shared_ptr<Shader> createPhong()
{
    return std::shared_ptr<Shader>(new Shader(
        std::filesystem::absolute("shaders/phong.vert"),
        std::filesystem::absolute("shaders/phong.frag"),
        std::nullopt));
}

std::shared_ptr<Shader> createDefault()
{
    return std::shared_ptr<Shader>(new Shader(
        std::filesystem::absolute("shaders/default.vert"),
        std::filesystem::absolute("shaders/default.frag"),
        std::nullopt));
}

std::shared_ptr<Shader> createShadows()
{
    return std::shared_ptr<Shader>(new Shader(
        std::filesystem::absolute("shaders/shadows.vert"),
        std::filesystem::absolute("shaders/shadows.frag"),
        std::nullopt));
}

std::shared_ptr<Shader> createCubeMap()
{
    return std::shared_ptr<Shader>(new Shader(
        std::filesystem::absolute("shaders/cubeMap.vert"),
        std::filesystem::absolute("shaders/cubeMap.frag"),
        std::filesystem::absolute("shaders/cubeMap.geom")));
}
}

std::shared_ptr<Shader> ShaderFactory::get(ShaderFactory::LightModel model)
{
    switch (model)
    {
    case ShaderFactory::LightModel::FLAT:
        return createFlat();
    case ShaderFactory::LightModel::GOURAND:
        return createGourand();
    case ShaderFactory::LightModel::PHONG:
        return createPhong();
    case ShaderFactory::LightModel::SHADOWS:
        return createShadows();
    case ShaderFactory::LightModel::CUBE_MAP:
        return createCubeMap();
    default:
        return createDefault();
    }
}
}

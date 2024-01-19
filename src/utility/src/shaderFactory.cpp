#include "shaderFactory.h"

#include <filesystem>

namespace Real
{
namespace
{
std::unique_ptr<Shader> createFlat()
{
    return std::unique_ptr<Shader>(new Shader(
        std::filesystem::absolute("shaders/flat.vert"),
        std::filesystem::absolute("shaders/flat.frag")));
}

std::unique_ptr<Shader> createGourand()
{
    return std::unique_ptr<Shader>(new Shader(
        std::filesystem::absolute("shaders/gourand.vert"),
        std::filesystem::absolute("shaders/gourand.frag")));
}

std::unique_ptr<Shader> createPhong()
{
    return std::unique_ptr<Shader>(new Shader(
        std::filesystem::absolute("shaders/phong.vert"),
        std::filesystem::absolute("shaders/phong.frag")));
}

std::unique_ptr<Shader> createDefault()
{
    return std::unique_ptr<Shader>(new Shader(
        std::filesystem::absolute("shaders/default.vert"),
        std::filesystem::absolute("shaders/default.frag")));
}
}

std::unique_ptr<Shader> ShaderFactory::get(ShaderFactory::LightModel model)
{
    switch (model)
    {
    case ShaderFactory::LightModel::FLAT:
        return createFlat();
    case ShaderFactory::LightModel::GOURAND:
        return createGourand();
    case ShaderFactory::LightModel::PHONG:
        return createPhong();
    default:
        return createDefault();
    }
}
}

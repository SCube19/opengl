#pragma once

#include "shader.h"

#include <memory>

namespace Real
{
class ShaderFactory
{

public:
    enum class LightModel
    {
        FLAT,
        GOURAND,
        PHONG,
        NONE
    };
    static std::unique_ptr<Shader> get(LightModel model);

};
} // namespace Real

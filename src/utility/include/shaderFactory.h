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
        SHADOWS,
        CUBE_MAP,
        NONE
    };
    static std::shared_ptr<Shader> get(LightModel model);

};
} // namespace Real

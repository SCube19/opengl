#include "VAOFactory.h"

namespace Real
{
std::shared_ptr<VAO> VAOFactory::get(VAOFactory::Shape shape)
{
    return VAOFactory::models[static_cast<int>(shape)];
}
}

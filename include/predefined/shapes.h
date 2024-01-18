#include <GLFW/glfw3.h>
#include <vector>

using model_3d = std::pair<std::vector<GLfloat>, std::vector<GLuint>>;

namespace Real::Shapes
{
extern model_3d CUBE;

extern model_3d D8;
}
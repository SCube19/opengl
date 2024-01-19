#include <GLFW/glfw3.h>
#include <vector>


namespace Real::Shapes
{
using model_3d = std::pair<std::vector<GLfloat>, std::vector<GLuint>>;

extern model_3d CUBE;

extern model_3d D8;

extern model_3d PLANE;

extern model_3d PYRAMID;
}
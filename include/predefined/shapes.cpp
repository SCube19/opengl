#include "shapes.h"

namespace Real::Shapes
{
model_3d CUBE = {
{
    -0.01f, -0.01f,  0.01f,
    -0.01f, -0.01f, -0.01f,
     0.01f, -0.01f, -0.01f,
     0.01f, -0.01f,  0.01f,
    -0.01f,  0.01f,  0.01f,
    -0.01f,  0.01f, -0.01f,
     0.01f,  0.01f, -0.01f,
     0.01f,  0.01f,  0.01f
},
{	0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7}
};

model_3d D8 = {
{
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -1.0f, 1.0f,  0.0f, // Left Side
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -1.0f, 1.0f,  0.0f, // Left Side
     0.0f, 0.5f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -1.0f, 1.0f,  0.0f, // Left Side

    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 1.0f, -1.0f, // Non-facing side
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 1.0f, -1.0f, // Non-facing side
     0.0f, 0.5f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 1.0f, -1.0f, // Non-facing side

     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      1.0f, 1.0f,  0.0f, // Right side
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      1.0f, 1.0f,  0.0f, // Right side
     0.0f, 0.5f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      1.0f, 1.0f,  0.0f, // Right side

     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 1.0f,  1.0f, // Facing side
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 1.0f,  1.0f, // Facing side
     0.0f, 0.5f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 1.0f,  1.0f,  // Facing side

    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      -1.0f, -1.0f,  0.0f, // Left Side Down
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      -1.0f, -1.0f,  0.0f, // Left Side Down
     0.0f, -0.5f,  0.0f,    0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      -1.0f, -1.0f,  0.0f, // Left Side Down

    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, -1.0f, // Non-facing side Down
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, -1.0f, -1.0f, // Non-facing side Down
     0.0f, -0.5f,  0.0f,    0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, -1.0f, -1.0f, // Non-facing side Down

     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      1.0f, -1.0f,  0.0f, // Right side Down
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      1.0f, -1.0f,  0.0f, // Right side Down
     0.0f, -0.5f,  0.0f,    0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      1.0f, -1.0f,  0.0f, // Right side Down

     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f,  1.0f, // Facing side Down
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f,  1.0f, // Facing side Down
     0.0f, -0.5f,  0.0f,    0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, -1.0f,  1.0f  // Facing side Down
},
{
    0, 1, 2, // Left side
    3, 4, 5, // Non-facing side
    6, 7, 8, // Right side
    9, 10, 11, // Facing side
    12, 13, 14, // left down
    15, 16, 17, // non-facing down
    18, 19, 20, // right down
    21, 22, 23 // facing down
}
};
}
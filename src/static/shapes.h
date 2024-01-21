#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include "vertex.h"

namespace Real
{
using model_3d = std::pair<std::vector<Vertex>, std::vector<GLuint>>;

class Shapes {
public:
    inline static const model_3d CUBE = {
    {
        Vertex{Vertex::Position(-0.2f, -0.2f,  0.2f), Vertex::Color(1.0f), Vertex::UV(.0f), Vertex::Normal(-0.01f, -0.01f,  0.01f)},
        Vertex{Vertex::Position(-0.2f, -0.2f, -0.2f), Vertex::Color(1.0f), Vertex::UV(.0f), Vertex::Normal(-0.01f, -0.01f, -0.01f)},
        Vertex{Vertex::Position(0.2f, -0.2f, -0.2f), Vertex::Color(1.0f), Vertex::UV(.0f), Vertex::Normal(0.01f, -0.01f, -0.01f)},
        Vertex{Vertex::Position(0.2f, -0.2f,  0.2f), Vertex::Color(1.0f), Vertex::UV(.0f), Vertex::Normal(0.01f, -0.01f,  0.01f)},
        Vertex{Vertex::Position(-0.2f,  0.2f,  0.2f), Vertex::Color(1.0f), Vertex::UV(.0f), Vertex::Normal(-0.01f,  0.01f,  0.01f)},
        Vertex{Vertex::Position(-0.2f,  0.2f, -0.2f), Vertex::Color(1.0f), Vertex::UV(.0f), Vertex::Normal(-0.01f,  0.01f, -0.01f)},
        Vertex{Vertex::Position(0.2f,  0.2f, -0.2f), Vertex::Color(1.0f), Vertex::UV(.0f), Vertex::Normal(0.01f,  0.01f, -0.01f)},
        Vertex{Vertex::Position(0.2f,  0.2f,  0.2f), Vertex::Color(1.0f), Vertex::UV(.0f), Vertex::Normal(0.01f,  0.01f,  0.01f)}
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

    inline static const model_3d SMALL_CUBE = {
    {
        Vertex{Vertex::Position(-0.01f, -0.01f,  0.01f), Vertex::Color(1.0f), Vertex::UV(.0f), Vertex::Normal(-0.01f, -0.01f,  0.01f)},
        Vertex{Vertex::Position(-0.01f, -0.01f, -0.01f), Vertex::Color(1.0f), Vertex::UV(.0f), Vertex::Normal(-0.01f, -0.01f, -0.01f)},
        Vertex{Vertex::Position(0.01f, -0.01f, -0.01f), Vertex::Color(1.0f), Vertex::UV(.0f), Vertex::Normal(0.01f, -0.01f, -0.01f)},
        Vertex{Vertex::Position(0.01f, -0.01f,  0.01f), Vertex::Color(1.0f), Vertex::UV(.0f), Vertex::Normal(0.01f, -0.01f,  0.01f)},
        Vertex{Vertex::Position(-0.01f,  0.01f,  0.01f), Vertex::Color(1.0f), Vertex::UV(.0f), Vertex::Normal(-0.01f,  0.01f,  0.01f)},
        Vertex{Vertex::Position(-0.01f,  0.01f, -0.01f), Vertex::Color(1.0f), Vertex::UV(.0f), Vertex::Normal(-0.01f,  0.01f, -0.01f)},
        Vertex{Vertex::Position(0.01f,  0.01f, -0.01f), Vertex::Color(1.0f), Vertex::UV(.0f), Vertex::Normal(0.01f,  0.01f, -0.01f)},
        Vertex{Vertex::Position(0.01f,  0.01f,  0.01f), Vertex::Color(1.0f), Vertex::UV(.0f), Vertex::Normal(0.01f,  0.01f,  0.01f)}
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

    inline static const model_3d D8 = {
    {
        Vertex{Vertex::Position(-0.5f, 0.0f,  0.5f),   Vertex::Color(0.83f, 0.70f, 0.44f),  Vertex::UV(0.0f, 0.0f),      Vertex::Normal(-1.0f, 1.0f,  0.0f)}, // Left Side
        Vertex{Vertex::Position(-0.5f, 0.0f, -0.5f),   Vertex::Color(0.83f, 0.70f, 0.44f),  Vertex::UV(5.0f, 0.0f),      Vertex::Normal(-1.0f, 1.0f,  0.0f)}, // Left Side
        Vertex{Vertex::Position(0.0f, 0.5f,  0.0f),    Vertex::Color(0.92f, 0.86f, 0.76f),  Vertex::UV(2.5f, 5.0f),      Vertex::Normal(-1.0f, 1.0f,  0.0f)}, // Left Side
        Vertex{Vertex::Position(-0.5f, 0.0f, -0.5f),   Vertex::Color(0.83f, 0.70f, 0.44f),  Vertex::UV(5.0f, 0.0f),      Vertex::Normal(0.0f, 1.0f, -1.0f)}, // Non-facing side
        Vertex{Vertex::Position(0.5f, 0.0f, -0.5f),    Vertex::Color(0.83f, 0.70f, 0.44f),  Vertex::UV(0.0f, 0.0f),      Vertex::Normal(0.0f, 1.0f, -1.0f)}, // Non-facing side
        Vertex{Vertex::Position(0.0f, 0.5f,  0.0f),    Vertex::Color(0.92f, 0.86f, 0.76f),  Vertex::UV(2.5f, 5.0f),      Vertex::Normal(0.0f, 1.0f, -1.0f)}, // Non-facing side
        Vertex{Vertex::Position(0.5f, 0.0f, -0.5f),    Vertex::Color(0.83f, 0.70f, 0.44f),  Vertex::UV(0.0f, 0.0f),      Vertex::Normal(1.0f, 1.0f,  0.0f)}, // Right side
        Vertex{Vertex::Position(0.5f, 0.0f,  0.5f),    Vertex::Color(0.83f, 0.70f, 0.44f),  Vertex::UV(5.0f, 0.0f),      Vertex::Normal(1.0f, 1.0f,  0.0f)}, // Right side
        Vertex{Vertex::Position(0.0f, 0.5f,  0.0f),    Vertex::Color(0.92f, 0.86f, 0.76f),  Vertex::UV(2.5f, 5.0f),      Vertex::Normal(1.0f, 1.0f,  0.0f)}, // Right side
        Vertex{Vertex::Position(0.5f, 0.0f,  0.5f),    Vertex::Color(0.83f, 0.70f, 0.44f),  Vertex::UV(5.0f, 0.0f),      Vertex::Normal(0.0f, 1.0f,  1.0f)}, // Facing side
        Vertex{Vertex::Position(-0.5f, 0.0f,  0.5f),   Vertex::Color(0.83f, 0.70f, 0.44f),  Vertex::UV(0.0f, 0.0f),      Vertex::Normal(0.0f, 1.0f,  1.0f)}, // Facing side
        Vertex{Vertex::Position(0.0f, 0.5f,  0.0f),    Vertex::Color(0.92f, 0.86f, 0.76f),  Vertex::UV(2.5f, 5.0f),      Vertex::Normal(0.0f, 1.0f,  1.0f)},  // Facing side
        Vertex{Vertex::Position(-0.5f, 0.0f,  0.5f),   Vertex::Color(0.83f, 0.70f, 0.44f),  Vertex::UV(0.0f, 0.0f),      Vertex::Normal(-1.0f, -1.0f,  0.0f)}, // Left Side Down
        Vertex{Vertex::Position(-0.5f, 0.0f, -0.5f),   Vertex::Color(0.83f, 0.70f, 0.44f),  Vertex::UV(5.0f, 0.0f),      Vertex::Normal(-1.0f, -1.0f,  0.0f)}, // Left Side Down
        Vertex{Vertex::Position(0.0f, -0.5f, 0.0f),    Vertex::Color(0.92f, 0.86f, 0.76f),  Vertex::UV(2.5f, 5.0f),      Vertex::Normal(-1.0f, -1.0f,  0.0f)}, // Left Side Down
        Vertex{Vertex::Position(-0.5f, 0.0f, -0.5f),   Vertex::Color(0.83f, 0.70f, 0.44f),  Vertex::UV(5.0f, 0.0f),      Vertex::Normal(0.0f, -1.0f, -1.0f)}, // Non-facing side Down
        Vertex{Vertex::Position(0.5f, 0.0f, -0.5f),    Vertex::Color(0.83f, 0.70f, 0.44f),  Vertex::UV(0.0f, 0.0f),      Vertex::Normal(0.0f, -1.0f, -1.0f)}, // Non-facing side Down
        Vertex{Vertex::Position(0.0f, -0.5f, 0.0f),    Vertex::Color(0.92f, 0.86f, 0.76f),  Vertex::UV(2.5f, 5.0f),      Vertex::Normal(0.0f, -1.0f, -1.0f)}, // Non-facing side Down
        Vertex{Vertex::Position(0.5f, 0.0f, -0.5f),    Vertex::Color(0.83f, 0.70f, 0.44f),  Vertex::UV(0.0f, 0.0f),      Vertex::Normal(1.0f, -1.0f,  0.0f)}, // Right side Down
        Vertex{Vertex::Position(0.5f, 0.0f,  0.5f),    Vertex::Color(0.83f, 0.70f, 0.44f),  Vertex::UV(5.0f, 0.0f),      Vertex::Normal(1.0f, -1.0f,  0.0f)}, // Right side Down
        Vertex{Vertex::Position(0.0f, -0.5f, 0.0f),    Vertex::Color(0.92f, 0.86f, 0.76f),  Vertex::UV(2.5f, 5.0f),      Vertex::Normal(1.0f, -1.0f,  0.0f)}, // Right side Down
        Vertex{Vertex::Position(0.5f, 0.0f,  0.5f),    Vertex::Color(0.83f, 0.70f, 0.44f),  Vertex::UV(5.0f, 0.0f),      Vertex::Normal(0.0f, -1.0f,  1.0f)}, // Facing side Down
        Vertex{Vertex::Position(-0.5f, 0.0f,  0.5f),   Vertex::Color(0.83f, 0.70f, 0.44f),  Vertex::UV(0.0f, 0.0f),      Vertex::Normal(0.0f, -1.0f,  1.0f)}, // Facing side Down
        Vertex{Vertex::Position(0.0f, -0.5f, 0.0f),    Vertex::Color(0.92f, 0.86f, 0.76f),  Vertex::UV(2.5f, 5.0f),      Vertex::Normal(0.0f, -1.0f,  1.0f)}  // Facing side Down
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

    inline static const model_3d PLANE = {
    {
        Vertex{Vertex::Position(-1.0f, 0.0f,  1.0f),	Vertex::Color(0.0f, 0.0f, 0.0f),		Vertex::UV(0.0f, 0.0f),		Vertex::Normal(0.0f, 1.0f, 0.0f)},
        Vertex{Vertex::Position(-1.0f, 0.0f, -1.0f),	Vertex::Color(0.0f, 0.0f, 0.0f),		Vertex::UV(0.0f, 1.0f),		Vertex::Normal(0.0f, 1.0f, 0.0f)},
        Vertex{Vertex::Position(1.0f, 0.0f, -1.0f),		Vertex::Color(0.0f, 0.0f, 0.0f),		Vertex::UV(1.0f, 1.0f),		Vertex::Normal(0.0f, 1.0f, 0.0f)},
        Vertex{Vertex::Position(1.0f, 0.0f,  1.0f),		Vertex::Color(0.0f, 0.0f, 0.0f),		Vertex::UV(1.0f, 0.0f),		Vertex::Normal(0.0f, 1.0f, 0.0f)}
    },
    {
        0, 1, 2,
        0, 2, 3
    }
    };

    inline static const model_3d PYRAMID = { {
        Vertex{Vertex::Position(-0.5f, 0.0f,  0.5f),    Vertex::Color(0.83f, 0.70f, 0.44f),  Vertex::UV(0.0f, 0.0f),     Vertex::Normal(0.0f, -1.0f, 0.0f)}, // Bottom side
        Vertex{Vertex::Position(-0.5f, 0.0f, -0.5f),    Vertex::Color(0.83f, 0.70f, 0.44f),	 Vertex::UV(0.0f, 5.0f),     Vertex::Normal(0.0f, -1.0f, 0.0f)}, // Bottom side
        Vertex{Vertex::Position(0.5f, 0.0f, -0.5f),    Vertex::Color(0.83f, 0.70f, 0.44f),	 Vertex::UV(5.0f, 5.0f),     Vertex::Normal(0.0f, -1.0f, 0.0f)}, // Bottom side
        Vertex{Vertex::Position(0.5f, 0.0f,  0.5f),    Vertex::Color(0.83f, 0.70f, 0.44f),	 Vertex::UV(5.0f, 0.0f),     Vertex::Normal(0.0f, -1.0f, 0.0f)}, // Bottom side
        Vertex{Vertex::Position(-0.5f, 0.0f,  0.5f),    Vertex::Color(0.83f, 0.70f, 0.44f),  Vertex::UV(0.0f, 0.0f),     Vertex::Normal(-0.8f, 0.5f,  0.0f)}, // Left Side
        Vertex{Vertex::Position(-0.5f, 0.0f, -0.5f),    Vertex::Color(0.83f, 0.70f, 0.44f),	 Vertex::UV(5.0f, 0.0f),     Vertex::Normal(-0.8f, 0.5f,  0.0f)}, // Left Side
        Vertex{Vertex::Position(0.0f, 0.8f,  0.0f),    Vertex::Color(0.92f, 0.86f, 0.76f),	 Vertex::UV(2.5f, 5.0f),     Vertex::Normal(-0.8f, 0.5f,  0.0f)}, // Left Side
        Vertex{Vertex::Position(-0.5f, 0.0f, -0.5f),    Vertex::Color(0.83f, 0.70f, 0.44f),	 Vertex::UV(5.0f, 0.0f),     Vertex::Normal(0.0f, 0.5f, -0.8f)}, // Non-facing side
        Vertex{Vertex::Position(0.5f, 0.0f, -0.5f),    Vertex::Color(0.83f, 0.70f, 0.44f),	 Vertex::UV(0.0f, 0.0f),     Vertex::Normal(0.0f, 0.5f, -0.8f)}, // Non-facing side
        Vertex{Vertex::Position(0.0f, 0.8f,  0.0f),    Vertex::Color(0.92f, 0.86f, 0.76f),	 Vertex::UV(2.5f, 5.0f),     Vertex::Normal(0.0f, 0.5f, -0.8f)}, // Non-facing side
        Vertex{Vertex::Position(0.5f, 0.0f, -0.5f),    Vertex::Color(0.83f, 0.70f, 0.44f),	 Vertex::UV(0.0f, 0.0f),     Vertex::Normal(0.8f, 0.5f,  0.0f)}, // Right side
        Vertex{Vertex::Position(0.5f, 0.0f,  0.5f),    Vertex::Color(0.83f, 0.70f, 0.44f),	 Vertex::UV(5.0f, 0.0f),     Vertex::Normal(0.8f, 0.5f,  0.0f)}, // Right side
        Vertex{Vertex::Position(0.0f, 0.8f,  0.0f),    Vertex::Color(0.92f, 0.86f, 0.76f),	 Vertex::UV(2.5f, 5.0f),     Vertex::Normal(0.8f, 0.5f,  0.0f)}, // Right side
        Vertex{Vertex::Position(0.5f, 0.0f,  0.5f),    Vertex::Color(0.83f, 0.70f, 0.44f),	 Vertex::UV(5.0f, 0.0f),     Vertex::Normal(0.0f, 0.5f,  0.8f)}, // Facing side
        Vertex{Vertex::Position(-0.5f, 0.0f,  0.5f),    Vertex::Color(0.83f, 0.70f, 0.44f),  Vertex::UV(0.0f, 0.0f),     Vertex::Normal(0.0f, 0.5f,  0.8f)}, // Facing side
        Vertex{Vertex::Position(0.0f, 0.8f,  0.0f),    Vertex::Color(0.92f, 0.86f, 0.76f),	 Vertex::UV(2.5f, 5.0f),     Vertex::Normal(0.0f, 0.5f,  0.8f)}  // Facing side
    },
    {
        0, 1, 2, // Bottom side
        0, 2, 3, // Bottom side
        4, 6, 5, // Left side
        7, 9, 8, // Non-facing side
        10, 12, 11, // Right side
        13, 15, 14 // Facing side
    } };
};
}
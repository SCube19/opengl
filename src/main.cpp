#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "uniforms/uniforms.h"

#include <math.h>
#include <filesystem>
#include <random>
#include <chrono>
#include <optional>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shader.h"
#include "window.h"
#include "texture.h"
#include "camera.h"
#include "model.h"
#include "light.h"
#include "textureSet.h"

// Vertices coordinates
std::vector<GLfloat> vertices =
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
};

// Indices for vertices order
std::vector<GLuint> indices =
{
    0, 1, 2, // Left side
    3, 4, 5, // Non-facing side
    6, 7, 8, // Right side
    9, 10, 11, // Facing side
    12, 13, 14, // left down
    15, 16, 17, // non-facing down
    18, 19, 20, // right down
    21, 22, 23 // facing down
};


using model_3d = std::pair<std::vector<GLfloat>, std::vector<GLuint>>;

model_3d cube = {
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

int main()
{
    // Initialize GLFW
    glfwInit();

    Real::Window window({ 800, 800 }, "Real Engine");


    Real::Camera::getInstace()
        .setPosition(glm::vec3(0.0f, 0.0f, 2.0f)).
        setSpeed(2.0f)
        .setSize(window.getSize())
        .setWindow(window);

    glEnable(GL_DEPTH_TEST);
    {
        Real::Shader shader(
            std::filesystem::absolute("shaders/default.vert"),
            std::filesystem::absolute("shaders/default.frag"));

        Real::Shader lightShader(
            std::filesystem::absolute("shaders/light.vert"),
            std::filesystem::absolute("shaders/light.frag")
        );

        Real::VAO vao;
        Real::VAO cubevao;

        vao.fromVectors(vertices, indices, {
            0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0
            });
        cubevao.fromVectors(cube.first, cube.second, {
            0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0
            });

        vao.linkAttrib({
            1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float))
            });
        vao.linkAttrib({
            2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float))
            });
        vao.linkAttrib({
            3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float))
            });
        std::unique_ptr<Real::Texture> popcat = std::make_unique<Real::Texture>(std::filesystem::absolute("textures/planks.png"), GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
        std::unique_ptr<Real::Texture> specular = std::make_unique<Real::Texture>(std::filesystem::absolute("textures/planksSpec.png"), GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);

        Real::TextureSet textures(std::move(popcat), std::move(specular));

        Real::Light light(
            glm::vec3(0.5f, 0.5f, 0.5f),
            cubevao,
            lightShader,
            glm::vec4(1.0f)
        );

        Real::Model pyramid(glm::vec3(0.0f, 0.0f, 0.0f), vao, shader, textures);

        pyramid.applyLight(light, "lightPos", "lightColor");

        // Main while loop
        while (!glfwWindowShouldClose(&window))
        {
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            pyramid.draw();

            light.draw();

            glfwSwapBuffers(&window);

            glfwPollEvents();

            Real::Camera::getInstace().handleInput();
        }
    }

    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}
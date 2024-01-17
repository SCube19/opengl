#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>
#include <filesystem>
#include <random>
#include <chrono>


#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shader.h"
#include "window.h"
#include "texture.h"
#include "camera.h"

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
        Real::Texture popcat(std::filesystem::absolute("textures/brick.jpg"), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
        popcat.bindShader(shader, "tex0");

        glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, lightPos);

        glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::mat4 pyramidModel = glm::mat4(1.0f);
        pyramidModel = glm::translate(pyramidModel, pyramidPos);

        lightShader.setUniformMatrix(glUniformMatrix4fv, "model", 1, GL_FALSE, glm::value_ptr(lightModel));
        shader.setUniformMatrix(glUniformMatrix4fv, "model", 1, GL_FALSE, glm::value_ptr(pyramidModel));

        lightShader.setUniform("lightColor", lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        shader.setUniform("lightColor", lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        shader.setUniform("lightPos", lightPos.x, lightPos.y, lightPos.z);


        std::mt19937_64 rng;
        // initialize the random number generator with time-dependent seed
        uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
        rng.seed(ss);
        // initialize a uniform distribution between 0 and 1
        std::uniform_real_distribution<double> unif(0.3f, 2);

        double prevTime = glfwGetTime();

        // Main while loop
        while (!glfwWindowShouldClose(&window))
        {
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            double currTime = glfwGetTime();
            if (currTime - prevTime >= 1 / 30)
            {
                pyramidModel = glm::rotate(pyramidModel, glm::radians(2.0f), glm::vec3(unif(rng), unif(rng), unif(rng)));
                shader.setUniformMatrix(glUniformMatrix4fv, "model", 1, GL_FALSE, glm::value_ptr(pyramidModel));
            }
            shader.use();

            Real::Camera::getInstace().project(shader, "camera");

            popcat.bind();

            vao.draw();

            lightShader.use();
            Real::Camera::getInstace().project(lightShader, "camera");
            cubevao.draw();

            glfwSwapBuffers(&window);

            glfwPollEvents();

            Real::Camera::getInstace().handleInput();
        }
    }

    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}
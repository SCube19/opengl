#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>
#include <filesystem>

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
    //COORDS                //COLORS            //TEXTURES
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
std::vector<GLuint> indices =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};


int main()
{
    // Initialize GLFW
    glfwInit();

    Real::Window window({ 800, 800 }, "Real Engine");
    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, 800, 800);

    Real::Camera::getInstace().setPosition(glm::vec3(0.0f, 0.0f, 2.0f)).setSpeed(0.05f);

    glEnable(GL_DEPTH_TEST);
    {
        Real::Shader shader(
            std::filesystem::absolute("shaders/default.vert"),
            std::filesystem::absolute("shaders/default.frag"));

        Real::VAO vao;
        vao.fromVectors(vertices, indices, {
            0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0
            });
        vao.linkAttrib({
            1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float))
            });
        vao.linkAttrib({
            2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float))
            });

        Real::Texture popcat(std::filesystem::absolute("textures/brick.jpg"), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
        popcat.bindShader(shader, "tex0");

        // Main while loop
        while (!glfwWindowShouldClose(&window))
        {
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader.use();

            Real::Camera::getInstace().handleInput(window);
            Real::Camera::getInstace().project(shader, "camera");

            popcat.bind();

            vao.bind();

            glDrawElements(GL_TRIANGLES, vao.getNumberOfVertices(), GL_UNSIGNED_INT, 0);

            glfwSwapBuffers(&window);

            glfwPollEvents();
        }
    }

    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}
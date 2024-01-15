#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <math.h>
#include <filesystem>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shader.h"
#include "window.h"
#include "texture.h"

// Vertices coordinates
std::vector<GLfloat> vertices =
{
    //COORDS                //COLORS            //TEXTURES
 -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
    -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
     0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
     0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

// Indices for vertices order
std::vector<GLuint> indices =
{
    0, 2, 1, // Upper triangle
    0, 3, 2 // Lower triangle
};


int main()
{
    // Initialize GLFW
    glfwInit();

    Real::Window window({ 800, 800 }, "Real Engine");
    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, 800, 800);

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

        Real::Texture popcat(std::filesystem::absolute("textures/popcat.png"), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
        popcat.bindShader(shader, "tex0");

        // Main while loop
        while (!glfwWindowShouldClose(&window))
        {
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

            glClear(GL_COLOR_BUFFER_BIT);

            shader.use();

            shader.setUniform<GLfloat>("scale", 0.5f);

            popcat.bind();

            vao.bind();

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glfwSwapBuffers(&window);

            glfwPollEvents();
        }
    }

    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}
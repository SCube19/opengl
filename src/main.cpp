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
#include "VAOFactory.h"

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

        std::unique_ptr<Real::VAO> vao = Real::VAOFactory::get(Real::VAOFactory::Shape::D8);

        std::unique_ptr<Real::Texture> popcat =
            std::make_unique<Real::Texture>(std::filesystem::absolute("textures/planks.png"), Real::Texture::Type::DIFFUSE, 0);
        std::unique_ptr<Real::Texture> specular =
            std::make_unique<Real::Texture>(std::filesystem::absolute("textures/planksSpec.png"), Real::Texture::Type::SPECULAR, 1);

        Real::TextureSet textures(std::move(popcat), std::move(specular));

        Real::Light light(
            Real::Light::Type::SPOTLIGHT,
            glm::vec3(0.3f, 0.7f, 0.7f),
            lightShader,
            glm::vec4(1.0f),
            1.0f,
            Real::Light::SpotlightParameters{
                direction: glm::vec3(1.0f, 1.0f, 1.0f),
                inner : 0.03f,
                outer : 0.10f,
            }
        );

        Real::Model pyramid(glm::vec3(0.0f, 0.0f, 0.0f), std::move(vao), shader, textures);

        light.applyLight(pyramid);

        // Main while loop
        while (!glfwWindowShouldClose(&window))
        {
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            shader.use();

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
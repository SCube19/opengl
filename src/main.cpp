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
#include "lightManager.h"

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
        std::unique_ptr<Real::Shader> shader(
            new Real::Shader(
                std::filesystem::absolute("shaders/default.vert"),
                std::filesystem::absolute("shaders/default.frag")));

        std::unique_ptr<Real::Shader> shader2(
            new Real::Shader(
                std::filesystem::absolute("shaders/default.vert"),
                std::filesystem::absolute("shaders/default.frag")));

        std::unique_ptr<Real::Shader> shader3(
            new Real::Shader(
                std::filesystem::absolute("shaders/default.vert"),
                std::filesystem::absolute("shaders/default.frag")));

        std::unique_ptr<Real::Shader> lightShader(
            new Real::Shader(
                std::filesystem::absolute("shaders/light.vert"),
                std::filesystem::absolute("shaders/light.frag")));

        std::unique_ptr<Real::Shader> lightShader2(
            new Real::Shader(
                std::filesystem::absolute("shaders/light.vert"),
                std::filesystem::absolute("shaders/light.frag")));

        std::unique_ptr<Real::Shader> lightShader3(
            new Real::Shader(
                std::filesystem::absolute("shaders/light.vert"),
                std::filesystem::absolute("shaders/light.frag")));

        std::unique_ptr<Real::Shader> lightShader4(
            new Real::Shader(
                std::filesystem::absolute("shaders/light.vert"),
                std::filesystem::absolute("shaders/light.frag")));


        std::unique_ptr<Real::VAO> vao = Real::VAOFactory::get(Real::VAOFactory::Shape::D8);
        std::unique_ptr<Real::VAO> plane = Real::VAOFactory::get(Real::VAOFactory::Shape::PLANE);
        std::unique_ptr<Real::VAO> plane2 = Real::VAOFactory::get(Real::VAOFactory::Shape::PLANE);

        std::shared_ptr<Real::Texture> popcat =
            std::make_unique<Real::Texture>(std::filesystem::absolute("textures/planks.png"), Real::Texture::Type::DIFFUSE, 0);
        std::shared_ptr<Real::Texture> specular =
            std::make_unique<Real::Texture>(std::filesystem::absolute("textures/planksSpec.png"), Real::Texture::Type::SPECULAR, 1);

        Real::TextureSet textures(popcat, specular);

        std::unique_ptr<Real::Light> light(new Real::Light(
            Real::Light::Type::DIRECTIONAL,
            glm::vec3(.0f, 1.0f, .0f),
            std::move(lightShader),
            glm::vec4(1.0f),
            1.0f,
            Real::Light::DirectionalParameters{
                direction: glm::vec3(-1.5f, -1.0f, -1.0f)
            }
        ));

        std::unique_ptr<Real::Light> light2(new Real::Light(
            Real::Light::Type::SPOTLIGHT,
            glm::vec3(0.0f, 1.0f, .0f),
            std::move(lightShader2),
            glm::vec4(1.0f),
            5.5f,
            Real::Light::SpotlightParameters{
                direction: glm::vec3(0.0f, -1.0f, 0.0f),
                inner : 0.99f,
                outer : 0.97f,
            }
        ));

        std::unique_ptr<Real::Light> light3(new Real::Light(
            Real::Light::Type::POINT,
            glm::vec3(-5.0f, 0.1f, 0.2f),
            std::move(lightShader3),
            glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
            2.0f,
            Real::Light::PointParameters{
                falloff: glm::vec2(3.0f, 0.7f)
            }
        ));

        std::unique_ptr<Real::Light> light4(new Real::Light(
            Real::Light::Type::POINT,
            glm::vec3(-0.5f, 0.2f, .0f),
            std::move(lightShader4),
            glm::vec4(1.0f),
            7.0f,
            Real::Light::PointParameters{
                falloff: glm::vec2(3.0f, 0.7f)
            }
        ));

        Real::Model pyramid(glm::vec3(0.0f, 0.0f, 0.0f), std::move(vao), std::move(shader), textures);
        Real::Model plank(glm::vec3(0.0f, 0.0f, 0.0f), std::move(plane), std::move(shader2), textures);
        Real::Model plank2(glm::vec3(-2.0f, 0.0f, 0.0f), std::move(plane2), std::move(shader3), textures);
        Real::LightManager::getInstance().addLight(std::move(light));
        Real::LightManager::getInstance().addLight(std::move(light2));
        Real::LightManager::getInstance().addLight(std::move(light3));
        Real::LightManager::getInstance().addLight(std::move(light4));

        // plank.rotate(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        plank2.rotate(-90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        pyramid.rotate(203.0f, glm::vec3(1.0f, 1.0f, 0.0f));

        Real::LightManager::getInstance().applyLight(pyramid.getShader());
        Real::LightManager::getInstance().applyLight(plank.getShader());
        Real::LightManager::getInstance().applyLight(plank2.getShader());
        // Main while loop
        while (!glfwWindowShouldClose(&window))
        {
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            pyramid.draw();
            plank.draw();
            plank2.draw();

            Real::LightManager::getInstance().draw();

            glfwSwapBuffers(&window);

            glfwPollEvents();

            Real::Camera::getInstace().handleInput();
        }
    }

    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}
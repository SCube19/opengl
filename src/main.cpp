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
#include <optional>
#include <iostream>
#include <ranges>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shader.h"
#include "window.h"
#include "texture.h"
#include "camera.h"
#include "model.h"
#include "light.h"
#include "VAOFactory.h"
#include "lightManager.h"
#include "shaderFactory.h"
#include "mesh.h"

using namespace Real;

void renderQuad();

float rectangleVertices[] =
{
    //  Coords   // texCoords
     1.0f, -1.0f,  1.0f, 0.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
    -1.0f,  1.0f,  0.0f, 1.0f,

     1.0f,  1.0f,  1.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f,  0.0f, 1.0f
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
    //glEnable(GL_FRAMEBUFFER_SRGB);
    {

        std::shared_ptr<Real::Shader> shaderFlat(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::FLAT));
        std::shared_ptr<Real::Shader> shaderGourand(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::GOURAND));
        std::shared_ptr<Real::Shader> shaderPhong(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::PHONG));
        std::shared_ptr<Real::Shader> shaderNone(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::NONE));
        std::shared_ptr<Real::Shader> shaderShadows(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::SHADOWS));
        std::shared_ptr<Real::Shader> shaderCubeMap(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::CUBE_MAP));
        std::shared_ptr<Real::Shader> shaderFramebuffer(new Shader("shaders/framebuffer.vert", "shaders/framebuffer.frag", std::nullopt));

        std::shared_ptr<Real::Texture> popcat =
            std::make_unique<Real::Texture>(std::filesystem::absolute("textures/planks.png"), Real::Texture::Type::DIFFUSE, 0);
        std::shared_ptr<Real::Texture> specular =
            std::make_unique<Real::Texture>(std::filesystem::absolute("textures/planksSpec.png"), Real::Texture::Type::SPECULAR, 1);

        std::vector<std::shared_ptr<Real::Texture>> textures = { popcat, specular };

        std::unique_ptr<Real::Light> lightTest(new Real::Light(
            Real::Light::Type::DIRECTIONAL,
            glm::vec3(0.0f, 0.0f, .0f),
            glm::vec4(1.0f),
            1.0f,
            Real::Light::DirectionalParameters{
                direction: glm::vec3(0, -1, 0)
            }
        ));

        std::unique_ptr<Real::Light> lightTest2(new Real::Light(
            Real::Light::Type::SPOTLIGHT,
            glm::vec3(0.0f, 1.0f, .0f),
            glm::vec4(1.0f),
            1.0f,
            Real::Light::SpotlightParameters{
                direction: glm::vec3(0.0f, -1.0f, 0.0f),
                inner : 0.95f,
                outer : 0.90f
            }
        ));

        std::unique_ptr<Real::Light> lightTest3(new Real::Light(
            Real::Light::Type::POINT,
            glm::vec3(.0f, 1.0f, .0f),
            glm::vec4(1.0f),
            10.0f,
            Real::Light::PointParameters{
                falloff: glm::vec2(3.0f, 0.7f)
            }
        ));
        // std::unique_ptr<Real::Light> lightTest4(new Real::Light(
        //     Real::Light::Type::POINT,
        //     glm::vec3(-.2f, 1.0f, .0f),
        //     glm::vec4(1.0f),
        //     10.0f,
        //     Real::Light::PointParameters{
        //         falloff: glm::vec2(3.0f, 0.7f)
        //     }
        // ));
        std::shared_ptr<Real::Mesh> plank(new Mesh(glm::vec3(0, -1, 0), VAOFactory::get(VAOFactory::Shape::PLANE), textures));
        std::shared_ptr<Real::Model> bunny3(new Model("models/stanford-bunny.obj"));
        std::shared_ptr<Real::Model> bunny2(new Model("models/stanford-bunny.obj"));
        std::shared_ptr<Real::Model> sphere(new Model("models/sphere.obj"));

        bunny3->scale(3.0f);
        bunny2->scale(3.0f);
        bunny2->translate(glm::vec3(-.1f, -.2f, 0));

        LightManager::getInstance().addLight(std::move(lightTest));
        //LightManager::getInstance().addLight(std::move(lightTest2));
        //LightManager::getInstance().addLight(std::move(lightTest3));
        LightManager::getInstance().applyLight(*shaderPhong);
        LightManager::getInstance().applyLight(*shaderFlat);
        LightManager::getInstance().applyLight(*shaderGourand);
        std::vector<std::shared_ptr<Drawable>> drawables = { bunny3, plank, bunny2 };

        Shader& currentShader = *shaderPhong;
        // Main while loop
        while (!glfwWindowShouldClose(&window))
        {
            glEnable(GL_DEPTH_TEST);

            glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            LightManager::getInstance().castShadows(currentShader, window, drawables);
            for (auto& drawable : drawables)
                drawable->draw(currentShader);

            LightManager::getInstance().draw();
            glfwSwapBuffers(&window);

            glfwPollEvents();

            Real::Camera::getInstace().handleInput();
        }
    }

    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}


unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
    if (quadVAO == 0)
    {
        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}
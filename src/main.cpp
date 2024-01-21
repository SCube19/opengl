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

        std::shared_ptr<Real::Shader> shaderFlat(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::FLAT));
        std::shared_ptr<Real::Shader> shaderGourand(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::GOURAND));
        std::shared_ptr<Real::Shader> shaderPhong(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::PHONG));
        std::shared_ptr<Real::Shader> shaderNone(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::NONE));

        std::shared_ptr<Real::Texture> popcat =
            std::make_unique<Real::Texture>(std::filesystem::absolute("textures/planks.png"), Real::Texture::Type::DIFFUSE, 0);
        std::shared_ptr<Real::Texture> specular =
            std::make_unique<Real::Texture>(std::filesystem::absolute("textures/planksSpec.png"), Real::Texture::Type::SPECULAR, 1);

        std::vector<std::shared_ptr<Real::Texture>> textures = { popcat, specular };

        std::unique_ptr<Real::Light> lightTest(new Real::Light(
            Real::Light::Type::POINT,
            glm::vec3(0.0f, 0.0f, .0f),
            glm::vec4(1.0f),
            3.0f,
            Real::Light::PointParameters{
                falloff: glm::vec2(2.0f, 0.7f)
            }
        ));

        lightTest->translate(glm::vec3(3.0f, 0, 2.0f));
        Real::Model bunny("models/sphere.obj");
        Real::Model bunny1("models/sphere.obj");
        Real::Model bunny2("models/sphere.obj");

        bunny.scale(0.3f);
        bunny1.scale(0.3f);
        bunny2.scale(0.3f);
        bunny.translate(glm::vec3(-5.0f, .0f, .0f));
        bunny2.translate(glm::vec3(5.0f, .0f, .0f));

        LightManager::getInstance().addLight(std::move(lightTest));


        double prevTime = glfwGetTime();

        // Main while loop
        while (!glfwWindowShouldClose(&window))
        {
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            double currTime = glfwGetTime();
            if (currTime - prevTime > 1 / 60)
            {
                bunny.rotate(1.0f, glm::vec3(1.0f, 0.5f, -1.0f));
                bunny1.rotate(1.0f, glm::vec3(1.0f, 0.5f, -1.0f));
                bunny2.rotate(1.0f, glm::vec3(1.0f, 0.5f, -1.0f));
                LightManager::getInstance().translateLight(0, glm::vec3(-0.01f, 0, 0));
            }
            Real::LightManager::getInstance().draw();
            LightManager::getInstance().applyLight(*shaderFlat);
            LightManager::getInstance().applyLight(*shaderGourand);
            LightManager::getInstance().applyLight(*shaderPhong);
            bunny.draw(*shaderFlat);
            bunny1.draw(*shaderGourand);
            bunny2.draw(*shaderPhong);


            glfwSwapBuffers(&window);

            glfwPollEvents();

            Real::Camera::getInstace().handleInput();
        }
    }

    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}
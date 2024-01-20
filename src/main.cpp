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
#include "shaderFactory.h"

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

        std::unique_ptr<Real::Shader> shader(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::FLAT));
        std::unique_ptr<Real::Shader> shader2(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::FLAT));
        std::unique_ptr<Real::Shader> shader3(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::FLAT));
        std::unique_ptr<Real::Shader> shaderFlat(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::FLAT));
        std::unique_ptr<Real::Shader> shaderGourand(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::GOURAND));
        std::unique_ptr<Real::Shader> shaderPhong(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::PHONG));

        std::unique_ptr<Real::Shader> shaderCube(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::FLAT));


        std::unique_ptr<Real::Shader> lightShader(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::NONE));
        std::unique_ptr<Real::Shader> lightShader2(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::NONE));
        std::unique_ptr<Real::Shader> lightShader3(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::NONE));
        std::unique_ptr<Real::Shader> lightShader4(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::NONE));

        std::unique_ptr<Real::VAO> vao = Real::VAOFactory::get(Real::VAOFactory::Shape::D8);
        std::unique_ptr<Real::VAO> plane = Real::VAOFactory::get(Real::VAOFactory::Shape::PLANE);
        std::unique_ptr<Real::VAO> plane2 = Real::VAOFactory::get(Real::VAOFactory::Shape::PLANE);
        std::unique_ptr<Real::VAO> planeFlat = Real::VAOFactory::get(Real::VAOFactory::Shape::PYRAMID);
        std::unique_ptr<Real::VAO> planeGourand = Real::VAOFactory::get(Real::VAOFactory::Shape::PYRAMID);
        std::unique_ptr<Real::VAO> planePhong = Real::VAOFactory::get(Real::VAOFactory::Shape::PYRAMID);

        std::unique_ptr<Real::VAO> cubeVAO = Real::VAOFactory::get(Real::VAOFactory::Shape::CUBE);

        std::shared_ptr<Real::Texture> popcat =
            std::make_unique<Real::Texture>(std::filesystem::absolute("textures/planks.png"), Real::Texture::Type::DIFFUSE, 0);
        std::shared_ptr<Real::Texture> specular =
            std::make_unique<Real::Texture>(std::filesystem::absolute("textures/planksSpec.png"), Real::Texture::Type::SPECULAR, 1);

        Real::TextureSet textures(popcat, specular);

        ////////////////////
        std::unique_ptr<Real::Light> lightTest(new Real::Light(
            Real::Light::Type::SPOTLIGHT,
            glm::vec3(0.0f, 0.0f, .0f),
            std::move(lightShader2),
            glm::vec4(1.0f),
            2.0f,
            Real::Light::SpotlightParameters{
                direction: glm::vec3(0.0f, -1.0f, 0.0f),
                inner : 0.7f,
                outer : 0.6f,
            }
        ));
        std::unique_ptr<Real::Light> lightTest2(new Real::Light(
            Real::Light::Type::SPOTLIGHT,
            glm::vec3(0.0f, 0.0f, .0f),
            std::move(lightShader3),
            glm::vec4(1.0f),
            2.0f,
            Real::Light::SpotlightParameters{
                direction: glm::vec3(0.0f, 1.0f, 0.0f),
                inner : 0.99f,
                outer : 0.97f,
            }
        ));
        std::unique_ptr<Real::Light> lightTest3(new Real::Light(
            Real::Light::Type::SPOTLIGHT,
            glm::vec3(0.0f, 0.0f, .0f),
            std::move(lightShader4),
            glm::vec4(1.0f),
            2.0f,
            Real::Light::SpotlightParameters{
                direction: glm::vec3(-1.0f, 0.0f, 0.0f),
                inner : 0.99f,
                outer : 0.97f,
            }
        ));


        // std::unique_ptr<Real::Light> lightTest(new Real::Light(
        //     Real::Light::Type::POINT,
        //     glm::vec3(0.0f, 0.0f, .0f),
        //     std::move(lightShader2),
        //     glm::vec4(1.0f),
        //     7.0f,
        //     Real::Light::PointParameters{
        //         falloff: glm::vec2(2.0f, 0.7f)
        //     }
        // ));
        // std::unique_ptr<Real::Light> lightTest(new Real::Light(
        //     Real::Light::Type::DIRECTIONAL,
        //     glm::vec3(0.0f, 0.0f, .0f),
        //     std::move(lightShader2),
        //     glm::vec4(1.0f),
        //     3.0f,
        //     Real::Light::DirectionalParameters{
        //         direction: glm::vec3(1.0f, -1.0f, 0.0f)
        //     }
        // ));
        Real::Model plank(glm::vec3(0.0f, -1.0f, 0.0f), std::move(planeFlat), std::move(shaderFlat), textures);
        Real::Model plank2(glm::vec3(0.0f, 1.0f, 0.0f), std::move(planeGourand), std::move(shaderGourand), textures);
        Real::Model plank3(glm::vec3(-1.0f, 0.0f, 0.0f), std::move(planePhong), std::move(shaderPhong), textures);

        Real::Model cube(glm::vec3(0.0f, -1.0f, 0.0f), std::move(cubeVAO), std::move(shaderCube), textures);

        //plank.rotate(35.0f, glm::vec3(1.0f, 0.5f, 1.2f));
        plank2.rotate(180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        plank3.rotate(-90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

        LightManager::getInstance().addLight(std::move(lightTest));
        LightManager::getInstance().addLight(std::move(lightTest2));
        LightManager::getInstance().addLight(std::move(lightTest3));
        LightManager::getInstance().applyLight(plank.getShader());
        LightManager::getInstance().applyLight(plank2.getShader());
        LightManager::getInstance().applyLight(plank3.getShader());
        LightManager::getInstance().applyLight(cube.getShader());
        // std::unique_ptr<Real::Light> light5(new Real::Light(
        //     Real::Light::Type::SPOTLIGHT,
        //     glm::vec3(0.0f, 1.0f, .0f),
        //     ShaderFactory::get(ShaderFactory::LightModel::NONE),
        //     glm::vec4(1.0f),
        //     7.0f,
        //     Real::Light::PointParameters{
        //         falloff: glm::vec2(3.0f, 0.7f)
        //     }
        // ));

        // Real::Model pyramid(glm::vec3(0.0f, 0.0f, 0.0f), std::move(vao), std::move(shader), textures);
        // Real::Model plank(glm::vec3(0.0f, -1.0f, 0.0f), std::move(plane), std::move(shader2), textures);
        // Real::Model plank2(glm::vec3(-2.0f, 0.0f, 0.0f), std::move(plane2), std::move(shader3), textures);
        // // Real::LightManager::getInstance().addLight(std::move(light));
        // Real::LightManager::getInstance().addLight(std::move(light2));
        // // Real::LightManager::getInstance().addLight(std::move(light3));
        // // Real::LightManager::getInstance().addLight(std::move(light4));

        // // plank.rotate(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        // plank2.rotate(-90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        // pyramid.rotate(203.0f, glm::vec3(1.0f, 1.0f, 0.0f));

        // Real::LightManager::getInstance().applyLight(pyramid.getShader());
        // Real::LightManager::getInstance().applyLight(plank.getShader());
        // Real::LightManager::getInstance().applyLight(plank2.getShader());


        double prevTime = glfwGetTime();

        // Main while loop
        while (!glfwWindowShouldClose(&window))
        {
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            double currTime = glfwGetTime();
            if (currTime - prevTime > 1 / 60)
            {
                plank.rotate(1.0f, glm::vec3(1.0f, 0.5f, -1.0f));
                plank2.rotate(1.0f, glm::vec3(1.0f, 0.5f, -1.0f));
                plank3.rotate(1.0f, glm::vec3(1.0f, 0.5f, -1.0f));
            }
            plank.draw();
            plank2.draw();
            plank3.draw();

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
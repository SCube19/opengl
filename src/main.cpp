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

    Real::Window window({ 1200, 1200 }, "Real Engine");


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
            std::make_unique<Real::Texture>(std::filesystem::absolute("textures/planks.png"), Real::Texture::Type::DIFFUSE);
        std::shared_ptr<Real::Texture> specular =
            std::make_unique<Real::Texture>(std::filesystem::absolute("textures/planksSpec.png"), Real::Texture::Type::SPECULAR);
        std::shared_ptr<Real::Texture> terrainTex =
            std::make_unique<Real::Texture>(std::filesystem::absolute("textures/rock.png"), Real::Texture::Type::DIFFUSE);
        std::shared_ptr<Real::Texture> pillarTex =
            std::make_unique<Real::Texture>(std::filesystem::absolute("textures/rock2.jpg"), Real::Texture::Type::DIFFUSE);

        std::shared_ptr<Real::Texture> terrainTex2 =
            std::make_unique<Real::Texture>(std::filesystem::absolute("textures/rock.png"), Real::Texture::Type::DIFFUSE);

        std::shared_ptr<Real::Texture> ratTex =
            std::make_unique<Real::Texture>(std::filesystem::absolute("models/rat/mat0_c.jpg"), Real::Texture::Type::DIFFUSE);

        std::vector<std::shared_ptr<Real::Texture>> textures = { terrainTex, specular };

        std::shared_ptr<Real::Light> directional(new Real::Light(
            Real::Light::Type::DIRECTIONAL,
            glm::vec3(0.0f, 0.0f, .0f),
            glm::vec4(1.0f),
            0.05f,
            Real::Light::DirectionalParameters{
                direction: glm::vec3(0, -1, 0)
            }
        ));

        std::shared_ptr<Real::Light> pointLight(new Real::Light(
            Real::Light::Type::POINT,
            glm::vec3(-1.0f, 1.8f, .0f),
            glm::vec4(1.0f),
            8.6f,
            Real::Light::PointParameters{
                falloff: glm::vec2(2.5f, 1.2f)
            }
        ));

        std::shared_ptr<Real::Light> spotLight(new Real::Light(
            Real::Light::Type::SPOTLIGHT,
            glm::vec3(3.0f, 0.6f, -3.0f),
            glm::vec4(1.0f),
            4.0f,
            Real::Light::SpotlightParameters{
                direction: glm::vec3(-2.0f, 0.2f, -0.5f),
                inner : 0.95f,
                outer : 0.90f
            }
        ));

        std::shared_ptr<Real::Light> spotLight1(new Real::Light(
            Real::Light::Type::SPOTLIGHT,
            glm::vec3(3.0f, 1.4f, 2.5f),
            glm::vec4(1.0f, 0.0f, 1.0f, 0.3f),
            0.1f,
            Real::Light::SpotlightParameters{
                direction: glm::vec3(-0.0f, -1.2f, 1.5f),
                inner : 0.98999f,
                outer : 0.90f
            }
        ));

        std::shared_ptr<Real::Light> spotLight2(new Real::Light(
            Real::Light::Type::SPOTLIGHT,
            glm::vec3(-3.0f, 1.4f, 2.5f),
            glm::vec4(0.0f, 1.0f, 0.5f, 0.3f),
            1.6f,
            Real::Light::SpotlightParameters{
                direction: glm::vec3(1.0f, -0.3f, 0.0f),
                inner : 0.98999f,
                outer : 0.90f
            }
        ));

        std::shared_ptr<Real::Light> spotLight3(new Real::Light(
            Real::Light::Type::SPOTLIGHT,
            glm::vec3(0, 2, 0),
            glm::vec4(1.0f, 0.0f, 0.3f, 1.0f),
            1.6f,
            Real::Light::SpotlightParameters{
                direction: glm::vec3(0.0f, -1.0f, 0.0f),
                inner : 0.98999f,
                outer : 0.90f
            }
        ));


        std::shared_ptr<Real::Mesh> terrain(new Mesh(glm::vec3(0, -1, 0), VAOFactory::get(VAOFactory::Shape::PLANE), textures));
        std::vector<std::shared_ptr<Real::Model>> pillars = {
                std::shared_ptr<Real::Model>(new Model("models/pillar.obj")),
                std::shared_ptr<Real::Model>(new Model("models/pillar.obj")),
                std::shared_ptr<Real::Model>(new Model("models/pillar.obj")),
                std::shared_ptr<Real::Model>(new Model("models/pillar.obj")),
                std::shared_ptr<Real::Model>(new Model("models/pillar.obj")),
                std::shared_ptr<Real::Model>(new Model("models/pillar.obj")),
                std::shared_ptr<Real::Model>(new Model("models/pillar.obj")),
                std::shared_ptr<Real::Model>(new Model("models/pillar.obj")),
                std::shared_ptr<Real::Model>(new Model("models/pillar.obj")),
                std::shared_ptr<Real::Model>(new Model("models/pillar.obj")),
        };

        std::shared_ptr<Real::Model> bunny(new Model("models/stanford-bunny.obj"));
        std::shared_ptr<Real::Model> bunny1(new Model("models/stanford-bunny.obj"));
        std::shared_ptr<Real::Model> rat(new Model("models/rat/obj.obj"));
        std::shared_ptr<Real::Mesh> pyramid(new Mesh(glm::vec3(1.0f, 0, -2.5), VAOFactory::get(VAOFactory::Shape::PYRAMID), { popcat, specular }));
        std::shared_ptr<Real::Model> sphere(new Model("models/sphere.obj"));
        std::shared_ptr<Real::Mesh> cube(new Mesh(glm::vec3(0.8f, 1.0f, -3), VAOFactory::get(VAOFactory::Shape::CUBE), {}));

        //sphere->setDiffuse(bricksTex);
        sphere->translate(glm::vec3(0, 1.5f, 0));
        sphere->scale(0.1f);

        rat->scale(0.01f);
        rat->rotate(90.0f, glm::vec3(0, -1.0f, 0));
        rat->translate(glm::vec3(-40.0f, -15.15f, -35.5f));
        rat->rotate(30.0f, glm::vec3(-1, 0, 0));
        rat->setDiffuse(terrainTex2);

        std::srand(std::time(nullptr)); // use current time as seed for random generator
        glm::vec3 translation(1.5f, 0.0f, 0.0f);
        for (int i = 0; i < 10; i++)
        {
            pillars[i]->setDiffuse(pillarTex);
            pillars[i]->translate(translation);
            pillars[i]->rotate((float)(std::rand() % 360), glm::vec3(0, 1, 0));
            pillars[i]->scale(0.3f);
            translation = glm::rotate(translation, glm::radians(36.0f), glm::vec3(0, 1, 0));
        }

        terrain->scale(4.0f);
        terrain->translate(glm::vec3(0, 0.26f, 0));

        bunny->scale(5.0f);
        bunny->translate(glm::vec3(0.65f, -0.03f, 0.6f));
        bunny->rotate(90.0f, glm::vec3(0, -1, 0));

        bunny1->scale(5.0f);
        bunny1->translate(glm::vec3(0.35f, -0.03f, 0.55f));
        bunny1->rotate(120.0f, glm::vec3(0, -1, 0));

        LightManager::getInstance().addLight(directional);
        LightManager::getInstance().addLight(pointLight);
        LightManager::getInstance().addLight(spotLight);
        LightManager::getInstance().addLight(spotLight1);
        LightManager::getInstance().addLight(spotLight2);
        LightManager::getInstance().addLight(spotLight3);

        std::vector<std::shared_ptr<Drawable>> drawables = { terrain, bunny, bunny1, rat, pyramid, cube, sphere };
        drawables.insert(drawables.end(), pillars.begin(), pillars.end());

        std::shared_ptr<Shader> currentShader = shaderPhong;

        double prevTime = glfwGetTime();
        glm::vec3 pointDirection(0, 0, 1);
        // Main while loop
        while (!glfwWindowShouldClose(&window))
        {
            glEnable(GL_DEPTH_TEST);

            glClearColor(0.4f, 0.3f, 0.3f, 0.2f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            double currTime = glfwGetTime();
            if (currTime - prevTime > 1 / 40)
            {
                prevTime = currTime;
                pointLight->translate(0.01f * pointDirection);
                glm::vec3 pos = 0.01f * pointLight->getPosition();
                pointDirection.z -= pos.z;
                pointDirection.x -= pos.x;
            }

            LightManager::getInstance().applyLight(*currentShader);
            LightManager::getInstance().castShadows(*currentShader, window, drawables);
            for (auto& drawable : drawables)
                drawable->draw(*currentShader);

            LightManager::getInstance().draw();
            glfwSwapBuffers(&window);

            glfwPollEvents();

            Real::Camera::getInstace().handleInput();

            if (glfwGetKey(&window, GLFW_KEY_P) == GLFW_PRESS)
            {
                currentShader = shaderPhong;
            }
            else if (glfwGetKey(&window, GLFW_KEY_G) == GLFW_PRESS)
            {
                currentShader = shaderGourand;
            }
            else if (glfwGetKey(&window, GLFW_KEY_F) == GLFW_PRESS)
            {
                currentShader = shaderFlat;
            }
        }
    }

    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}

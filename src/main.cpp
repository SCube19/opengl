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
    glEnable(GL_FRAMEBUFFER_SRGB);
    {

        std::shared_ptr<Real::Shader> shaderFlat(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::FLAT));
        std::shared_ptr<Real::Shader> shaderGourand(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::GOURAND));
        std::shared_ptr<Real::Shader> shaderPhong(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::PHONG));
        std::shared_ptr<Real::Shader> shaderNone(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::NONE));
        std::shared_ptr<Real::Shader> shaderShadows(Real::ShaderFactory::get(Real::ShaderFactory::LightModel::SHADOWS));
        std::shared_ptr<Real::Shader> shaderFramebuffer(new Shader("shaders/framebuffer.vert", "shaders/framebuffer.frag"));

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


        Real::Mesh plank(glm::vec3(0, -1, 0), VAOFactory::get(VAOFactory::Shape::PLANE), textures);

        // Real::Model bunny("models/sphere.obj");
        // Real::Model bunny1("models/sphere.obj");
        // Real::Model bunny2("models/sphere.obj");
        Real::Model bunny3("models/stanford-bunny.obj");

        // bunny.scale(0.2f);
        // bunny1.scale(0.2f);
        // bunny2.scale(0.2f);
        bunny3.scale(3.0f);

        // bunny.translate(glm::vec3(-5.0f, .0f, .0f));
        // bunny2.translate(glm::vec3(5.0f, .0f, .0f));

        double prevTime = glfwGetTime();

        const unsigned int SHADOW_WIDTH = 4096, SHADOW_HEIGHT = 4096;
        unsigned int depthMapFBO;
        glGenFramebuffers(1, &depthMapFBO);
        // create depth texture
        unsigned int depthMap;
        glGenTextures(1, &depthMap);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        float clamp[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clamp);
        // attach depth texture as FBO's depth buffer
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        shaderFramebuffer->setUniform("depthMap", 0);

        glm::vec3 lightPos(lightTest->getPosition());

        LightManager::getInstance().addLight(std::move(lightTest));
        LightManager::getInstance().applyLight(*shaderPhong);

        // Main while loop
        while (!glfwWindowShouldClose(&window))
        {
            glEnable(GL_DEPTH_TEST);

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glm::mat4 lightProjection, lightView;
            glm::mat4 lightSpaceMatrix;
            lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, Camera::getInstace().getNear(), Camera::getInstace().getFar());
            lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            lightSpaceMatrix = lightProjection * lightView;
            // render scene from light's point of view
            shaderShadows->setUniformMatrix(glUniformMatrix4fv, "lightProjection", 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

            glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
            glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
            glClear(GL_DEPTH_BUFFER_BIT);
            glCullFace(GL_FRONT);
            bunny3.draw(*shaderShadows);
            plank.draw(*shaderShadows);
            glCullFace(GL_BACK);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            // reset viewport
            glViewport(0, 0, 800, 800);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shaderPhong->setUniformMatrix(glUniformMatrix4fv, "lightProjection", 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
            glActiveTexture(GL_TEXTURE0 + 2);
            glBindTexture(GL_TEXTURE_2D, depthMap);
            shaderPhong->setUniform("shadowMap", 2);

            bunny3.draw(*shaderPhong);
            plank.draw(*shaderPhong);
            // // render Depth map to quad for visual debugging
            //         // ---------------------------------------------
            // shaderFramebuffer->setUniform("near_plane", near_plane);
            // shaderFramebuffer->setUniform("far_plane", far_plane);
            // glActiveTexture(GL_TEXTURE0);
            // glBindTexture(GL_TEXTURE_2D, depthMap);
            // renderQuad();

            glfwSwapBuffers(&window);

            glfwPollEvents();

            Real::Camera::getInstace().handleInput();
            // double currTime = glfwGetTime();
            // if (currTime - prevTime > 1 / 60)
            // {
            //     bunny.rotate(1.0f, glm::vec3(1.0f, 0.5f, -1.0f));
            //     bunny1.rotate(1.0f, glm::vec3(1.0f, 0.5f, -1.0f));
            //     bunny2.rotate(1.0f, glm::vec3(1.0f, 0.5f, -1.0f));
            // }
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
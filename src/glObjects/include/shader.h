#pragma once

#include <glad/glad.h>
#include <string>

namespace Real
{
class Shader
{
private:
    GLuint shaderProgram;
    static void assertNoCompileError(GLuint shader, const std::string& type);

public:
    Shader(const std::string& vertexFile, const std::string& fragmentFile);
    ~Shader();

    void use();

    GLuint getProgram();

    template<typename T>
    void setUniform(const std::string& uniformName, T value);
};
}
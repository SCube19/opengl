#pragma once

#include <glad/glad.h>
#include <string>
#include <functional>

namespace Real
{
class Shader
{
private:
    GLuint shaderProgram;
    static void assertNoCompileError(GLuint shader, const std::string& type, const std::string& file);

    GLint prepareForSetUniform(Shader& shader, const std::string& uniformName)
    {
        shader.use();
        return glGetUniformLocation(shader.getProgram(), uniformName.c_str());

    }

public:
    Shader(const std::string& vertexFile, const std::string& fragmentFile);
    ~Shader();

    void use();

    GLuint getProgram();

    template<typename T>
    void setUniform(const std::string& uniformName, T value);

    template<typename T>
    void setUniform(const std::string& uniformName, T value1, T value2);

    template<typename T>
    void setUniform(const std::string& uniformName, T value1, T value2, T value3);

    template<typename T>
    void setUniform(const std::string& uniformName, T value1, T value2, T value3, T value4);

    template<typename T>
    using value_callback = std::function<void(GLint, GLsizei, const T*)>;

    using matrix_callback = std::function<void(GLint, GLsizei, GLboolean, const GLfloat*)>;

    template<typename T>
    void setUniformVector(
        value_callback<T> glUniform,
        const std::string& uniformName,
        GLsizei count,
        const T* value)
    {
        GLint uniform = prepareForSetUniform(*this, uniformName);
        glUniform(uniform, count, value);
    }

    void setUniformMatrix(
        matrix_callback glUniform,
        const std::string& uniformName,
        GLsizei count,
        GLboolean transpose,
        const GLfloat* value);
};
}
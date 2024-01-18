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

    using value_callback = std::function<void(GLint, GLsizei, const GLfloat*)>;
    using matrix_callback = std::function<void(GLint, GLsizei, GLboolean, const GLfloat*)>;

    void setUniformValue(
        value_callback glUniform,
        const std::string& uniformName,
        GLsizei count,
        const GLfloat* value);

    void setUniformMatrix(
        matrix_callback glUniform,
        const std::string& uniformName,
        GLsizei count,
        GLboolean transpose,
        const GLfloat* value);
};
}
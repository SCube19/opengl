#include "shader.h"

#include <fstream>
#include <string>
#include <stdexcept>
#include <iostream>

namespace Real
{
namespace
{
std::string getFileContents(const std::string& fileName)
{
    std::ifstream stream(fileName);
    return { (std::istreambuf_iterator<char>(stream)),
        std::istreambuf_iterator<char>() };
}
}

void Shader::assertNoCompileError(GLuint shader, const std::string& type, const std::string& file)
{
    GLint hasCompiled;
    char infoLog[1024];

    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            throw std::runtime_error("SHADER_COMPILATION_ERROR in " + file + " for: " + type + "\n" + infoLog + "\n");
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            throw std::runtime_error("SHADER_LINKING_ERROR in " + file + " for: " + type + "\n" + infoLog + "\n");
        }
    }
}

Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile)
{
    std::string vertexCode = getFileContents(vertexFile);
    std::string fragmentCode = getFileContents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(vertexShader);
    // Checks if Shader compiled succesfully
    assertNoCompileError(vertexShader, "VERTEX", vertexFile);

    // Create Fragment Shader Object and get its reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the Fragment Shader Object
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(fragmentShader);
    // Checks if Shader compiled succesfully
    assertNoCompileError(fragmentShader, "FRAGMENT", fragmentFile);

    // Create Shader Program Object and get its reference
    this->shaderProgram = glCreateProgram();
    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(this->shaderProgram, vertexShader);
    glAttachShader(this->shaderProgram, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(this->shaderProgram);
    // Checks if Shaders linked succesfully
    assertNoCompileError(this->shaderProgram, "PROGRAM", "");

    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(shaderProgram);
}

void Shader::use()
{
    glUseProgram(shaderProgram);
}

GLuint Shader::getProgram()
{
    return shaderProgram;
}

namespace
{
GLint prepareForSetUniform(Shader& shader, const std::string& uniformName)
{
    shader.use();
    return glGetUniformLocation(shader.getProgram(), uniformName.c_str());
}
}

template<>
void Shader::setUniform(const std::string& uniformName, GLfloat value)
{
    GLint uniform = prepareForSetUniform(*this, uniformName);
    glUniform1f(uniform, value);
}

template<>
void Shader::setUniform(const std::string& uniformName, GLint value)
{
    GLint uniform = prepareForSetUniform(*this, uniformName);
    glUniform1i(uniform, value);
}

template<>
void Shader::setUniform(const std::string& uniformName, GLuint value)
{
    GLint uniform = prepareForSetUniform(*this, uniformName);
    glUniform1ui(uniform, value);
}

template<>
void Shader::setUniform(const std::string& uniformName, GLfloat value1, GLfloat value2)
{
    GLint uniform = prepareForSetUniform(*this, uniformName);
    glUniform2f(uniform, value1, value2);
}

template<>
void Shader::setUniform(const std::string& uniformName, GLint value1, GLint value2)
{
    GLint uniform = prepareForSetUniform(*this, uniformName);
    glUniform2i(uniform, value1, value2);
}

template<>
void Shader::setUniform(const std::string& uniformName, GLuint value1, GLuint value2)
{
    GLint uniform = prepareForSetUniform(*this, uniformName);
    glUniform2ui(uniform, value1, value2);
}

template<>
void Shader::setUniform(const std::string& uniformName, GLfloat value1, GLfloat value2, GLfloat value3)
{
    GLint uniform = prepareForSetUniform(*this, uniformName);
    glUniform3f(uniform, value1, value2, value3);
}

template<>
void Shader::setUniform(const std::string& uniformName, GLint value1, GLint value2, GLint value3)
{
    GLint uniform = prepareForSetUniform(*this, uniformName);
    glUniform3i(uniform, value1, value2, value3);
}

template<>
void Shader::setUniform(const std::string& uniformName, GLuint value1, GLuint value2, GLuint value3)
{
    GLint uniform = prepareForSetUniform(*this, uniformName);
    glUniform3ui(uniform, value1, value2, value3);
}

template<>
void Shader::setUniform(const std::string& uniformName, GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4)
{
    GLint uniform = prepareForSetUniform(*this, uniformName);
    glUniform4f(uniform, value1, value2, value3, value4);
}

template<>
void Shader::setUniform(const std::string& uniformName, GLint value1, GLint value2, GLint value3, GLint value4)
{
    GLint uniform = prepareForSetUniform(*this, uniformName);
    glUniform4i(uniform, value1, value2, value3, value4);
}

template<>
void Shader::setUniform(const std::string& uniformName, GLuint value1, GLuint value2, GLuint value3, GLuint value4)
{
    GLint uniform = prepareForSetUniform(*this, uniformName);
    glUniform4ui(uniform, value1, value2, value3, value4);
}

void Shader::setUniformValue(
    value_callback glUniform,
    const std::string& uniformName,
    GLsizei count,
    const GLfloat* value)
{
    GLint uniform = prepareForSetUniform(*this, uniformName);
    glUniform(uniform, count, value);
}

void Shader::setUniformMatrix(
    matrix_callback glUniform,
    const std::string& uniformName,
    GLsizei count,
    GLboolean transpose,
    const GLfloat* value)
{
    GLint uniform = prepareForSetUniform(*this, uniformName);
    glUniform(uniform, count, transpose, value);
}

}
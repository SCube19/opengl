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

void Shader::assertNoCompileError(GLuint shader, const std::string& type)
{
    GLint hasCompiled;
    char infoLog[1024];

    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            throw std::runtime_error("SHADER_COMPILATION_ERROR for: " + type + "\n" + infoLog + "\n");
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            throw std::runtime_error("SHADER_LINKING_ERROR for: " + type + "\n" + infoLog + "\n");
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
    assertNoCompileError(vertexShader, "VERTEX");

    // Create Fragment Shader Object and get its reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the Fragment Shader Object
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(fragmentShader);
    // Checks if Shader compiled succesfully
    assertNoCompileError(fragmentShader, "FRAGMENT");

    // Create Shader Program Object and get its reference
    this->shaderProgram = glCreateProgram();
    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(this->shaderProgram, vertexShader);
    glAttachShader(this->shaderProgram, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(this->shaderProgram);
    // Checks if Shaders linked succesfully
    assertNoCompileError(this->shaderProgram, "PROGRAM");

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

template<>
void Shader::setUniform(const std::string& uniformName, GLfloat value)
{
    GLuint uniform = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniform1f(uniform, value);
}

template<>
void Shader::setUniform(const std::string& uniformName, GLint value)
{
    GLuint uniform = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniform1i(uniform, value);
}

template<>
void Shader::setUniform(const std::string& uniformName, GLuint value)
{
    GLuint uniform = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniform1ui(uniform, value);
}
}
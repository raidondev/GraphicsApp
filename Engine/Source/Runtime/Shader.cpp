#include "Shader.h"

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <iostream>

namespace GraphicsEngine
{
    Shader::Shader(const char* vertexPath, const char* fragmentPath)
    {
        std::string vertexCode = LoadShaderSource(vertexPath);
        std::string fragmentCode = LoadShaderSource(fragmentPath);

        unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexCode);
        unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);

        m_ShaderID = glCreateProgram();
        glAttachShader(m_ShaderID, vertexShader);
        glAttachShader(m_ShaderID, fragmentShader);
        glLinkProgram(m_ShaderID);
        CheckProgramLinkErrors(m_ShaderID);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_ShaderID);
    }

    void Shader::Use() const
    {
        glUseProgram(m_ShaderID);
    }

    void Shader::SetBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), static_cast<int>(value));
    }

    void Shader::SetInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), value);
    }

    void Shader::SetFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(m_ShaderID, name.c_str()), value);
    }

    std::string Shader::LoadShaderSource(const std::string& filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            std::cerr << "ERROR::SHADER::FILE_NOT_FOUND: " << filePath << '\n';
            return "";
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
    {
        unsigned int shader = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        CheckShaderCompileErrors(shader, type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
        return shader;
    }

    void Shader::CheckShaderCompileErrors(unsigned int shader, const std::string& type)
    {
        // Check compilation errors
        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::" << type <<"::COMPILATION_FAILED\n" << infoLog << "\n";
        }
    }

    void Shader::CheckProgramLinkErrors(unsigned int program)
    {
        // Check linking errors
        int success;
        char infoLog[512];
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
        }
    }
}

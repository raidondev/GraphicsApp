#pragma once

#include <string>

namespace GraphicsApp
{
    class Shader
    {
    public:
        unsigned int ID;

        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();

        void Use() const;
        
        void SetBool(const std::string& name, bool value) const;
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;

    private:
        std::string LoadShaderSource(const std::string& filePath);
        unsigned int CompileShader(unsigned int type, const std::string& source);
        void CheckShaderCompileErrors(unsigned int shader, const std::string& type);
        void CheckProgramLinkErrors(unsigned int program);
    };
}
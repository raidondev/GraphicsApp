#pragma once

#include <EntryPoint.h>

class Sandbox : public GraphicsApp::Application
{
public:
    Sandbox();
    ~Sandbox() override = default;

    void Initialize() override;
    void OnUpdate() override;
    void OnFramebufferResize(int width, int height) override;
    void Shutdown() override;

private:
    unsigned int m_VAO = 0, m_VBO = 0, m_EBO = 0;
    unsigned int m_ShaderProgram = 0;

    static void CheckShaderCompileErrors(unsigned int shader, const char* type);
    static void CheckProgramLinkErrors(unsigned int program);
};
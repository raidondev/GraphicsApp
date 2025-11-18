#pragma once

#include <EntryPoint.h>

#include "Shader.h"
#include "Texture.h"
#include "ImGuiLayer.h"

namespace GraphicsEngine
{
    class Sandbox : public Application
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

        Shader* m_Shader = nullptr;
        Texture* m_Texture1 = nullptr;
        Texture* m_Texture2 = nullptr;

        ImGuiLayer m_ImGuiLayer;
        ImVec4 m_ClearColor = ImVec4(0.2f, 0.3f, 0.3f, 1.0f);

        bool m_Wireframe = false;
        bool m_ShowDebugMenu = true;

        GLuint m_FBO = 0;
        GLuint m_FBOTexture = 0;
        GLuint m_RBO = 0; // optional depth/stencil
        int m_FBOWidth = 800;
        int m_FBOHeight = 600;
    };
}

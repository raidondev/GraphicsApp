#pragma once

#include <EntryPoint.h>

#include "Shader.h"
#include "Texture.h"
#include "ImGuiLayer.h"

namespace GraphicsApp
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
    };
}

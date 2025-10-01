#pragma once

#include <EntryPoint.h>

#include "Shader.h"

namespace GraphicsApp
{
    class Sandbox : public Application
    {
        public
        :
        Sandbox();
        ~Sandbox()
        override = default;

        void Initialize() override;
        void OnUpdate() override;
        void OnFramebufferResize(int width, int height) override;
        void Shutdown() override;

        private
        :
        unsigned int m_VAO = 0, m_VBO = 0, m_EBO = 0;
        unsigned int m_Texture1 = 0, m_Texture2 = 0;

        Shader* m_Shader = nullptr;
    };
}

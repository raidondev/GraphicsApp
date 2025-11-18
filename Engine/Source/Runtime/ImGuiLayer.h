#pragma once

#include <imgui.h>

#include <GLFW/glfw3.h>

namespace GraphicsEngine
{
    class ImGuiLayer
    {
    public:
        ImGuiLayer() = default;
        ~ImGuiLayer() = default;

        void Initialize(GLFWwindow* window);
        void BeginFrame();
        void EndFrame();
        void Shutdown();
    };
}
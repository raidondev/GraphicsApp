#pragma once

#include <imgui.h>

struct GLFWwindow;

namespace GraphicsApp
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
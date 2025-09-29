#pragma once

#include <functional>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using FramebufferResizeCallbackFn = std::function<void(int, int)>;

namespace GraphicsApp
{
    class Window
    {
    public:
        struct WindowProps
        {
            std::string Title;
            uint32_t Width;
            uint32_t Height;

            WindowProps(std::string title = "GLFW Application", uint32_t width = 1280, uint32_t height = 720)
                : Title(std::move(title)), Width(width), Height(height)
            {
            }
        };

        Window(const WindowProps& props = WindowProps());
        virtual ~Window();

        void OnUpdate();
        void SetFramebufferResizeCallback(FramebufferResizeCallbackFn callback);

        uint32_t GetWidth() const { return m_Data.Width; }
        uint32_t GetHeight() const { return m_Data.Height; }

        bool ShouldClose() const { return glfwWindowShouldClose(m_Window); }

    private:
        void Initialize(const WindowProps& props);
        void Shutdown();

        void OnFramebufferResize(int width, int height);
        
        GLFWwindow* m_Window;
        FramebufferResizeCallbackFn m_FramebufferResizeCallback;

        struct WindowData
        {
            std::string Title;
            uint32_t Width;
            uint32_t Height;
        };

        WindowData m_Data;
    };
}
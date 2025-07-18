#pragma once

#include <string>
#include <GLFW/glfw3.h>

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
        uint32_t GetWidth() const { return m_Data.Width; }
        uint32_t GetHeight() const { return m_Data.Height; }

        bool ShouldClose() const { return glfwWindowShouldClose(m_Window); }

    private:
        void Init(const WindowProps& props);
        void Shutdown();

    private:
        GLFWwindow* m_Window;

        struct WindowData
        {
            std::string Title;
            uint32_t Width;
            uint32_t Height;
        };

        WindowData m_Data;
    };
}
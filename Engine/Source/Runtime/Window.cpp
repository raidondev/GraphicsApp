#include "Window.h"

#include <iostream>

namespace GraphicsApp
{
    Window::Window(const WindowProps& props)
    {
        Init(props);
    }

    Window::~Window()
    {
        Shutdown();
    }

    void Window::Init(const WindowProps& props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW!" << '\n';
        }

        m_Window = glfwCreateWindow(static_cast<int>(m_Data.Width), static_cast<int>(m_Data.Height), m_Data.Title.c_str(), nullptr, nullptr);
        if (!m_Window)
        {
            std::cerr << "Failed to create GLFW window!" << '\n';
            glfwTerminate();
        }

        glfwMakeContextCurrent(m_Window);
        glfwSwapInterval(1); // Enable V-Sync
    }

    void Window::Shutdown()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void Window::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }
}

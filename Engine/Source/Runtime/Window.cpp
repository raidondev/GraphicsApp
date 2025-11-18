#include "Window.h"

#include <iostream>

namespace GraphicsEngine
{
    Window::Window(const WindowProps& props)
    {
        Initialize(props);
    }

    Window::~Window()
    {
        Shutdown();
    }

    void Window::Initialize(const WindowProps& props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW!" << '\n';
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(static_cast<int>(m_Data.Width), static_cast<int>(m_Data.Height), m_Data.Title.c_str(), nullptr, nullptr);
        if (!m_Window)
        {
            std::cerr << "Failed to create GLFW window!" << '\n';
            glfwTerminate();
        }

        glfwMakeContextCurrent(m_Window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD!" << '\n';
            return;
        }
        
        glfwSetWindowUserPointer(m_Window, this);

        glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
        {
            auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
            if (win)
            {
                win->m_FramebufferResizeCallback(width, height);
            }
        });
        
        glfwSwapInterval(1); // Enable V-Sync
    }

    void Window::OnFramebufferResize(int width, int height)
    {
        m_Data.Width = width;
        m_Data.Height = height;

        glViewport(0, 0, width, height);

        if (m_FramebufferResizeCallback)
        {
            m_FramebufferResizeCallback(width, height);
        }
    }

    void Window::SetFramebufferResizeCallback(FramebufferResizeCallbackFn callback)
    {
        m_FramebufferResizeCallback = std::move(callback);
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

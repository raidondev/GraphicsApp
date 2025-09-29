#include "Application.h"

namespace GraphicsApp
{
    Application::Application(const Window::WindowProps& props)
    {
        m_Window = std::make_unique<Window>(props);
    }

    Application::~Application() = default;

    void Application::Run()
    {
        while (m_Running && !m_Window->ShouldClose())
        {
            m_Window->OnUpdate();
        }
    }
}

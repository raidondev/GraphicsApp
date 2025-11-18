#include "Application.h"

namespace GraphicsEngine
{
    Application::Application(const Window::WindowProps& props)
    {
        m_Window = std::make_unique<Window>(props);

        m_Window->SetFramebufferResizeCallback(
        [this](int width, int height)
        {
            this->OnFramebufferResize(width, height);
        });
    }

    Application::~Application() = default;

    void Application::Run()
    {
        Initialize();

        while (m_Running && !m_Window->ShouldClose())
        {
            OnUpdate();
            m_Window->OnUpdate();
        }

        Shutdown();
    }
}

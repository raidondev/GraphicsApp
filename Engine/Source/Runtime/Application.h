#pragma once

#include <memory>

#include "Window.h"

namespace GraphicsApp
{
    class Application
    {
    public:
        Application(const Window::WindowProps& props);
        virtual ~Application();

        virtual void Run();

    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    // Defined in client application
    Application* CreateApplication();
}

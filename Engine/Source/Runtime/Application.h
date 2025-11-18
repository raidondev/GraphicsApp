#pragma once

#include <memory>

#include "Window.h"

namespace GraphicsEngine
{
    class Application
    {
    public:
        Application(const Window::WindowProps& props);
        virtual ~Application();

        void Run();

    protected:
        virtual void Initialize() {}
        virtual void OnUpdate() {}
        virtual void OnFramebufferResize(int width, int height) {}
        virtual void Shutdown() {}

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    // Defined in client application
    Application* CreateApplication();
}

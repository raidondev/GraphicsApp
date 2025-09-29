#include <EntryPoint.h>

class Sandbox : public GraphicsApp::Application
{
public:
    Sandbox()
        : Application(GraphicsApp::Window::WindowProps("Sandbox", 1280, 720))
    {}

    ~Sandbox() override = default;

    void Run() override { Application::Run(); }
};

GraphicsApp::Application* GraphicsApp::CreateApplication()
{
    return new Sandbox();
}
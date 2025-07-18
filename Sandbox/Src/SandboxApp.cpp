#include <Application.h>

class Sandbox : public GraphicsApp::Application
{
public:
    Sandbox()
        : Application(GraphicsApp::Window::WindowProps("Sandbox", 1280, 720))
    {}

    virtual ~Sandbox() override = default;

    virtual void Run() override { Application::Run(); }
};

int main()
{
    Sandbox app;
    app.Run();
    return 0;
}
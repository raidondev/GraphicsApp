#include <EntryPoint.h>

#include <iostream>
#include <ostream>

class Sandbox : public GraphicsApp::Application
{
public:
    Sandbox()
        : Application(GraphicsApp::Window::WindowProps("Sandbox", 1280, 720))
    {}

    ~Sandbox() override = default;

    void Initialize() override
    {
        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";

        // TODO: Setup shaders, VAOs, VBOs here
    }

    void OnUpdate() override
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // TODO: Draw calls go here
    }

    void OnFramebufferResize(int width, int height) override
    {
        // std::cout << "Framebuffer resized to: " << width << "x" << height << "\n";
    }

    void Shutdown() override
    {
        std::cout << "Shutdown\n";

        // TODO: Cleanup OpenGL resources (glDeleteBuffers, etc.)
    }
};

GraphicsApp::Application* GraphicsApp::CreateApplication()
{
    return new Sandbox();
}
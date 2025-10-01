#include "SandboxApp.h"

#include <iostream>
#include <ostream>

namespace GraphicsApp
{
    Sandbox::Sandbox()
        : Application(Window::WindowProps("Sandbox", 800, 600))
    {
    }

    void Sandbox::Initialize()
    {
        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";

        // Toggle wireframe mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // Triangle Vertices
        float vertices[] = {
            // positions        // Colors
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Bottom left
             0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // Top
        };

        // unsigned int indices[] ={
        //     0, 1, 3, // First triangle
        //     1, 2, 3  // Second triangle
        // };

        // Vertex Buffer Object
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        // glGenBuffers(1, &m_EBO);

        // Bind Vertex Array Object
        glBindVertexArray(m_VAO);

        // Bind Vertex Buffer Object
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Bind Element Buffer Object
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<void*>(nullptr));
        glEnableVertexAttribArray(0);

        // Color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        m_Shader = new Shader("Assets/Shaders/vertex.glsl", "Assets/Shaders/fragment.glsl");
    }

    void Sandbox::OnUpdate()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Shader->Use();
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void Sandbox::OnFramebufferResize(int width, int height)
    {
        // std::cout << "Framebuffer resized to: " << width << "x" << height << "\n";
        glViewport(0, 0, width, height);
    }

    void Sandbox::Shutdown()
    {
        std::cout << "Shutdown\n";

        delete m_Shader;
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
    }

    Application* CreateApplication()
    {
        return new Sandbox();
    }
}

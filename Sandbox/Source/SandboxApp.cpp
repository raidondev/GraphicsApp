#include "SandboxApp.h"

#include <iostream>
#include <ostream>

namespace GraphicsApp
{
    Sandbox::Sandbox()
        : Application(Window::WindowProps("Sandbox", 800, 600))
    {}

    void Sandbox::Initialize()
    {
        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";

        m_ImGuiLayer.Initialize(m_Window->GetNativeWindow());

        // Triangle Vertices
        float vertices[] = {
            // Positions            // Colors            // Textures
             0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // top right
             0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,    1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,    0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f,    0.0f, 1.0f    // top left
        };

        unsigned int indices[] ={
            0, 1, 3, // First triangle
            1, 2, 3  // Second triangle
        };

        // Vertex Buffer Object
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        // Bind Vertex Array Object
        glBindVertexArray(m_VAO);

        // Bind Vertex Buffer Object
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Bind Element Buffer Object
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<void*>(nullptr));
        glEnableVertexAttribArray(0);

        // Color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Texture coordinate
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        m_Shader = new Shader("Assets/Shaders/vertex.glsl", "Assets/Shaders/fragment.glsl");

        m_Texture1 = new Texture("Assets/Textures/wall.jpg", GL_TEXTURE0, false);
        m_Texture2 = new Texture("Assets/Textures/awesomeface.png", GL_TEXTURE1, true);

        m_Shader->Use();
        m_Shader->SetInt("texture1", 0);
        m_Shader->SetInt("texture2", 1);
    }

    void Sandbox::OnUpdate()
    {
        m_ImGuiLayer.BeginFrame();

        // Debug panel
        ImGui::Begin("Debug Menu");
        ImGui::ColorEdit3("Clear Color", reinterpret_cast<float*>(&m_ClearColor));
        if (ImGui::Checkbox("Wireframe", &m_Wireframe))
        {
            // Toggle wireframe mode
            glPolygonMode(GL_FRONT_AND_BACK, m_Wireframe ? GL_LINE : GL_FILL);
        }
        ImGui::End();

        glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Texture1->Bind();
        m_Texture2->Bind();

        m_Shader->Use();
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        m_ImGuiLayer.EndFrame();
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
        delete m_Texture1;
        delete m_Texture2;

        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
    }

    Application* CreateApplication()
    {
        return new Sandbox();
    }
}

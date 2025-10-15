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

        m_ImGuiLayer.Initialize(m_Window->GetNativeWindow());

        // Triangle Vertices
        float vertices[] = {
            // Positions            // Colors            // Textures
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
        };

        unsigned int indices[] = {
            0, 1, 3, // First triangle
            1, 2, 3 // Second triangle
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


        // Create framebuffer
        glGenFramebuffers(1, &m_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

        // Create color texture
        glGenTextures(1, &m_FBOTexture);
        glBindTexture(GL_TEXTURE_2D, m_FBOTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_FBOWidth, m_FBOHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_FBOTexture, 0);

        // Optional: depth/stencil renderbuffer
        glGenRenderbuffers(1, &m_RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_FBOWidth, m_FBOHeight);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR: Framebuffer is not complete!" << '\n';

        glBindFramebuffer(GL_FRAMEBUFFER, 0);


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

        // Main Menu
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Window"))
            {
                ImGui::MenuItem("Debug Menu", nullptr, &m_ShowDebugMenu);
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        // Viewport window
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        
        ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_None);

        ImVec2 viewportSize = ImGui::GetContentRegionAvail();

        // Resize FBO if necessary
        if (static_cast<int>(viewportSize.x) != m_FBOWidth || static_cast<int>(viewportSize.y) != m_FBOHeight)
        {
            m_FBOWidth = static_cast<int>(viewportSize.x);
            m_FBOHeight = static_cast<int>(viewportSize.y);

            glBindTexture(GL_TEXTURE_2D, m_FBOTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_FBOWidth, m_FBOHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

            glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_FBOWidth, m_FBOHeight);
        }

        // Bind FBO
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
        glViewport(0, 0, m_FBOWidth, m_FBOHeight);

        glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Texture1->Bind();
        m_Texture2->Bind();

        m_Shader->Use();
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        // Restore viewport
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        ImGuiIO& io = ImGui::GetIO();
        glViewport(0, 0, static_cast<int>(io.DisplaySize.x), static_cast<int>(io.DisplaySize.y));

        ImGui::Image(m_FBOTexture, viewportSize, ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();
        ImGui::PopStyleVar(3);

        // Debug panel
        if (m_ShowDebugMenu)
        {
            ImGui::Begin("Debug Menu", nullptr, ImGuiWindowFlags_NoDocking);
            ImGui::ColorEdit3("Clear Color", reinterpret_cast<float*>(&m_ClearColor));
            if (ImGui::Checkbox("Wireframe", &m_Wireframe))
            {
                // Toggle wireframe mode
                glPolygonMode(GL_FRONT_AND_BACK, m_Wireframe ? GL_LINE : GL_FILL);
            }
            ImGui::End();
        }
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

        glDeleteFramebuffers(1, &m_FBO);
        glDeleteTextures(1, &m_FBOTexture);
        glDeleteRenderbuffers(1, &m_RBO);
    }

    Application* CreateApplication()
    {
        return new Sandbox();
    }
}

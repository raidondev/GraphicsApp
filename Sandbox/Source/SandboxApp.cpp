#include "SandboxApp.h"

#include <iostream>
#include <ostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

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

        // Load Texture 1
        glGenTextures(1, &m_Texture1);
        glBindTexture(GL_TEXTURE_2D, m_Texture1);

        // Set texture wrapping and filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        unsigned char* data = stbi_load("Assets/Textures/wall.jpg", &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << "\n";
        }
        stbi_image_free(data);

        // Load Texture 2
        glGenTextures(1, &m_Texture2);
        glBindTexture(GL_TEXTURE_2D, m_Texture2);

        // Set texture wrapping and filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(true);
        data = stbi_load("Assets/Textures/awesomeface.png", &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << "\n";
        }
        stbi_image_free(data);

        m_Shader->Use();
        glUniform1i(glGetUniformLocation(m_Shader->ID, "texture1"), 0);
        glUniform1i(glGetUniformLocation(m_Shader->ID, "texture2"), 1);
    }

    void Sandbox::OnUpdate()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_Texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_Texture2);

        m_Shader->Use();
        glBindVertexArray(m_VAO);
        glDrawElements((GL_TRIANGLES), 6, GL_UNSIGNED_INT, nullptr);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
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

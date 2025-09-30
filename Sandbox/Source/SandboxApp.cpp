#include "SandboxApp.h"

#include <iostream>
#include <ostream>

Sandbox::Sandbox()
    : Application(GraphicsApp::Window::WindowProps("Sandbox", 800, 600))
{}

void Sandbox::Initialize()
{
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";

    // Toggle wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Triangle Vertices
    float vertices[] = {
         0.5f,  0.5f, 0.0f, // Top right
         0.5f, -0.5f, 0.0f, // Bottom right
        -0.5f, -0.5f, 0.0f, // Bottom left
        -0.5f,  0.5f, 0.0f, // top left
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
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);

    // Vertex Shader
    const char* vertexShaderSource = R"(
    #version 460 core
    layout (location = 0) in vec3 aPos;

    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
    )";

    // Fragment Shader
    const char* fragmentShaderSource = R"(
    #version 460 core
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    }
    )";
    
    // Compile Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    CheckShaderCompileErrors(vertexShader, "VERTEX");
    
    // Compile Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    CheckShaderCompileErrors(fragmentShader, "FRAGMENT");

    // Link Shader Program
    m_ShaderProgram = glCreateProgram();
    glAttachShader(m_ShaderProgram, vertexShader);
    glAttachShader(m_ShaderProgram, fragmentShader);
    glLinkProgram(m_ShaderProgram);
    CheckProgramLinkErrors(m_ShaderProgram);

    // Clean up shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Sandbox::OnUpdate()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_ShaderProgram);
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Sandbox::OnFramebufferResize(int width, int height)
{
    // std::cout << "Framebuffer resized to: " << width << "x" << height << "\n";
    glViewport(0, 0, width, height);
}

void Sandbox::Shutdown()
{
    std::cout << "Shutdown\n";

    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    glDeleteProgram(m_ShaderProgram);
}

void Sandbox::CheckShaderCompileErrors(unsigned int shader, const char* type)
{
    // Check compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::" << type <<"::COMPILATION_FAILED\n" << infoLog << "\n";
    }
}

void Sandbox::CheckProgramLinkErrors(unsigned int program)
{
    // Check linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
    }
}

GraphicsApp::Application* GraphicsApp::CreateApplication()
{
    return new Sandbox();
}
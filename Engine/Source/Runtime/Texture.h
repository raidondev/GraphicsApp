#pragma once

#include <string>
#include <glad/glad.h>

namespace GraphicsApp
{
    class Texture
    {
    public:
        Texture(const std::string& path, GLenum textureUnit = GL_TEXTURE0, bool flip = false);
        ~Texture();

        void Bind() const;
        void Unbind() const;

        unsigned int GetTextureID() const { return m_TextureID; }

    private:
        unsigned int m_TextureID = 0;
        GLenum m_TextureUnit;
    };
}
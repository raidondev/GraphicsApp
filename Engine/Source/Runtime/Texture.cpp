#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

namespace GraphicsEngine
{
    Texture::Texture(const std::string& path, GLenum textureUnit, bool flip)
    : m_TextureUnit(textureUnit)
    {
        stbi_set_flip_vertically_on_load(flip);

        glGenTextures(1, &m_TextureID);
        glActiveTexture(m_TextureUnit);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        // Default wrapping/filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            GLint format = nrChannels == 4 ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture: " << path << "\n";
        }
        stbi_image_free(data);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_TextureID);
    }

    void Texture::Bind() const
    {
        glActiveTexture(m_TextureUnit);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
    }

    void Texture::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
#include "FrameBuffer.h"
#include <glad/glad.h>
#include <iostream>

void Phantom::FrameBuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, _id);
}

void Phantom::FrameBuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Phantom::FrameBuffer::Resize(const glm::vec2& size)
{
    Resize(size.x, size.y);
}

bool Phantom::FrameBuffer::Create(const glm::vec2& size)
{
    return Create(size.x, size.y);
}

void Phantom::FrameBuffer::Resize(const unsigned int& width, const unsigned int& heigth)
{
    Delete();
    Create(width, heigth);
}

bool Phantom::FrameBuffer::Create(const unsigned int& width, const unsigned int& heigth)
{
    _width = width;
    _height = heigth;
    glGenFramebuffers(1, &_id);
    glBindFramebuffer(GL_FRAMEBUFFER, _id);

    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "RENDERER::FRAMEBUFFER::ERROR" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return false;
    }
    else if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "RENDERER::FRAMEBUFFER::SUCESSFULL" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return true;
    }
}

void Phantom::FrameBuffer::Delete()
{
    glDeleteFramebuffers(1, &_id);
    glDeleteTextures(1, &_texture);
}

Phantom::FrameBuffer::~FrameBuffer()
{
    Delete();
}

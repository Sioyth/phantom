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

void Phantom::FrameBuffer::Resize(const unsigned int& width, const unsigned int& heigth)
{
    Delete();
    Create(width, heigth);
}

bool Phantom::FrameBuffer::Create(const unsigned int& width, const unsigned int& heigth)
{
    // temp fbo
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

    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

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

#include "glh/classes/Framebuffer.h"

//-----------------------------------------------
// Constructor
//-----------------------------------------------
Framebuffer::Framebuffer()
{
    glhGenFramebuffers(1, &m_FramebufferName);

    // gotta name this pattern
    glhBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferName);
    glhBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//-----------------------------------------------
// Destructor
//-----------------------------------------------
Framebuffer::~Framebuffer()
{

}

//-----------------------------------------------
// Move Constructor
//-----------------------------------------------
Framebuffer::Framebuffer(Framebuffer&& other) noexcept
{

}

//-----------------------------------------------
// Move Assignment
//-----------------------------------------------
Framebuffer& Framebuffer::operator=(Framebuffer&& other) noexcept
{
    return *this;
}

//-----------------------------------------------
// bind()
//-----------------------------------------------
void Framebuffer::bind() const
{
    glhBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferName);
}

//-----------------------------------------------
// unbind()
//-----------------------------------------------
void Framebuffer::unbind() const
{
    glhBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//-----------------------------------------------
// setColorAttachment2D()
//-----------------------------------------------
void Framebuffer::setColorAttachment2D(GLenum textarget, GLuint texture)
{
    glhFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textarget, texture, 0);

    m_ColorAttachmentTarget = textarget;
    m_ColorAttachmentTextureName = texture;
}

//-----------------------------------------------
// unbindColorAttachment2D()
//-----------------------------------------------
void Framebuffer::unbindColorAttachment2D()
{
    glhFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_ColorAttachmentTarget, 0, 0);

    m_ColorAttachmentTarget = GL_NONE;
    m_ColorAttachmentTextureName = 0;
}

//-----------------------------------------------
// setDepthAttachment2D()
//-----------------------------------------------
void Framebuffer::setDepthAttachment2D(GLenum textarget, GLuint texture)
{
    glhFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textarget, texture, 0);

    m_DepthAttachmentTarget = textarget;
    m_DepthAttachmentTextureName = texture;
}

//-----------------------------------------------
// unbindDepthAttachment2D()
//-----------------------------------------------
void Framebuffer::unbindDepthAttachment2D()
{
    glhFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_DepthAttachmentTarget, 0, 0);
    
    m_DepthAttachmentTarget = GL_NONE;
    m_DepthAttachmentTextureName = 0;
}

//-----------------------------------------------
// setStencilAttachment2D()
//-----------------------------------------------
void Framebuffer::setStencilAttachment2D(GLenum textarget, GLuint texture)
{
    glhFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, textarget, texture, 0);

    m_StencilAttachmentTarget = textarget;
    m_StencilAttachmentTextureName = texture;
}

//-----------------------------------------------
// unbindStencilAttachment2D()
//-----------------------------------------------
void Framebuffer::unbindStencilAttachment2D()
{
    glhFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, m_StencilAttachmentTarget, 0, 0);

    m_StencilAttachmentTarget = GL_NONE;
    m_StencilAttachmentTextureName = 0;
}
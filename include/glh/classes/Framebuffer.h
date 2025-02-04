#ifndef GLH_FRAMEBUFFER_H
#define GLH_FRAMEBUFFER_H

#include "glh/functionWrappers.h"

class Framebuffer
{
public:
    Framebuffer();
    ~Framebuffer();

    Framebuffer(const Framebuffer& other) = delete;
    Framebuffer& operator=(const Framebuffer& other) = delete;

    Framebuffer(Framebuffer&& other) noexcept;
    Framebuffer& operator=(Framebuffer&& other) noexcept;

    void bind() const;
    void unbind() const;

    void setColorAttachment2D(GLenum textarget, GLuint texture);
    void unbindColorAttachment2D();
    void setDepthAttachment2D(GLenum textarget, GLuint texture);
    void unbindDepthAttachment2D();
    void setStencilAttachment2D(GLenum textarget, GLuint texture);
    void unbindStencilAttachment2D();

    GLuint handle() const { return m_FramebufferName; }
    bool isValid() const { return m_FramebufferName != 0; }
    bool isComplete() const
    {
        return glhCheckNamedFramebufferStatus(m_FramebufferName, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    }

private:
    GLuint m_FramebufferName{0};
    GLenum m_ColorAttachmentTarget{GL_NONE};
    GLuint m_ColorAttachmentTextureName{0};
    GLenum m_DepthAttachmentTarget{GL_NONE};
    GLuint m_DepthAttachmentTextureName{0};
    GLenum m_StencilAttachmentTarget{GL_NONE};
    GLuint m_StencilAttachmentTextureName{0};
};

#endif
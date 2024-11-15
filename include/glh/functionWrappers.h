#ifndef GLH_DEBUG_WRAPPERS_H
#define GLH_DEBUG_WRAPPERS_H

#include "glad/gl.h"
#include "glh/macros.h"

// Framebuffers
static void glhGenFramebuffers(GLsizei n, GLuint* framebuffers) {
    GL_ERROR_CHECK("Begin glGenFramebuffers()");
    glGenFramebuffers(n, framebuffers);
    GL_ERROR_CHECK("glGenFramebuffers()");
}

static void glhBindFramebuffer(GLenum target, GLuint framebuffer) {
    GL_ERROR_CHECK("Before glBindFramebuffer()");
    glBindFramebuffer(target, framebuffer);
    GL_ERROR_CHECK("glBindFramebuffer()");
}

static void glhFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    GL_ERROR_CHECK("Before glFramebufferTexture2D()");
    glFramebufferTexture2D(target, attachment, textarget, texture, level);
    GL_ERROR_CHECK("glFramebufferTexture2D()");
}

static GLenum glhCheckFramebufferStatus(GLenum target) {
    GL_ERROR_CHECK("Before glCheckFramebufferStatus()");
    GLenum status = glCheckFramebufferStatus(target);
    GL_ERROR_CHECK("glCheckFramebufferStatus()");
    return status;
}

// Textures
static void glhGenTextures(GLsizei num, GLuint* textures) {
    GL_ERROR_CHECK("Before glGenTextures()");
    glGenTextures(num, textures);
    GL_ERROR_CHECK("glGenTextures()");
}

static void glhDeleteTextures(GLsizei num, GLuint* textures) {
    GL_ERROR_CHECK("Before glDeleteTextures()");
    glDeleteTextures(num, textures);
    GL_ERROR_CHECK("glDeleteTextures()");
}

static void glhBindTexture(GLenum target, GLuint texture)
{
    GL_ERROR_CHECK("Before glBindTexture()");
    glBindTexture(target, texture);
    GL_ERROR_CHECK("glBindTexture()");
}

static void glhTextureStorage2D(GLuint texture, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height) {
    GL_ERROR_CHECK("Before glTextureStorage2D()");
    glTextureStorage2D(texture, levels, internalFormat, width, height);
    GL_ERROR_CHECK("glTextureStorage2D()");
}

static void glhGenerateTextureMipmap(GLuint texture) {
    GL_ERROR_CHECK("Before glGenerateTextureMipmap()");
    glGenerateTextureMipmap(texture);
    GL_ERROR_CHECK("glGenerateTextureMipmap()");
}

static void glhTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) {
    GL_ERROR_CHECK("Before glTextureSubImage2D()");
    glTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels);
    GL_ERROR_CHECK("glTextureSubImage2D()");
}

static void glhTextureParameteri(GLuint texture, GLenum pname, GLint param) {
    GL_ERROR_CHECK("Before glTextureParameteri()");
    glTextureParameteri(texture, pname, param);
    GL_ERROR_CHECK("glTextureParameteri()");
}

// Clearing
static void glhClear(GLenum clearTarget) {
    GL_ERROR_CHECK("Before glClear()");
    glClear(clearTarget);
    GL_ERROR_CHECK("glClear()");
}

static void glhClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    GL_ERROR_CHECK("Before glClearColor()");
    glClearColor(r, g, b, a);
    GL_ERROR_CHECK("glClearColor()");
}

// Fixed Function Procedures
// NOTE: Cannot execute glGetError() while between glBegin() and glEnd()
static void glhBegin(GLenum mode) {
    GL_ERROR_CHECK("Before glBegin()");
    glBegin(mode);
    //  Can't execute glGetError() after starting
}

static void glhEnd() {
    // Can't execute glGetError() before ending
    glEnd();
    GL_ERROR_CHECK("glEnd()");
}

static void glhTexCoord2f(GLfloat s, GLfloat t) {
    glTexCoord2f(s, t);
}

static void glhVertex2f(GLfloat x, GLfloat y) {
    glVertex2f(x, y);
}

#endif
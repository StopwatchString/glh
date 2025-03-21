#ifndef GLH_DEBUG_WRAPPERS_H
#define GLH_DEBUG_WRAPPERS_H

#include "glh/openglapi.h"
#include "glh/macros.h"

// Framebuffers
static void glhGenFramebuffers(GLsizei n, GLuint* framebuffers)
{
    GL_ERROR_CHECK("Begin glGenFramebuffers()");
    glGenFramebuffers(n, framebuffers);
    GL_ERROR_CHECK("glGenFramebuffers()");
}

static void glhBindFramebuffer(GLenum target, GLuint framebuffer)
{
    GL_ERROR_CHECK("Before glBindFramebuffer()");
    glBindFramebuffer(target, framebuffer);
    GL_ERROR_CHECK("glBindFramebuffer()");
}

static void glhFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
    GL_ERROR_CHECK("Before glFramebufferTexture2D()");
    glFramebufferTexture2D(target, attachment, textarget, texture, level);
    GL_ERROR_CHECK("glFramebufferTexture2D()");
}

static GLenum glhCheckFramebufferStatus(GLenum target)
{
    GL_ERROR_CHECK("Before glCheckFramebufferStatus()");
    GLenum status = glCheckFramebufferStatus(target);
    GL_ERROR_CHECK("glCheckFramebufferStatus()");
    return status;
}

static GLenum glhCheckNamedFramebufferStatus(GLuint framebuffer, GLenum target)
{
    GL_ERROR_CHECK("Before glCheckNamedFramebufferStatus()");
    GLenum status = glCheckNamedFramebufferStatus(framebuffer, target);
    GL_ERROR_CHECK("glCheckNamedFramebufferStatus()");
    return status;
}

// Vertex Array Object
static void glhBindVertexArray(GLuint array)
{
    GL_ERROR_CHECK("Before glBindVertexArray()");
    glBindVertexArray(array);
    GL_ERROR_CHECK("glBindVertexArray()");
}

// Buffer Objects
static void glhBindBuffer(GLenum target, GLuint buffer)
{
    GL_ERROR_CHECK("Before glBindBuffer()");
    glBindBuffer(target, buffer);
    GL_ERROR_CHECK("glBindBuffer()");
}

// Textures
static void glhGenTextures(GLsizei num, GLuint* textures)
{
    GL_ERROR_CHECK("Before glGenTextures()");
    glGenTextures(num, textures);
    GL_ERROR_CHECK("glGenTextures()");
}

static void glhDeleteTextures(GLsizei num, GLuint* textures)
{
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

static void glhTextureStorage2D(GLuint texture, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height)
{
    GL_ERROR_CHECK("Before glTextureStorage2D()");
    glTextureStorage2D(texture, levels, internalFormat, width, height);
    GL_ERROR_CHECK("glTextureStorage2D()");
}

static void glhGenerateTextureMipmap(GLuint texture)
{
    GL_ERROR_CHECK("Before glGenerateTextureMipmap()");
    glGenerateTextureMipmap(texture);
    GL_ERROR_CHECK("glGenerateTextureMipmap()");
}

static void glhTextureSubImage2D(
    GLuint texture,
    GLint level,
    GLint xoffset,
    GLint yoffset,
    GLsizei width,
    GLsizei height,
    GLenum format,
    GLenum type,
    const void* pixels)
{
    GL_ERROR_CHECK("Before glTextureSubImage2D()");
    glTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels);
    GL_ERROR_CHECK("glTextureSubImage2D()");
}

static void glhTextureParameteri(GLuint texture, GLenum pname, GLint param)
{
    GL_ERROR_CHECK("Before glTextureParameteri()");
    glTextureParameteri(texture, pname, param);
    GL_ERROR_CHECK("glTextureParameteri()");
}

static void glhActiveTexture(GLenum texture)
{
    GL_ERROR_CHECK("Before glActiveTexture()");
    glActiveTexture(texture);
    GL_ERROR_CHECK("glActiveTexture()");
}

// Clearing
static void glhClear(GLenum clearTarget)
{
    GL_ERROR_CHECK("Before glClear()");
    glClear(clearTarget);
    GL_ERROR_CHECK("glClear()");
}

static void glhClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    GL_ERROR_CHECK("Before glClearColor()");
    glClearColor(r, g, b, a);
    GL_ERROR_CHECK("glClearColor()");
}

// Shaders
static GLuint glhCreateShader(GLenum type)
{
    GL_ERROR_CHECK("Before glCreateShader()");
    GLuint shader = glCreateShader(type);
    GL_ERROR_CHECK("glCreateShader()");
    return shader;
}

static void glhDeleteShader(GLuint shader)
{
    GL_ERROR_CHECK("Before glDeleteShader()");
    glDeleteShader(shader);
    GL_ERROR_CHECK("glDeleteShader()");
}

static void glhShaderSource(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length)
{
    GL_ERROR_CHECK("Before glShaderSource()");
    glShaderSource(shader, count, string, length);
    GL_ERROR_CHECK("glShaderSource()");
}

static void glhCompileShader(GLuint shader)
{
    GL_ERROR_CHECK("Before glCompileShader()");
    glCompileShader(shader);
    GL_ERROR_CHECK("glCompileShader()");
}

static void glhGetShaderiv(GLenum shader, GLenum pname, GLint* params)
{
    GL_ERROR_CHECK("Before glGetShaderiv()");
    glGetShaderiv(shader, pname, params);
    GL_ERROR_CHECK("glGetShaderiv()");
}

static void glhGetShaderInfoLog(GLenum shader, GLsizei bufsize, GLsizei* length, GLchar* infoLog)
{
    GL_ERROR_CHECK("Before glGetShaderInfoLog()");
    glGetShaderInfoLog(shader, bufsize, length, infoLog);
    GL_ERROR_CHECK("glGetShaderInfoLog()");
}

// Program
static void glhUseProgram(GLuint program)
{
    GL_ERROR_CHECK("Before glUseProgram()");
    glUseProgram(program);
    GL_ERROR_CHECK("glUseProgram()");
}

// Blending
static void glhBlendFunc(GLenum sfactor, GLenum dfactor)
{
    GL_ERROR_CHECK("Before glBlendFunc()");
    glBlendFunc(sfactor, dfactor);
    GL_ERROR_CHECK("glBlendFunc()");
}

// Fixed Function Procedures
// NOTE: Cannot execute glGetError() while between glBegin() and glEnd()
static void glhBegin(GLenum mode)
{
    GL_ERROR_CHECK("Before glBegin()");
    glBegin(mode);
    //  Can't execute glGetError() after starting
}

static void glhEnd()
{
    // Can't execute glGetError() before ending
    glEnd();
    GL_ERROR_CHECK("glEnd()");
}

static void glhTexCoord2f(GLfloat s, GLfloat t)
{
    glTexCoord2f(s, t);
}

static void glhVertex2f(GLfloat x, GLfloat y)
{
    glVertex2f(x, y);
}

static void glhShadeModel(GLenum model)
{
    GL_ERROR_CHECK("Before glShadeModel()");
    glShadeModel(model);
    GL_ERROR_CHECK("glShadeModel()");
}

// State Setters
static void glhEnable(GLenum cap)
{
    GL_ERROR_CHECK("Before glEnable()");
    glEnable(cap);
    GL_ERROR_CHECK("glEnable()");
}

static void glhDisable(GLenum cap)
{
    GL_ERROR_CHECK("Befor glDisable()");
    glDisable(cap);
    GL_ERROR_CHECK("glDisable()");
}

// State Getters
static bool glhIsEnabled(GLenum cap)
{
    GL_ERROR_CHECK("Before glIsEnabled()");
    bool enabled = glIsEnabled(cap);
    GL_ERROR_CHECK("glIsEnabled()");
    return enabled;
}

static void glhGetIntegerv(GLenum pname, GLint* data)
{
    GL_ERROR_CHECK("Before glGetIntegerv()");
    glGetIntegerv(pname, data);
    GL_ERROR_CHECK("glGetIntegerv()");
}

#endif
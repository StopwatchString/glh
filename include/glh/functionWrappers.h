#ifndef GLH_DEBUG_WRAPPERS_H
#define GLH_DEBUG_WRAPPERS_H

#include "glad/gl.h"
#include "glh/macros.h"

// Framebuffers

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
    GL_ERROR_CHECK("Before glClear");
    glClear(clearTarget);
    GL_ERROR_CHECK("After glClear");
}

static void glhClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    GL_ERROR_CHECK("Before glClearColor");
    glClearColor(r, g, b, a);
    GL_ERROR_CHECK("After glClearColor");
}

#endif
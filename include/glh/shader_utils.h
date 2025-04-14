#ifndef GLH_SHADER_UTILS_H
#define GLH_SHADER_UTILS_H

#include "glh/openglapi.h"

namespace glh {
GLuint compileShader(GLenum type, const char* source);
GLuint createProgram(const char* vertexSource, const char* fragmentSource);
} // End glh

#endif

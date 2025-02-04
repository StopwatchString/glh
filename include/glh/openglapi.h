#ifndef GLH_OPENGL_API_H
#define GLH_OPENGL_API_H

#include "glad/gl.h"

#ifdef _WIN32
    #include "glad/wgl.h"
#elif defined(__linux__)
    #include "glad/glx.h"
#endif

#endif
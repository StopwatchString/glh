#ifndef GLH_H
#define GLH_H

#include "glad/gl.h"

#ifdef _WIN32
#include "glad/wgl.h"
#elif defined(__linux__)
#include "glad/glx.h"
#endif

#include "glh/functionWrappers.h"
#include "glh/utils.h"
#include "glh/Texture2D.h"

//-----------------------------------------------
// glhLoadExtensions()
//-----------------------------------------------
static bool glhLoadExtensions(GLADloadfunc load) {
    return gladLoadGL((GLADloadfunc)load);
}

//-----------------------------------------------
// glhLoadPlatformExtensions()
//-----------------------------------------------
#ifdef _WIN32
static bool glhLoadPlatformExtensions(HDC hdc, GLADloadfunc load) {
    return gladLoadWGL(hdc, (GLADloadfunc)load);
}
#elif defined(__linux__)
// TODO:: Linux Implementation
#endif

#endif
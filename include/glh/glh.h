#ifndef GLH_H
#define GLH_H

#include "glad/gl.h"

#ifdef _WIN32
#include "glad/wgl.h"
#elif defined(__linux__)
#include "glad/glx.h"
#endif

// Top level
#include "glh/functionWrappers.h"
#include "glh/utils.h"

// Classes
#include "glh/classes/Texture2D.h"
#include "glh/classes/D3DInteropTexture2D.h"

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
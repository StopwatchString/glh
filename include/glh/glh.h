#ifndef GLH_H
#define GLH_H

#include "glh/openglapi.h"

// Top level
#include "glh/functionWrappers.h"
#include "glh/utils.h"

// DirectX Interop
#include "glh/direct3d_utils.h"
#include "glh/D3DInteropTexture2D.h"

//-----------------------------------------------
// glhLoadExtensions()
//-----------------------------------------------
static bool glhLoadExtensions(GLADloadfunc load)
{
    return gladLoadGL((GLADloadfunc)load);
}

//-----------------------------------------------
// glhLoadPlatformExtensions()
//-----------------------------------------------
#ifdef _WIN32
static bool glhLoadPlatformExtensions(HDC hdc, GLADloadfunc load)
{
    return gladLoadWGL(hdc, (GLADloadfunc)load);
}
#elif defined(__linux__)
// TODO:: Linux Implementation
#endif

#endif

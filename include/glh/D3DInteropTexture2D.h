/*
 * @file         D3DInteropTexture2D.h
 * @brief        Static functions for creating shared ID3D11Texture2D
 *               objects for use with OpenGL.
 * @creationdate 2025-02-08
 * @lastupdate   2025-02-08
 * @license      MIT License (See LICENSE file for details)
 *
 * Copyright (c) 2025 Mason Speck
 *
 * Description:
 * A group of static functions and structs to facilitate managing
 * an ID3D11Texture2D as a mechanism for GPU-level IPC in OpenGL.
 *
 * Usage:
 * Before using these functions, have a valid instance of Direct3DContext.
 * The definition and handling mechanisms for this are located in
 * direct3d_utils.h, and this context is used to create and manage
 * Direct3D resources.
 *
 * In the process which will create and fill the texture, create and fill in
 * a D3DInteropTextureCreateInfo struct. This will be used to generate an
 * ID3D11Texture2D with the correct parameters. Once this is created, pass
 * it and the Direct3DContext into createD3DInteropTexture(). This will return
 * a D3DInteropTexture struct which will contain all necessary handles for
 * working with this texture as both an OpenGL and Direct3D texture.
 *
 * Within the D3DInteropTexture struct, there is a HANDLE
 * hDxTextureSharedResource. This handle must be shared to the target process
 * so that it can open the same Direct3D texture resource. NOTE: The target
 * process must obtain its own copy of the handle, usually through the use
 * of the DuplicateHandle() function in the Windows API. Simply sharing the
 * same HANDLE value between processes will not suffice. Typically this is
 * achieved by sharing the hDxTextureSharedResource and source process id
 * with the target process, so that it has the tools to create its own handle
 * via DuplicateHandle().
 *
 * Once the target process has obtained the hDxTextureSharedResource, pass it
 * and its Direct3DContext to openD3DInteropTexture().
 *
 * Now both processes have access to the same texture resource, as both an
 * OpenGL and Direct3D texture. The only stipulation in this interoperability
 * is that the driver must be given advanced notice of which API you plan to
 * use before you issue it commands. This is controlled through the interopLock()
 * and interopUnlock() functions. While 'unlocked' the texture is only
 * interactable as a Direct3D texture. While 'locked' the texture is only
 * interactable as an OpenGL texture.
 *
 * interopLock() and interopUnlock() **DO NOT** have an impact on inter-process
 * locking of resources. This is a lock only within the driver to indicate
 * whether the texture is currently in OpenGL mode. This lock is derived from
 * OpenGL extensions.
 */

#ifndef GLH_D3D_INTEROP_TEXTURE2D_H
#define GLH_D3D_INTEROP_TEXTURE2D_H

#include "glh/glh.h"

#include "glh/direct3d_utils.h"

#include <D3D11_1.h>
#include <wrl/client.h> // for Microsoft::WRL::ComPtr template

namespace glh {
namespace d3dinterop {

struct D3DInteropTextureCreateInfo
{
    GLsizei width{0};
    GLsizei height{0};
    bool useMipmaps{false};
};

struct D3DInteropTexture
{
    GLuint openGLTextureName{0};
    ID3D11Texture2D* d3dTexture{nullptr};
    HANDLE hDxTextureSharedResource{NULL};
    HANDLE hWglSharedTextureLock{NULL};
    GLenum internalFormat{GL_NONE};
    GLsizei width{0};
    GLsizei height{0};
    GLsizei mipmapLevels{0};
};

D3DInteropTexture
    createD3DInteropTexture(const D3DInteropTextureCreateInfo& createInfo, const Direct3DContext& context);
D3DInteropTexture openD3DInteropTexture(HANDLE dxSharedResourceHandle, const Direct3DContext& context);
bool destroyD3DInteropTexture(D3DInteropTexture& interopTexture, const Direct3DContext& context);
void interopLock(D3DInteropTexture& interopTexture, const Direct3DContext& context);
void interopUnlock(D3DInteropTexture& interopTexture, const Direct3DContext& context);

} // namespace d3dinterop
} // namespace glh

#endif

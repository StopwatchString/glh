/**
 * @file         D3DInteropTexture2D.cpp
 * @brief        Static functions for creating shared ID3D11Texture2D
 *               objects for use with OpenGL.
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

#include "glh/D3DInteropTexture2D.h"

#include <iostream>
#include <vector>
#include <cmath>

namespace glh {
namespace d3dinterop {

D3DInteropTexture createD3DInteropTexture(const D3DInteropTextureCreateInfo& createInfo, const Direct3DContext& context)
{
    bool sRGB = false;

    D3DInteropTexture interopTexture;
    interopTexture.width = createInfo.width;
    interopTexture.height = createInfo.height;
    interopTexture.mipmapLevels
        = createInfo.useMipmaps ? 1 + static_cast<GLsizei>(std::log2(max(createInfo.width, createInfo.height))) : 1;

    D3D11_TEXTURE2D_DESC texDesc{};
    texDesc.Width = createInfo.width;
    texDesc.Height = createInfo.height;
    texDesc.MipLevels = interopTexture.mipmapLevels;
    texDesc.ArraySize = 1;
    texDesc.Format = sRGB ? DXGI_FORMAT_R8G8B8A8_UNORM_SRGB : DXGI_FORMAT_R8G8B8A8_UNORM;
    texDesc.SampleDesc.Count = 1;
    texDesc.SampleDesc.Quality = 0;
    texDesc.Usage = D3D11_USAGE_DEFAULT;
    texDesc.BindFlags = D3D11_BIND_RENDER_TARGET;
    texDesc.CPUAccessFlags = 0;
    texDesc.MiscFlags = 0;
    texDesc.MiscFlags = D3D11_RESOURCE_MISC_SHARED_NTHANDLE | D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX;

    // Initial image data is empty
    // const D3D11_SUBRESOURCE_DATA* initialData = nullptr;

    // Create initial green color data
    std::vector<uint8_t> greenColorData(createInfo.width * createInfo.height * 4, 0);
    for (size_t i = 0; i < greenColorData.size(); i += 4) {
        greenColorData[i] = 0;       // Red
        greenColorData[i + 1] = 255; // Green
        greenColorData[i + 2] = 0;   // Blue
        greenColorData[i + 3] = 255; // Alpha
    }

    D3D11_SUBRESOURCE_DATA initialData{};
    initialData.pSysMem = greenColorData.data();
    initialData.SysMemPitch = createInfo.width * 4; // RGBA, so 4 bytes per pixel
    initialData.SysMemSlicePitch = 0;

    HRESULT hr = NULL;

    // Create the DirectX2D texture
    hr = context.d3dDevice1->CreateTexture2D(
        &texDesc,                  // pDesc        | Texture description object
        &initialData,              // pInitialData | Initial data for texture
        &interopTexture.d3dTexture // ppTexture2D  | Target pointer for created texture
    );
    if (hr != S_OK) {
        std::cerr << "ERROR createSharedTexture() CreateTexture2D() failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Get the Resource1 interface from the DirectX2D Texture for CreateSharedHandle()
    IDXGIResource1* pResource = NULL;
    hr = interopTexture.d3dTexture->QueryInterface(
        __uuidof(IDXGIResource1), // Interface to retrieve out of COM object (the texture object)
        (void**)&pResource        // Target to place interface in
    );
    if (hr != S_OK) {
        std::cerr << "ERROR createSharedTexture() QueryInterface failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Use CreateSharedHandle() to make a sharable handle betwen OpenGL and DirectX
    // NOTE: This does not create any sort of association between the texture and shared handle yet.
    // The IDXGIResource1 interface was retreived from the texture interface, but that does not inherently link them.
    hr = pResource->CreateSharedHandle(
        NULL,                                                   // pAttributes
        DXGI_SHARED_RESOURCE_READ | DXGI_SHARED_RESOURCE_WRITE, // dwAccess
        NULL,                                                   // lpName
        &interopTexture.hDxTextureSharedResource                // pHandle
    );
    if (hr != S_OK) {
        std::cerr << "ERROR createSharedTexture() CreateTexture2D() failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // We don't need the Resource1 interface anymore, so release it (decrementing its ref counter)
    pResource->Release();

    // Associate the D3DTexture with the generated resource handle
    if (!wglDXSetResourceShareHandleNV(interopTexture.d3dTexture, interopTexture.hDxTextureSharedResource)) {
        std::cerr << "ERROR createSharedTexture() wglDXSetResourceShareHandleNV() failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Make the OpenGL Texture
    glGenTextures(1, &interopTexture.openGLTextureName);

    // This lock synchronizes control of the texture between D3D and OpenGL
    interopTexture.hWglSharedTextureLock = wglDXRegisterObjectNV(
        context.hWglD3DDevice,            // hDevice  |
        interopTexture.d3dTexture,        // dxObject |
        interopTexture.openGLTextureName, // name     |
        GL_TEXTURE_2D,                    // type     |
        WGL_ACCESS_READ_WRITE_NV          // access   |
    );
    if (interopTexture.hWglSharedTextureLock == NULL) {
        std::cerr << "wglDXRegisterObjectNV failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (interopTexture.mipmapLevels > 1) {
        glTextureParameteri(interopTexture.openGLTextureName, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTextureParameteri(interopTexture.openGLTextureName, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else {
        glTextureParameteri(interopTexture.openGLTextureName, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(interopTexture.openGLTextureName, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    return interopTexture;
}

D3DInteropTexture openD3DInteropTexture(HANDLE dxSharedResourceHandle, const Direct3DContext& context)
{
    D3DInteropTexture interopTexture;
    interopTexture.hDxTextureSharedResource = dxSharedResourceHandle;

    if (interopTexture.hDxTextureSharedResource != NULL) {
        HRESULT hr = context.d3dDevice1->OpenSharedResource1(
            interopTexture.hDxTextureSharedResource,
            __uuidof(ID3D11Texture2D),
            reinterpret_cast<void**>(&interopTexture.d3dTexture));
        if (hr != S_OK) {
            std::cout << "Failed to open imported texture" << std::endl;
        }

        // Associate the D3DTexture with the generated resource handle
        if (!wglDXSetResourceShareHandleNV(interopTexture.d3dTexture, interopTexture.hDxTextureSharedResource)) {
            std::cerr << "ERROR createSharedTexture() wglDXSetResourceShareHandleNV() failed!" << std::endl;
            exit(EXIT_FAILURE);
        }

        // Make the OpenGL Texture
        glGenTextures(1, &interopTexture.openGLTextureName);

        // This lock synchronizes control of the texture between D3D and OpenGL
        // You *must* lock and unlock this resource when using the texture in OpenGL for any operation.
        // TBD for DirectX operations.
        interopTexture.hWglSharedTextureLock = wglDXRegisterObjectNV(
            context.hWglD3DDevice,            // hDevice  |
            interopTexture.d3dTexture,        // dxObject |
            interopTexture.openGLTextureName, // name     |
            GL_TEXTURE_2D,                    // type     |
            WGL_ACCESS_READ_WRITE_NV          // access   |
        );
        if (interopTexture.hWglSharedTextureLock == NULL) {
            std::cerr << "wglDXRegisterObjectNV failed" << std::endl;
            exit(EXIT_FAILURE);
        }

        glhTextureParameteri(interopTexture.openGLTextureName, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glhTextureParameteri(interopTexture.openGLTextureName, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    return interopTexture;
}

bool destroyD3DInteropTexture(D3DInteropTexture& interopTexture, const Direct3DContext& context)
{
    return true;
}

void interopLock(D3DInteropTexture& interopTexture, const Direct3DContext& context)
{
    wglDXLockObjectsNV(context.hWglD3DDevice, 1, &interopTexture.hWglSharedTextureLock);
}

void interopUnlock(D3DInteropTexture& interopTexture, const Direct3DContext& context)
{
    wglDXUnlockObjectsNV(context.hWglD3DDevice, 1, &interopTexture.hWglSharedTextureLock);
}

} // namespace d3dinterop
} // namespace glh

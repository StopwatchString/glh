#include "glh/directXInterop/D3DInteropTexture2D.h"

#include "glh/classes/SharedLibraryLoader.h"

#include <iostream>
#include <vector>
#include <cmath>

//-----------------------------------------------
// Export Constructor
//-----------------------------------------------
D3DInteropTexture2D::D3DInteropTexture2D(GLsizei width, GLsizei height, bool useMipmaps, Direct3DContext context) :
    m_Width(width),
    m_Height(height),
    m_InternalFormat(GL_RGBA8),
    m_Levels(useMipmaps ? 1 + static_cast<GLsizei>(std::log2(max(width, height))) : 1),
    m_Context(context)
{
    createSharedTexture();
}

//-----------------------------------------------
// Import Constructor
//-----------------------------------------------
D3DInteropTexture2D::D3DInteropTexture2D(HANDLE importTextureHandle, Direct3DContext context) : m_Context(context)
{
    if (importTextureHandle != NULL) {
        HRESULT hr = context.d3dDevice1->OpenSharedResource1(
            importTextureHandle, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&m_D3DTexture));
        if (hr != S_OK) {
            std::cout << "Failed to open imported texture" << std::endl;
        }

        // Associate the D3DTexture with the generated resource handle
        if (!wglDXSetResourceShareHandleNV(m_D3DTexture, importTextureHandle)) {
            std::cerr << "ERROR createSharedTexture() wglDXSetResourceShareHandleNV() failed!" << std::endl;
            exit(EXIT_FAILURE);
        }

        // Make the OpenGL Texture
        glGenTextures(1, &m_OpenGLTextureName);

        // This lock synchronizes control of the texture between D3D and OpenGL
        // You *must* lock and unlock this resource when using the texture in OpenGL for any operation.
        // TBD for DirectX operations.
        m_hWglSharedTextureLock = wglDXRegisterObjectNV(
            m_Context.hWglD3DDevice, // hDevice  |
            m_D3DTexture,            // dxObject |
            m_OpenGLTextureName,     // name     |
            GL_TEXTURE_2D,           // type     |
            WGL_ACCESS_READ_WRITE_NV // access   |
        );
        if (m_hWglSharedTextureLock == NULL) {
            std::cerr << "wglDXRegisterObjectNV failed" << std::endl;
            exit(EXIT_FAILURE);
        }

        glhTextureParameteri(m_OpenGLTextureName, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glhTextureParameteri(m_OpenGLTextureName, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}

//-----------------------------------------------
// Destructor
//-----------------------------------------------
D3DInteropTexture2D::~D3DInteropTexture2D()
{
    // TODO
    if (m_Context.hWglD3DDevice != NULL) {
        interopUnlock();
    }
}

//-----------------------------------------------
// bind()
//-----------------------------------------------
void D3DInteropTexture2D::bind() const
{
    glhBindTexture(GL_TEXTURE_2D, m_OpenGLTextureName);
}

//-----------------------------------------------
// unbind()
//-----------------------------------------------
void D3DInteropTexture2D::unbind() const
{
    glhBindTexture(GL_TEXTURE_2D, 0);
}

//-----------------------------------------------
// uploadData()
//-----------------------------------------------
void D3DInteropTexture2D::uploadData(GLenum sourceFormat, GLenum sourceDataType, const void* sourceData)
{
    glhTextureSubImage2D(m_OpenGLTextureName, 0, 0, 0, m_Width, m_Height, sourceFormat, sourceDataType, sourceData);
    if (m_Levels > 1) {
        glhGenerateTextureMipmap(m_OpenGLTextureName);
    }
    m_HasData = true;
}

//-----------------------------------------------
// setParameter()
//-----------------------------------------------
void D3DInteropTexture2D::setParameter(GLenum parameterName, GLint parameter)
{
    glhTextureParameteri(m_OpenGLTextureName, parameterName, parameter);
}

//-----------------------------------------------
// interopLock()
//-----------------------------------------------
void D3DInteropTexture2D::interopLock()
{
    wglDXLockObjectsNV(m_Context.hWglD3DDevice, 1, &m_hWglSharedTextureLock);
}

//-----------------------------------------------
// interopUnlock()
//-----------------------------------------------
void D3DInteropTexture2D::interopUnlock()
{
    wglDXUnlockObjectsNV(m_Context.hWglD3DDevice, 1, &m_hWglSharedTextureLock);
}

//-----------------------------------------------
// createSharedTexture()
//-----------------------------------------------
void D3DInteropTexture2D::createSharedTexture()
{
    bool sRGB = false;

    D3D11_TEXTURE2D_DESC texDesc{};
    texDesc.Width = m_Width;
    texDesc.Height = m_Height;
    texDesc.MipLevels = m_Levels;
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
    std::vector<uint8_t> greenColorData(m_Width * m_Height * 4, 0);
    for (size_t i = 0; i < greenColorData.size(); i += 4) {
        greenColorData[i] = 0;       // Red
        greenColorData[i + 1] = 255; // Green
        greenColorData[i + 2] = 0;   // Blue
        greenColorData[i + 3] = 255; // Alpha
    }

    D3D11_SUBRESOURCE_DATA initialData{};
    initialData.pSysMem = greenColorData.data();
    initialData.SysMemPitch = m_Width * 4; // RGBA, so 4 bytes per pixel
    initialData.SysMemSlicePitch = 0;

    HRESULT hr = NULL;

    // Create the DirectX2D texture
    hr = m_Context.d3dDevice1->CreateTexture2D(
        &texDesc,     // pDesc        | Texture description object
        &initialData, // pInitialData | Initial data for texture
        &m_D3DTexture // ppTexture2D  | Target pointer for created texture
    );
    if (hr != S_OK) {
        std::cerr << "ERROR createSharedTexture() CreateTexture2D() failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Get the Resource1 interface from the DirectX2D Texture for CreateSharedHandle()
    IDXGIResource1* pResource = NULL;
    hr = m_D3DTexture->QueryInterface(
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
        &m_hDxTextureSharedResource                             // pHandle
    );
    if (hr != S_OK) {
        std::cerr << "ERROR createSharedTexture() CreateTexture2D() failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // We don't need the Resource1 interface anymore, so release it (decrementing its ref counter)
    pResource->Release();

    // Associate the D3DTexture with the generated resource handle
    if (!wglDXSetResourceShareHandleNV(m_D3DTexture, m_hDxTextureSharedResource)) {
        std::cerr << "ERROR createSharedTexture() wglDXSetResourceShareHandleNV() failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Make the OpenGL Texture
    glGenTextures(1, &m_OpenGLTextureName);

    // This lock synchronizes control of the texture between D3D and OpenGL
    // You *must* lock and unlock this resource when using the texture in OpenGL for any operation.
    // TBD for DirectX operations.
    m_hWglSharedTextureLock = wglDXRegisterObjectNV(
        m_Context.hWglD3DDevice, // hDevice  |
        m_D3DTexture,            // dxObject |
        m_OpenGLTextureName,     // name     |
        GL_TEXTURE_2D,           // type     |
        WGL_ACCESS_READ_WRITE_NV // access   |
    );
    if (m_hWglSharedTextureLock == NULL) {
        std::cerr << "wglDXRegisterObjectNV failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (m_Levels > 1) {
        glTextureParameteri(m_OpenGLTextureName, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTextureParameteri(m_OpenGLTextureName, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else {
        glTextureParameteri(m_OpenGLTextureName, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_OpenGLTextureName, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}
#ifndef GLH_D3D_INTEROP_TEXTURE2D_H
#define GLH_D3D_INTEROP_TEXTURE2D_H

#include "glh/glh.h"

#include <D3D11_1.h>
#include <wrl/client.h> // for Microsoft::WRL::ComPtr template

class D3DInteropTexture2D
{
public:
    D3DInteropTexture2D(GLsizei width, GLsizei height, bool useMipmaps);
    ~D3DInteropTexture2D();

    D3DInteropTexture2D(const D3DInteropTexture2D& other) = delete;
    D3DInteropTexture2D& operator=(const D3DInteropTexture2D& other) = delete;

    D3DInteropTexture2D(D3DInteropTexture2D&& other) noexcept;
    D3DInteropTexture2D& operator=(D3DInteropTexture2D&& other) noexcept;

    // Binds the texture on GL_TEXTURE_2D
    void bind() const;
    // Binds '0' on GL_TEXTURE_2D
    void unbind() const;

    // Upload data into the texture
    // sourceFormat- The storage format of the data being uploaded (ex: GL_RGBA)
    // sourceDataType- The data type of the data being uploaded (ex: GL_UNSIGNED_BYTE)
    // sourceData- Pointer to the data being uploaded
    void uploadData(GLenum sourceFormat, GLenum sourceDataType, const void* sourceData);

    // Set a parameter on the texture
    void setParameter(GLenum parameterName, GLint parameter);

    // Get direct OpenGL texture handle
    GLuint handle() const { return m_OpenGLTextureName; }
    // Returns true if texture handle != 0
    bool isValid() const { return m_OpenGLTextureName != 0; }
    // Returns true if data has been uploaded into texture
    bool hasData() const { return m_HasData; }
    // Returns the internal storage format of the texture
    GLenum internalFormat() const { return m_InternalFormat; }
    // Returns texture width
    GLsizei width() const { return m_Width; }
    // Returns texture height
    GLsizei height() const { return m_Height; }
    // Returns number of mipmaps levels
    GLsizei levels() const { return m_Levels; }
    // Returns true if texture has mipmaps
    bool hasMipmaps() const { return m_Levels > 1; }

    // Obtains a lock on the Graphics API interop lock.
    // The texture is only functional while this lock is active.
    void interopLock();
    // Unlocks the Graphics API interop lock
    void interopUnlock();

    static bool direct3DIsInit() { return d3dDevice1 != NULL && d3dDeviceContext1 != NULL && hWglD3DDevice != NULL; }
    static void initDirect3D();
    static void shutdownDirect3D();
private:
    bool m_HasData{ false };
    GLenum m_InternalFormat{ GL_NONE };
    GLsizei m_Width{ 0 };
    GLsizei m_Height{ 0 };
    GLsizei m_Levels{ 0 };

    // D3DState
    static Microsoft::WRL::ComPtr<ID3D11Device1> d3dDevice1;
    static Microsoft::WRL::ComPtr<ID3D11DeviceContext1> d3dDeviceContext1;
    static HANDLE hWglD3DDevice;

    // Texture handles
    GLuint m_OpenGLTextureName{ 0 };
    ID3D11Texture2D* m_D3DTexture{ nullptr };
    HANDLE hSharedTexture{ NULL };
    HANDLE hSharedTextureLock{ NULL };
    void createSharedTexture();
};

#endif
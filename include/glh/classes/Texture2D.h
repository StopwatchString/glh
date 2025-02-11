#ifndef GLH_TEXTURE2D_H
#define GLH_TEXTURE2D_H

#include "glh/functionWrappers.h"

class Texture2D
{
public:
    Texture2D(GLenum internalFormat, GLsizei width, GLsizei height, bool useMipmaps);
    ~Texture2D();

    Texture2D(const Texture2D& other) = delete;
    Texture2D& operator=(const Texture2D& other) = delete;

    Texture2D(Texture2D&& other) noexcept;
    Texture2D& operator=(Texture2D&& other) noexcept;

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
    GLuint handle() const { return m_TextureName; }
    // Returns true if texture handle != 0
    bool isValid() const { return m_TextureName != 0; }
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

private:
    GLuint m_TextureName{0};
    bool m_HasData{false};

    GLenum m_InternalFormat{GL_NONE};
    GLsizei m_Width{0};
    GLsizei m_Height{0};
    GLsizei m_Levels{0};
};

#endif
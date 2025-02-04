#include "glh/classes/Texture2D.h"

#include <algorithm>
#include <cmath>
//-----------------------------------------------
// Parameterized Constructor
//-----------------------------------------------
Texture2D::Texture2D(GLenum internalFormat, GLsizei width, GLsizei height, bool useMipmaps) :
    m_InternalFormat(internalFormat),
    m_Width(width),
    m_Height(height),
    m_Levels(useMipmaps ? 1 + static_cast<GLsizei>(std::log2(max(width, height))) : 1)
{
    // Create and bind so that the texture is associated as a 2D texture
    glhGenTextures(1, &m_TextureName);
    bind();
    unbind();

    // Allocate storage
    glhTextureStorage2D(m_TextureName, m_Levels, m_InternalFormat, m_Width, m_Height);

    // Set default parameters
    GLenum minFilterVal = useMipmaps ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR;
    setParameter(GL_TEXTURE_MIN_FILTER, minFilterVal);
    setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
}

//-----------------------------------------------
// Move Constructor
//-----------------------------------------------
Texture2D::Texture2D(Texture2D&& other) noexcept :
    m_TextureName(other.m_TextureName),
    m_HasData(other.m_HasData),
    m_InternalFormat(other.m_InternalFormat),
    m_Width(other.m_Width),
    m_Height(other.m_Height),
    m_Levels(other.m_Levels)
{
    // Clear their data
    other.m_TextureName = 0;
    other.m_HasData = false;
    other.m_InternalFormat = GL_NONE;
    other.m_Width = 0;
    other.m_Height = 0;
    other.m_Levels = 0;
}

//-----------------------------------------------
// Move Assignment
//-----------------------------------------------
Texture2D& Texture2D::operator=(Texture2D&& other) noexcept
{
    if (this != &other) {
        // Free current resources
        if (m_TextureName != 0) { glhDeleteTextures(1, &m_TextureName); }

        // Move ownership
        m_TextureName = other.m_TextureName;
        m_HasData = other.m_HasData;
        m_InternalFormat = other.m_InternalFormat;
        m_Width = other.m_Width;
        m_Height = other.m_Height;
        m_Levels = other.m_Levels;

        // Clear their data
        other.m_TextureName = 0;
        other.m_HasData = false;
        other.m_InternalFormat = GL_NONE;
        other.m_Width = 0;
        other.m_Height = 0;
        other.m_Levels = 0;
    }
    return *this;
}

//-----------------------------------------------
// Destructor
//-----------------------------------------------
Texture2D::~Texture2D()
{
    glhDeleteTextures(1, &m_TextureName);
}

//-----------------------------------------------
// bind()
//-----------------------------------------------
void Texture2D::bind() const
{
    glhBindTexture(GL_TEXTURE_2D, m_TextureName);
}

//-----------------------------------------------
// unbind()
//-----------------------------------------------
void Texture2D::unbind() const
{
    glhBindTexture(GL_TEXTURE_2D, 0);
}

//-----------------------------------------------
// uploadData()
//-----------------------------------------------
void Texture2D::uploadData(GLenum sourceFormat, GLenum sourceDataType, const void* sourceData)
{
    glhTextureSubImage2D(m_TextureName, 0, 0, 0, m_Width, m_Height, sourceFormat, sourceDataType, sourceData);
    if (m_Levels > 1) { glhGenerateTextureMipmap(m_TextureName); }
    m_HasData = true;
}

//-----------------------------------------------
// setParameter()
//-----------------------------------------------
void Texture2D::setParameter(GLenum parameterName, GLint parameter)
{
    glhTextureParameteri(m_TextureName, parameterName, parameter);
}
#ifndef GLH_SHADER_H
#define GLH_SHADER_H

#include "glh/functionWrappers.h"

#include <string>
#include <array>

class Shader
{
    static constexpr uint32_t INFO_LOG_SIZE = 1024;

public:
    Shader(GLenum shaderType, const char* source);
    ~Shader();

    GLenum type() { return m_ShaderType; }
    GLuint handle() { return m_ShaderName; }

    bool isCompiled();
    std::string getInfoLog();

private:
    GLenum m_ShaderType{ GL_NONE };
    GLuint m_ShaderName{ 0 };
};

#endif
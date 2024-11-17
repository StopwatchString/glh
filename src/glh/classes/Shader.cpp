#include "glh/classes/Shader.h"

//-----------------------------------------------
// Constructor
//-----------------------------------------------
Shader::Shader(GLenum shaderType, const char* source)
    : m_ShaderType(shaderType)
{
    m_ShaderName = glhCreateShader(shaderType);
    glhShaderSource(m_ShaderName, 1, &source, NULL);
    glhCompileShader(m_ShaderName);
}

//-----------------------------------------------
// Destructor
//-----------------------------------------------
Shader::~Shader()
{
    glhDeleteShader(m_ShaderName);
}

//-----------------------------------------------
// isCompiled()
//-----------------------------------------------
bool Shader::isCompiled()
{
    GLint compileStatus = 0;
    glhGetShaderiv(m_ShaderName, GL_COMPILE_STATUS, &compileStatus);
    return compileStatus == GL_TRUE;
}

//-----------------------------------------------
// getError()
//-----------------------------------------------
std::string Shader::getInfoLog()
{
    std::array<char, INFO_LOG_SIZE> infoLog;
    GLsizei length = 0;
    glhGetShaderInfoLog(m_ShaderName, INFO_LOG_SIZE, &length, infoLog.data());
    return std::string(infoLog.data());
}
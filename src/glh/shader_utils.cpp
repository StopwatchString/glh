#include "glh/shader_utils.h"

#include "glh/functionWrappers.h"

#include <array>
#include <iostream>

namespace glh {
constexpr size_t INFO_LOG_SIZE = 512;

GLuint compileShader(GLenum type, const char* source)
{
    GLuint shader = glhCreateShader(type);
    glhShaderSource(shader, 1, &source, nullptr);
    glhCompileShader(shader);

    GLint success{ 0 };
    glhGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::array<char, INFO_LOG_SIZE> log{};
        glhGetShaderInfoLog(shader, log.size(), nullptr, log.data());
        std::cerr << "Shader compilation failed: \n" << log.data() << std::endl;
    }
    return shader;
}

GLuint createProgram(const char* vertexSource, const char* fragmentSource)
{
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    GLuint program = glhCreateProgram();
    glhAttachShader(program, vertexShader);
    glhAttachShader(program, fragmentShader);
    glhLinkProgram(program);

    GLint success{ 0 };
    glhGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        std::array<char, INFO_LOG_SIZE> log{};
        glhGetProgramInfoLog(program, INFO_LOG_SIZE, nullptr, log.data());
        std::cerr << "Shader linking failed: \n" << log.data() << std::endl;
    }

    glhDeleteShader(vertexShader);
    glhDeleteShader(fragmentShader);
    return program;
}
} // End glh

#ifndef GLH_SHADER_H
#define GLH_SHADER_H

#include "../glad/gl.h"

#include <string>

namespace glh {
    namespace shader {
        // Valid Shader Types:
        // GL_COMPUTE_SHADER
        // GL_VERTEX_SHADER
        // GL_TESS_CONTROL_SHADER
        // GL_TESS_EVALUATION_SHADER
        // GL_GEOMETRY_SHADER
        // GL_FRAGMENT_SHADER
        GLuint create(GLenum shaderType);

        void destroy(GLuint shader);

        void attachSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);

        void compileShader(GLuint shader);

        bool isCompiled(GLuint shader);

        const std::string getShaderInfoLog(GLuint shader);
    }
}

#endif
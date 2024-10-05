#include "glh/Shader.h"
#include "glh/macros.h"

#include <iostream>
#include <array>

namespace glh {
    namespace shader {
        GLuint create(GLenum shaderType) {
            GL_ERROR_CHECK("shader", "create", "Pre-existing");

            GLuint shader = glCreateShader(shaderType);
            GL_ERROR_CHECK("shader", "create", "glCreateShader");

            return shader;
        }

        void destroy(GLuint shader) {
            GL_ERROR_CHECK("shader", "destroy", "Pre-existing");

            glDeleteShader(shader);
            GL_ERROR_CHECK("shader", "destroy", "glDeleteShader");
        }

        void attachSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) {
            GL_ERROR_CHECK("shader", "attachSource", "Pre-existing");

            glShaderSource(shader, count, string, length);
            GL_ERROR_CHECK("shader", "attachSource", "glShaderSource");
        }

        void compileShader(GLuint shader) {
            GL_ERROR_CHECK("shader", "compileShader", "Pre-existing");

            glCompileShader(shader);
            GL_ERROR_CHECK("shader", "compileShader", "glCompileShader");
        }

        bool isCompiled(GLuint shader) {
            GL_ERROR_CHECK("shader", "isCompiled", "Pre-existing");

            GLint status;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
            GL_ERROR_CHECK("shader", "isCompiled", "glGetShaderiv");

            return status == GL_TRUE;
        }

        const std::string getShaderInfoLog(GLuint shader) {
            GL_ERROR_CHECK("shader", "getShaderInfoLog", "Pre-existing");

            std::array<char, 1024> infoLog;
            GLsizei length = 0;
            glGetShaderInfoLog(shader, 1024, &length, infoLog.data());
            GL_ERROR_CHECK("shader", "getShaderInfoLog", "glGetShaderInfoLog");

            return std::string(infoLog.data());
        }
    }
}
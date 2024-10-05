#include "glh/Program.h"
#include "glh/macros.h"

#include <array>

namespace glh {
    namespace program {
        GLuint create() {
            GL_ERROR_CHECK("program", "create", "Pre-existing");

            GLuint program = glCreateProgram();
            GL_ERROR_CHECK("program", "create", "glCreateProgram");

            return program;
        }

        void destroy(GLuint& program) {
            GL_ERROR_CHECK("program", "destroy", "Pre-existing");

            glDeleteProgram(program);
            GL_ERROR_CHECK("program", "destroy", "glDeleteProgram");
        }

        void bind(GLuint program) {
            GL_ERROR_CHECK("program", "bind", "Pre-existing");

            glUseProgram(program);
            GL_ERROR_CHECK("program", "bind", "glUseProgram");
        }

        void attachShader(GLuint program, GLuint shader) {
            GL_ERROR_CHECK("program", "attachShader", "Pre-existing");

            glAttachShader(program, shader);
            GL_ERROR_CHECK("program", "attachShader", "glAttachShader");
        }

        void detachShader(GLuint program, GLuint shader) {
            GL_ERROR_CHECK("program", "detachShader", "Pre-existing");

            glDetachShader(program, shader);
            GL_ERROR_CHECK("program", "detachShader", "glDetachShader");
        }

        void linkProgram(GLuint program) {
            GL_ERROR_CHECK("program", "linkProgram", "Pre-existing");

            glLinkProgram(program);
            GL_ERROR_CHECK("program", "linkProgram", "glLinkProgram");
        }

        bool isLinked(GLuint program)
        {
            GL_ERROR_CHECK("program", "isLinked", "Pre-existing");

            GLint status;
            glGetProgramiv(program, GL_LINK_STATUS, &status);
            GL_ERROR_CHECK("program", "isLinked", "glGetShaderiv");

            return status == GL_TRUE;
        }

        const std::string getProgramInfoLog(GLuint program)
        {
            GL_ERROR_CHECK("program", "getProgramInfoLog", "Pre-existing");

            std::array<char, 1024> infoLog;
            GLsizei length = 0;
            glGetShaderInfoLog(program, 1024, &length, infoLog.data());
            GL_ERROR_CHECK("program", "getProgramInfoLog", "glGetShaderInfoLog");

            return std::string(infoLog.data());
        }

        GLint getAttribLocation(GLuint program, const GLchar* name) {
            GL_ERROR_CHECK("program", "getAttribLocation", "Pre-existing");

            GLint location = glGetAttribLocation(program, name);
            GL_ERROR_CHECK("program", "getAttribLocation", "glGetAttribLocation");

            return location;
        }

        GLint getUniformLocation(GLuint program, const GLchar* name) {
            GL_ERROR_CHECK("program", "getUniformLocation", "Pre-existing");

            GLint location = glGetUniformLocation(program, name);
            GL_ERROR_CHECK("program", "getUniformLocation", "glGetUniformLocation");

            return location;
        }
    }
}
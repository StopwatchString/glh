#ifndef GLH_PROGRAM_H
#define GLH_PROGRAM_H

#include "../glad/gl.h"

#include <string>

namespace glh {
    namespace program {
        GLuint create();

        void destroy(GLuint& program);

        void bind(GLuint program);

        void attachShader(GLuint program, GLuint shader);
        void detachShader(GLuint program, GLuint shader);

        void linkProgram(GLuint program);
        bool isLinked(GLuint program);
        const std::string getProgramInfoLog(GLuint program);

        GLint getAttribLocation(GLuint program, const GLchar* name);
        GLint getUniformLocation(GLuint program, const GLchar* name);

    }
}

#endif
#ifndef GLH_EBO_H
#define GLH_EBO_H

#include "../glad/gl.h"

namespace glh {
    namespace EBO {
        void create(GLuint& EBO);
        void create(GLsizei num, GLuint* EBOArray);

        void destroy(GLuint& EBO);
        void destroy(GLsizei num, GLuint* EBOArray);

        void bind(GLuint EBO);

        void allocateBuffer(GLsizeiptr size, const void* data, GLenum usage, GLuint expectedBoundEBO = 0);
        void updateBuffer(GLintptr offset, GLsizeiptr size, const void* data, GLuint expectedBoundEBO = 0);
    }
}

#endif
#include "glh/PBO.h"
#include "glh/macros.h"

#include <iostream>

namespace glh {
    namespace PBO {
        void create(GLuint& PBO) {
            GL_ERROR_CHECK("PBO", "create", "Pre-existing");

            glGenBuffers(1, &PBO);
            GL_ERROR_CHECK("PBO", "create", "glGenBuffers");
        }

        void create(GLsizei num, GLuint* PBOArray) {
            GL_ERROR_CHECK("PBO", "create", "Pre-existing");

            glGenBuffers(num, PBOArray);
            GL_ERROR_CHECK("PBO", "create", "glGenBuffers");
        }

        void destroy(GLuint& PBO) {
            GL_ERROR_CHECK("PBO", "destroy", "Pre-existing");

            glDeleteBuffers(1, &PBO);
            GL_ERROR_CHECK("PBO", "destroy", "glDeleteBuffers");
        }

        void destroy(GLsizei num, GLuint* PBOArray) {
            GL_ERROR_CHECK("PBO", "destroy", "Pre-existing");

            glDeleteBuffers(num, PBOArray);
            GL_ERROR_CHECK("PBO", "destroy", "glDeleteBuffers");
        }

        void bindForUpload(GLuint PBO) {
            GL_ERROR_CHECK("PBO", "bindForUpload", "Pre-existing");

            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, PBO);
            GL_ERROR_CHECK("PBO", "bindForUpload", "glBindBuffer");
        }

        void bindForDownload(GLuint PBO) {
            GL_ERROR_CHECK("PBO", "bindForDownload", "Pre-existing");

            glBindBuffer(GL_PIXEL_PACK_BUFFER, PBO);
            GL_ERROR_CHECK("PBO", "bindForDownload", "glBindBuffer");
        }

        void allocateBuffer(GLsizeiptr size, const void* data, GLenum usage, GLuint expectedBoundPBO) {
            GL_ERROR_CHECK("PBO", "allocateBuffer", "Pre-existing");

            glBufferData(GL_ARRAY_BUFFER, size, data, usage);
            GL_ERROR_CHECK("PBO", "allocateBuffer", "glBufferData");
        }

        void updateBuffer(GLintptr offset, GLsizeiptr size, const void* data, GLuint expectedBoundPBO) {
            GL_ERROR_CHECK("PBO", "updateBuffer", "Pre-existing");

            glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
            GL_ERROR_CHECK("PBO", "updateBuffer", "glBufferSubData");
        }

        void downloadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* data) {
            GL_ERROR_CHECK("PBO", "downloadPixels", "Pre-existing");

            glReadPixels(x, y, width, height, format, type, data);
            GL_ERROR_CHECK("PBO", "downloadPixels", "glReadPixels");
        }

        void uploadPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data) {
            GL_ERROR_CHECK("PBO", "uploadPixels", "Pre-existing");

            glDrawPixels(width, height, format, type, data);
            GL_ERROR_CHECK("PBO", "uploadPixels", "glDrawPixels");
        }
    }
}
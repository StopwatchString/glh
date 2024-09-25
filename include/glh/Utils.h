#ifndef GLH_UTILS_H
#define GLH_UTILS_H

#include <string>

#include "../glad/gl.h"

#ifdef _WIN32
#include "../glad/wgl.h"
#elif defined(__linux__)
#include "../glad/glx.h"
#endif

namespace glh {
    namespace utils {
        const char* loadFile(const std::string& filename);

        // Only checks for errors when NDEBUG is not defined
        void glErrorCheck(const std::string& identifier);

        typedef GLADloadfunc GLHloadfunc;
        bool loadExtensions(GLHloadfunc load);

#ifdef _WIN32
        bool loadPlatformExtensions(HDC hdc, GLHloadfunc load);
#elif defined(__linux__)
        //TODO LINUX IMPL
#endif
    }
}

#endif
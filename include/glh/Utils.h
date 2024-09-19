#ifndef GLH_UTILS_H
#define GLH_UTILS_H

#include <string>

#include "../glad/gl.h"

namespace glh {
    namespace utils {
        const char* loadFile(const std::string& filename);

        // Only checks for errors when NDEBUG is not defined
        void glErrorCheck(const std::string& identifier);
    }
}

#endif
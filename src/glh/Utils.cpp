#include "glh/Utils.h"
#include "glh/macros.h"

#include <fstream>
#include <vector>
#include <string>

namespace glh {
    namespace utils {
        const char* loadFile(const std::string& filename) {
            std::ifstream file(filename, std::ios::binary | std::ios::ate);
            if (!file.is_open()) {
                return nullptr; // File couldn't be opened
            }

            std::streamsize size = file.tellg();
            file.seekg(0, std::ios::beg);

            std::vector<char> buffer(size + 1);
            if (!file.read(buffer.data(), size)) {
                return nullptr; // Read failed
            }

            buffer[size] = '\0'; // Null-terminate the buffer

            char* result = new char[size + 1];
            std::copy(buffer.begin(), buffer.end(), result);

            return result;
        }

        void glErrorCheck(const std::string& identifier) {
            GL_ERROR_CHECK("utils", "glErrorCheck", identifier);
        }

        bool loadExtensions(GLHloadfunc load) {
            return gladLoadGL((GLADloadfunc) load);
        }

#ifdef _WIN32
        bool loadPlatformExtensions(HDC hdc, GLHloadfunc load) {
            return gladLoadWGL(hdc, (GLADloadfunc) load);
        }
#elif defined(__linux__)
        //TODO LINUX IMPL
#endif

    }
}
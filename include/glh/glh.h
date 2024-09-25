#ifndef GLH_H
#define GLH_H

#include "../glad/gl.h"

#ifdef _WIN32
#include "../glad/wgl.h"
#elif defined(__linux__)
#include "../glad/glx.h"
#endif

#include "./Shader.h"
#include "./Program.h"
#include "./Texture.h"
#include "./VAO.h"
#include "./VBO.h"
#include "./UBO.h"
#include "./EBO.h"
#include "./PBO.h"
#include "./Utils.h"

#endif
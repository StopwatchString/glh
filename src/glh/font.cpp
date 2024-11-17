#include "glh/font.h"

#include "glh/openglapi.h"
#include "glh/functionWrappers.h"

#define RFONT_IMPLEMENTATION
#include "glh/RFont/RFont.h"
#include "glh/RFont/DejaVuSans.h"

static RFont_font* font = nullptr;

// RFont doesn't cleanly preserve OpenGL state between calls.
// push/popOpenGLState() ensure that state is undisturbed.
GLint vao{ 0 };
GLint vbo{ 0 };
GLint ebo{ 0 };
GLint activeTextureUnit{ 0 };
GLint boundTexture2D{ 0 };
bool texture2DEnabled{ false };
bool depthTestEnabled{ false };
bool cullFaceEnabled{ false };
bool blendEnabled{ false };
GLint blendSrcFactor{ 0 };
GLint blendDstFactor{ 0 };
GLint shadeModel{ 0 };
GLint program{ 0 };

//-----------------------------------------------
// pushOpenGLState()
//-----------------------------------------------
void pushOpenGLState()
{
    glhGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vao);
    glhGetIntegerv(GL_ARRAY_BUFFER_BINDING, &vbo);
    glhGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &ebo);
    glhGetIntegerv(GL_ACTIVE_TEXTURE, &activeTextureUnit);
    glhGetIntegerv(GL_TEXTURE_BINDING_2D, &boundTexture2D);
    texture2DEnabled = glhIsEnabled(GL_TEXTURE_2D);
    depthTestEnabled = glhIsEnabled(GL_DEPTH_TEST);
    cullFaceEnabled = glhIsEnabled(GL_CULL_FACE);
    blendEnabled = glhIsEnabled(GL_BLEND);
    glhGetIntegerv(GL_BLEND_SRC_ALPHA, &blendSrcFactor);
    glhGetIntegerv(GL_BLEND_DST_ALPHA, &blendDstFactor);
    glhGetIntegerv(GL_SHADE_MODEL, &shadeModel);
    glhGetIntegerv(GL_CURRENT_PROGRAM, &program);
}

//-----------------------------------------------
// popOpenGLState()
//-----------------------------------------------
void popOpenGLState()
{
    glhBindVertexArray(vao);
    glhBindBuffer(GL_ARRAY_BUFFER, vbo);
    glhBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glhActiveTexture(activeTextureUnit);
    glhBindTexture(GL_TEXTURE_2D, boundTexture2D);
    texture2DEnabled ? glhEnable(GL_TEXTURE_2D) : glhDisable(GL_TEXTURE_2D);
    depthTestEnabled ? glhEnable(GL_DEPTH_TEST) : glhDisable(GL_DEPTH_TEST);
    cullFaceEnabled ? glhEnable(GL_CULL_FACE) : glhDisable(GL_CULL_FACE);
    blendEnabled ? glhEnable(GL_BLEND) : glhDisable(GL_BLEND);
    glhBlendFunc(blendSrcFactor, blendDstFactor);
    glhShadeModel(shadeModel);
    glhUseProgram(program);
}

//-----------------------------------------------
// glhInitFont()
//-----------------------------------------------
void glhInitFont(size_t framebufferWidth, size_t framebufferHeight)
{
    // RFont_init changes bound VAO
    pushOpenGLState();

    RFont_init(framebufferWidth, framebufferHeight);
    font = RFont_font_init_data((u8*)DejaVuSans, false);

    popOpenGLState();
}

//-----------------------------------------------
// glhFreeFont()
//-----------------------------------------------
void glhFreeFont()
{
    if (font != nullptr) {
        RFont_font_free(font);
        font = nullptr;
        RFont_close();
    }
}

//-----------------------------------------------
// glhDrawText()
//-----------------------------------------------
void glhDrawText(const std::string& text, float x, float y, float spacing)
{
    pushOpenGLState();

    if (font != nullptr) {
        RFont_draw_text_spacing(font, text.c_str(), x, y, text.size(), spacing);
    }

    popOpenGLState();
}

//-----------------------------------------------
// glhSetTextColor()
//-----------------------------------------------
void glhSetTextColor(float r, float g, float b, float a)
{
    if (font != nullptr) {
        RFont_set_color(r, g, b, a);
    }
}

//-----------------------------------------------
// glhUpdateFontFramebuffer()
//-----------------------------------------------
void glhUpdateFontFramebuffer(size_t width, size_t height)
{
    RFont_update_framebuffer(width, height);
}
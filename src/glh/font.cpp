#include "glh/font.h"

#include "glh/glh.h"

#define RFONT_IMPLEMENTATION
#include "glh/RFont/RFont.h"
#include "glh/RFont/DejaVuSans.h"

static RFont_font* font = nullptr;

//-----------------------------------------------
// glhInitFont()
//-----------------------------------------------
void glhInitFont(size_t framebufferWidth, size_t framebufferHeight)
{
    RFont_init(framebufferWidth, framebufferHeight);
    font = RFont_font_init_data((u8*)DejaVuSans, false);
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
    if (font != nullptr) {
        RFont_draw_text_spacing(font, text.c_str(), x, y, text.size(), spacing);
    }
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
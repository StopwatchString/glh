#ifndef GLH_FONT_H
#define GLH_FONT_H

#include <string>

struct FontRect {
    size_t width{ 0 };
    size_t height{ 0 };
};

void glhInitFont(size_t framebufferWidth, size_t framebufferHeight);
void glhFreeFont();
FontRect glhDrawText(const std::string& text, float x, float y, float size, float spacing = 0.0f);
void glhSetTextColor(float r, float g, float b, float a);
void glhUpdateFontFramebuffer(size_t width, size_t height);
FontRect glhGetTextSize(const std::string& text, float size);

#endif
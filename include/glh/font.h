#ifndef GLH_FONT_H
#define GLH_FONT_H

#include <string>

void glhInitFont(size_t framebufferWidth, size_t framebufferHeight);
void glhFreeFont();
void glhDrawText(const std::string& text, float x, float y, float size, float spacing = 0.0f);
void glhSetTextColor(float r, float g, float b, float a);
void glhUpdateFontFramebuffer(size_t width, size_t height);

#endif
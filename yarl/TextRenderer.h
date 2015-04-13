#pragma once

#include "SDLSurface.h"


class TextRenderer
{
    SDLSurface m_surface;
    int m_characterHeight;
    int m_characterWidth;
public:
    explicit TextRenderer(const std::string& fontFile);
    ~TextRenderer();

    void RenderCharacter(unsigned char c, int x, int y, const SDLSurface& target, Color color);
};


#pragma once

#include "SDLSurface.h"


class TextRenderer
{
    int m_characterHeight;
    int m_characterWidth;
    
    SDLTexture m_texture;
    const SDLRenderer& m_renderer;
public:
    TextRenderer(const std::string& fontFile, const SDLRenderer& renderer);
    ~TextRenderer();

    void RenderCharacter(unsigned char c, int x, int y, const SDLSurface& target, Color color);
};


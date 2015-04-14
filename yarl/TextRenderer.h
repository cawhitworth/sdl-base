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

    void PrintCharacter(unsigned char c, int x, int y, Color color) const;
    void PrintString(std::string string, int x, int y, Color color) const;

    void RenderCharacter(unsigned char c, int x, int y, Color color) const;

    int CharHeight() const { return m_characterHeight; }
    int CharWidth() const { return m_characterWidth; }
};


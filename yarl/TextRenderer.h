#pragma once

#include "SDLSurface.h"
#include <memory>

class TextRendererImpl;
class TextRenderer
{
    std::unique_ptr<TextRendererImpl> m_Impl;

public:
    TextRenderer(const std::string& fontFile, const SDLRenderer& renderer);
    ~TextRenderer();

    void PrintCharacter(unsigned char c, int x, int y, Color color) const;
    void PrintString(std::string string, int x, int y, Color color) const;

    int CharHeight() const;
    int CharWidth() const;
};


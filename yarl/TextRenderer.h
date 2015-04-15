#pragma once

#include "SDLSurface.h"
#include <memory>
#include "BasicTypes.h"

class TextRendererImpl;
class TextRenderer
{
    std::unique_ptr<TextRendererImpl> m_Impl;

public:
    TextRenderer(const std::string& fontFile, const SDLRenderer& renderer);
    ~TextRenderer();

    void PrintCharacter(unsigned char c, Position p, Color color) const;
    void PrintString(std::string string, Position p, Color color) const;

    const Size& CharSize() const;
};


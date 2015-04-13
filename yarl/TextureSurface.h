#pragma once
#include "SDLSurface.h"

class TextureSurface :
    public SDLSurface
{
public:
    TextureSurface();
    virtual ~TextureSurface();

    virtual void Blit(const SDLSurface& surface, const SDL_Rect& sourceRect, SDL_Rect& destRect);
};


#pragma once
#include <SDL.h>

class SDLRect
{
    SDL_Rect m_actualRect;

public:
    SDLRect(int x, int y, int w, int h)
    {
        m_actualRect.x = x; m_actualRect.y = y;
        m_actualRect.w = w; m_actualRect.h = h;
    }

    SDL_Rect& Rect() { return m_actualRect; }
    const SDL_Rect& Rect() const { return m_actualRect; }
};


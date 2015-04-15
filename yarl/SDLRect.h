#pragma once
#include <SDL.h>
#include "BasicTypes.h"

class SDLRect
{
    SDL_Rect m_actualRect;

public:
    SDLRect(Position p, Size s)
    {
        m_actualRect.x = p.x; m_actualRect.y = p.y;
        m_actualRect.w = s.w; m_actualRect.h = s.h;
    }

    SDLRect(int x, int y, int w, int h)
    {
        m_actualRect.x = x; m_actualRect.y = y;
        m_actualRect.w = w; m_actualRect.h = h;
    }

    Size GetSize() { return Size(m_actualRect.w, m_actualRect.h); }
    Position GetPosition() { return Position(m_actualRect.x, m_actualRect.y); }

    SDL_Rect& Rect() { return m_actualRect; }
    const SDL_Rect& Rect() const { return m_actualRect; }
};


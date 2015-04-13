#pragma once

#include <SDL.h>
#include "SDLSurface.h"

class SDLWrapper
{
    SDL_Window* m_window;
    SDLSurface m_screenSurface;

public:
    SDLWrapper(int width, int height);
    ~SDLWrapper();

    const SDLSurface& ScreenSurface() const { return m_screenSurface; }
    
    void Update() const;
};


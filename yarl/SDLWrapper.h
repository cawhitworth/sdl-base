#pragma once

#include <SDL.h>
#include "SDLSurface.h"
#include "SDLRenderer.h"

class SDLWrapper
{
    SDL_Window* m_window;
    SDLSurface m_screenSurface;
    SDLRenderer m_renderer;
    SDL_Renderer* m_pRenderer;

public:
    SDLWrapper(int width, int height);
    ~SDLWrapper();

    // No copying/moving
    SDLWrapper(const SDLWrapper& wrapper) = delete;
    SDLWrapper& operator=(const SDLWrapper& wrapper) = delete;
    SDLWrapper(SDLWrapper&& wrapper) = delete;
    SDLWrapper& operator=(SDLWrapper&& wrapper) = delete;

    const SDLSurface& ScreenSurface() const { return m_screenSurface; }
    const SDLRenderer& Renderer() const { return m_renderer;  }

    void Update() const;
};


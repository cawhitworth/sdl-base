#include "SDLSurface.h"

SDLSurface::~SDLSurface()
{
    if (m_surface != 0 && !m_suppressCleanup)
    {
        SDL_FreeSurface(m_surface);
    }
    m_surface = 0;
}

void SDLSurface::OptimizeFor(const SDLSurface& screenSurface)
{
    auto optimizedSurface = SDL_ConvertSurface(m_surface, screenSurface.m_surface->format, NULL);
    SDL_FreeSurface(m_surface);
    m_surface = optimizedSurface;
}

void SDLSurface::Blit(const SDLSurface& surface, const SDL_Rect& sourceRect, SDL_Rect& destRect) const
{
    SDL_SetSurfaceBlendMode(m_surface, SDL_BLENDMODE_BLEND);
    SDL_BlitSurface(surface.m_surface, &sourceRect, m_surface, &destRect);
}
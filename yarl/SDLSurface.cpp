#include "SDLSurface.h"
#include "SDLRect.h"
#include "Color.h"

SDLSurface::~SDLSurface()
{
    if (m_surface != 0 && !m_suppressCleanup)
    {
        SDL_FreeSurface(m_surface);
    }
    m_surface = nullptr;
}

void SDLSurface::OptimizeFor(const SDLSurface& screenSurface)
{
    auto optimizedSurface = SDL_ConvertSurface(m_surface, screenSurface.m_surface->format, NULL);
    SDL_FreeSurface(m_surface);
    m_surface = optimizedSurface;
}

void SDLSurface::Blit(const SDLSurface& surface, const SDLRect& sourceRect, SDLRect& destRect) const
{
    SDL_SetSurfaceColorMod(surface.m_surface, 255, 255, 255);
    SDL_BlitSurface(surface.m_surface, &sourceRect.Rect(), m_surface, &destRect.Rect());
}

void SDLSurface::ColorBlit(const SDLSurface& surface, const SDLRect& sourceRect, SDLRect& destRect, Color c) const
{

    SDL_SetSurfaceColorMod(surface.m_surface, c.r, c.g, c.b);
    SDL_BlitSurface(surface.m_surface, &sourceRect.Rect(), m_surface, &destRect.Rect());
}

int SDLSurface::Width()
{
    if (m_surface != nullptr)
        return m_surface->w;
    return 0;
}

int SDLSurface::Height()
{
    if (m_surface != nullptr)
        return m_surface->h;
    return 0;
}
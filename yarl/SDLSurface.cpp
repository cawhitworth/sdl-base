#include "SDLSurface.h"
#include "SDLRect.h"
#include "Color.h"
#include "SDLRenderer.h"
#include <sstream>

SDLSurface::~SDLSurface()
{
    if (m_surface != 0 && !m_suppressCleanup)
    {
        SDL_FreeSurface(m_surface);
    }
    m_surface = nullptr;
}

SDLTexture SDLSurface::CreateAsTexture(const SDLRenderer& renderer) const
{
    auto texture = SDL_CreateTextureFromSurface(renderer.Renderer() , m_surface);
    if (texture == nullptr)
    {
        std::stringstream err;
        err << "Could not create texture: " << SDL_GetError();
        throw std::exception(err.str().c_str());
    }
    return SDLTexture(texture);
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
#pragma once
#include <SDL.h>
#include <iostream>

class SDLSurface
{
protected:
    SDL_Surface* m_surface;
    bool m_suppressCleanup;

public:
    SDLSurface() : m_surface(nullptr), m_suppressCleanup(true) {}

    explicit SDLSurface(SDL_Surface* surface, bool suppressCleanup = false) 
        : m_surface(surface)
        , m_suppressCleanup(suppressCleanup)
    {}

    ~SDLSurface();

    SDLSurface(const SDLSurface& other) = delete;
    SDLSurface(SDLSurface&& other) 
        : m_surface(other.m_surface)
        , m_suppressCleanup(other.m_suppressCleanup)
    {
        other.m_surface = nullptr;
    }

    void OptimizeFor(const SDLSurface& screenSurface);

    void Blit(const SDLSurface& surface, const SDL_Rect& sourceRect, SDL_Rect& destRect) const;
};


#pragma once
#include <SDL.h>
#include <iostream>
#include "SDLTexture.h"

class SDLRenderer;
struct Color;
class SDLRect;

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

    SDLSurface(const SDLSurface&) = delete;
    SDLSurface(SDLSurface&& other) 
        : m_surface(other.m_surface)
        , m_suppressCleanup(other.m_suppressCleanup)
    {
        other.m_surface = nullptr;
    }

    SDLSurface& operator=(const SDLSurface&) = delete;
    SDLSurface& operator=(SDLSurface&& other)
    {
        if (m_surface != nullptr)
        {
            throw std::exception("Cannot assign to a previously assigned surface");
        }

        m_surface = other.m_surface;
        m_suppressCleanup = other.m_suppressCleanup;
        other.m_surface = nullptr;
        return *this;
    }

    SDLTexture CreateAsTexture(const SDLRenderer& renderer) const;

    void OptimizeFor(const SDLSurface& screenSurface);

    void Blit(const SDLSurface& surface, const SDLRect& sourceRect, SDLRect& destRect) const;
    void ColorBlit(const SDLSurface& surface, const SDLRect& sourceRect, SDLRect& destRect, Color c) const;

    int Width();
    int Height();
};


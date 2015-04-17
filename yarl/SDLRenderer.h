#pragma once
#include <SDL.h>
#include "TextRenderer.h"
#include "Color.h"
#include "SDLException.h"
struct SDL_Renderer;

class SDLRenderer
{
    SDL_Renderer* m_renderer;
    Color m_White = Color(0xff, 0xff, 0xff);

public:
    SDLRenderer() : m_renderer(nullptr) {}
    SDLRenderer(SDL_Renderer* renderer) : m_renderer(renderer)
    {
        if (SDL_RenderClear(renderer))
        {
            throw SDLException(SDL_GetError());
        }
    }

    SDLRenderer(const SDLRenderer&) = delete;
    SDLRenderer& operator=(const SDLRenderer&) = delete;

    SDLRenderer(SDLRenderer&& other) : m_renderer(other.m_renderer)
    {
        other.m_renderer = nullptr;
    }

    SDLRenderer& operator=(SDLRenderer&& other)
    {
        m_renderer = other.m_renderer;
        other.m_renderer = nullptr;
        return *this;
    }


    ~SDLRenderer()
    {
        if (m_renderer != nullptr)
        {
            Destroy();
        }
        m_renderer = nullptr;
    }

    SDL_Renderer* Renderer() const { return m_renderer; }

    void RenderCopy(const SDLTexture& texture, SDLRect& srcRect, SDLRect& destRect) const;
    void RenderCopyColor(const SDLTexture& texture, SDLRect& srcRect, SDLRect& destRect, const Color& color) const;
    void Present() const;
    void Clear() const;
    void Destroy();
};


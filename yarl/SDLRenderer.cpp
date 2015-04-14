#include "SDLRenderer.h"
#include "SDLRect.h"
#include <sstream>


void SDLRenderer::Destroy()
{
    SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;
}

void SDLRenderer::RenderCopy(const SDLTexture& texture, SDLRect& srcRect, SDLRect& destRect) const
{
    if (SDL_RenderCopy(m_renderer, texture.Texture(), &srcRect.Rect(), &destRect.Rect()) < 0)
    {
        std::stringstream err;
        err << "Failed render copy: " << SDL_GetError();
        throw std::exception(err.str().c_str());
    }
}

void SDLRenderer::Present() const
{
    SDL_RenderPresent(m_renderer);
}

void SDLRenderer::Clear() const
{
    if (SDL_RenderClear(m_renderer) < 0)
    {
        std::stringstream err;
        err << "Failed to clear renderer: " << SDL_GetError();
        throw std::exception(err.str().c_str());
    }
}
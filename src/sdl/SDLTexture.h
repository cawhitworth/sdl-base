#pragma once
class SDLSurface;

class SDLTexture
{
    SDL_Texture *m_texture;

public:
    SDLTexture() : m_texture(nullptr) {}

    SDLTexture(SDL_Texture* texture) : m_texture(texture) {}

    SDLTexture(const SDLTexture&) = delete;
    SDLTexture(SDLTexture&& other) : m_texture(other.m_texture)
    {
        other.m_texture = nullptr;
    }

    SDLTexture& operator=(const SDLTexture&) = delete;
    SDLTexture& operator=(SDLTexture&& other)
    {
        m_texture = other.m_texture;
        other.m_texture = nullptr;

        return *this;
    }

    ~SDLTexture()
    {
        if (m_texture != nullptr)
        {
            SDL_DestroyTexture(m_texture);
        }
    }

    SDL_Texture* Texture() const { return m_texture; }
};


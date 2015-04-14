
#include <sstream>
#include <exception>

#include "SDL_render.h"
#include "SDLWrapper.h"

SDLWrapper::SDLWrapper(int w, int h)
{
    std::stringstream err;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        err << "SDL could not initialise: " << SDL_GetError();
        throw std::exception(err.str().c_str());
    }

    m_window = SDL_CreateWindow("Yarl", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);

    if (m_window == nullptr)
    {
        err << "Window could not be created" << SDL_GetError();
        throw std::exception(err.str().c_str());
    }

    auto renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (SDL_RenderClear(renderer) < 0)
    {
        err << SDL_GetError();
        throw std::exception(err.str().c_str());
    }

    m_renderer = SDLRenderer(renderer);
    m_renderer.Clear();
}

SDLWrapper::~SDLWrapper()
{
    m_renderer.Destroy();
    SDL_Quit();
}

void SDLWrapper::Update() const
{
    SDL_UpdateWindowSurface(m_window);
}

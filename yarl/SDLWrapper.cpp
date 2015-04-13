
#include <sstream>
#include <exception>

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

    if (m_window == NULL)
    {
        err << "Window could not be created" << SDL_GetError();
        throw std::exception(err.str().c_str());
    }

    m_screenSurface = SDLSurface(SDL_GetWindowSurface(m_window), true);
}

SDLWrapper::~SDLWrapper()
{
    SDL_Quit();
}

void SDLWrapper::Update() const
{
    SDL_UpdateWindowSurface(m_window);
}

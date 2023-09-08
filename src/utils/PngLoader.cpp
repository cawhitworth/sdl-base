#include <sstream>
#include <SDL_image.h>

#include "PngLoader.h"

PNGLoader::PNGLoader()
{
    std::stringstream err;
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        err << "Cannot init PNG loader: " << IMG_GetError();
        throw SDLException(err.str().c_str());
    }
}

PNGLoader::~PNGLoader()
{
}

SDLSurface PNGLoader::Load(std::string path)
{
    std::stringstream err;

    auto loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr)
    {
        err << "Cannot load PNG '" << path << "' - " << IMG_GetError();
        throw SDLException(err.str().c_str());
    }

    auto surface = SDLSurface(loadedSurface);
    return surface;
}

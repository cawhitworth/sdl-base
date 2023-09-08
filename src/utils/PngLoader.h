#pragma once

#include <string>
#include "SDLSurface.h"

class PNGLoader
{
public:
    PNGLoader();
    ~PNGLoader();

    SDLSurface Load(std::string);
};


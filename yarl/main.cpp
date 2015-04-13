#include <iostream>

#include "SDLWrapper.h"
#include "PNGLoader.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


int main(int argc, char* argv [])
{
    try {
        SDLWrapper wrapper(SCREEN_WIDTH, SCREEN_HEIGHT);
        PNGLoader pngLoader;

        auto &screenSurface = wrapper.ScreenSurface();

        auto surface = pngLoader.Load("images/CLA.png");
        //surface.OptimizeFor(screenSurface);

        SDL_Rect src;
        src.x = src.y = 0;
        src.h = 100; src.w = 100;
        wrapper.ScreenSurface().Blit(surface, src, src);

        wrapper.Update();

        SDL_Delay(2000);
    }
    catch (std::exception e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}

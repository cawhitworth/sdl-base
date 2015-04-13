#include <iostream>

#include "SDLWrapper.h"
#include "PNGLoader.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#include "TextRenderer.h"
#include "Color.h"

int main(int argc, char* argv [])
{
    try {
        SDLWrapper wrapper(SCREEN_WIDTH, SCREEN_HEIGHT);
        PNGLoader pngLoader;

        auto &screenSurface = wrapper.ScreenSurface();

        auto textRenderer = TextRenderer("images/CLA.png");

        textRenderer.RenderCharacter('r', 32, 32, screenSurface, Color(255,0,0));
        textRenderer.RenderCharacter('g', 48, 32, screenSurface, Color(0,255,0));
        textRenderer.RenderCharacter('b', 64, 32, screenSurface, Color(0,0,255));

        wrapper.Update();

        auto quit = false;
        while (!quit)
        {
            SDL_Event e;
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }
        }
    }
    catch (std::exception e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}

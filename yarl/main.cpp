#include <iostream>
#include <chrono>

#include "SDLWrapper.h"
#include "PNGLoader.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#include "TextRenderer.h"
#include "Color.h"
#include <sstream>

int main(int argc, char* argv [])
{
    try {
        SDLWrapper wrapper(SCREEN_WIDTH, SCREEN_HEIGHT);
        PNGLoader pngLoader;

        auto &renderer = wrapper.Renderer();
        auto &screenSurface = wrapper.ScreenSurface();


        renderer.Clear();

        auto textRenderer = TextRenderer("images/CLA.png", renderer);

        textRenderer.PrintString("Yet Another Rogue-like", 5, 2, Color(200, 200, 200));

        textRenderer.RenderCharacter('r', 32, 32, Color(255,0,0));
        textRenderer.RenderCharacter('g', 48, 32, Color(0,255,0));
        textRenderer.RenderCharacter('b', 64, 32, Color(0,0,255));
        renderer.Present();

        auto quit = false;
        auto frame = 0;
        auto start = std::chrono::high_resolution_clock::now();
        std::chrono::seconds one_second(1);
        auto fps = 0;
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

            renderer.Clear();
            std::stringstream fpsText;
            fpsText << fps << "FPS";

            textRenderer.PrintString(fpsText.str(), 0, 0, Color(200, 255, 200));
            ;
            textRenderer.PrintString("Yet Another Rogue-like", 5, 2, Color(200, 200, 200));

            renderer.Present();

            frame++;
            if (std::chrono::high_resolution_clock::now() - start > one_second)
            {
                fps = frame;
                frame = 0;
                start = std::chrono::high_resolution_clock::now();
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

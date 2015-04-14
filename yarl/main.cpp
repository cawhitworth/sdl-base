#include <iostream>
#include <chrono>

#include "SDLWrapper.h"
#include "PNGLoader.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#include "TextRenderer.h"
#include "Color.h"
#include <sstream>
#include "FPS.h"
#include "Map.h"
#include "MapRenderer.h"

int main(int argc, char* argv [])
{
    try {
        Map m(200, 200);
        SDLWrapper wrapper(SCREEN_WIDTH, SCREEN_HEIGHT);

        auto &renderer = wrapper.Renderer();
        auto textRenderer = TextRenderer("images/CLA.png", renderer);
        MapRenderer mapRenderer(textRenderer, m);

        FPS fps;

        auto quit = false;
        while (!quit)
        {
            fps.Tick();

            SDL_Event e;
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }

            renderer.Clear();

            mapRenderer.Render(0, 0, SCREEN_WIDTH / textRenderer.CharWidth(), SCREEN_HEIGHT / textRenderer.CharHeight());

            std::stringstream fpsText;
            fpsText << fps.Fps() << "FPS";

            textRenderer.PrintString(fpsText.str(), 0, 0, Color(200, 255, 200));
            textRenderer.PrintString("Yet Another Rogue-like", 5, 2, Color(200, 200, 200));

            renderer.Present();

        }
    }
    catch (std::exception e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}

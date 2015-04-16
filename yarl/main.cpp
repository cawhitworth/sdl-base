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

#include "Imp.h"
#include "ImpRenderer.h"

using namespace std::chrono;

#pragma warning(disable: 4100)
int main(int argc, char* argv[])
{

    try {
        Position origin(0, 0);
        Map m(Size(200, 200));
        std::vector<Imp> imps;

        SDLWrapper wrapper(SCREEN_WIDTH, SCREEN_HEIGHT);

        auto &renderer = wrapper.Renderer();
        auto textRenderer = TextRenderer("images/Teeto_K_18x18.PNG", renderer);
        auto charSize = textRenderer.CharSize();
        MapRenderer mapRenderer(textRenderer, m);
        ImpRenderer impRenderer(textRenderer);

        Size viewPort(SCREEN_WIDTH / charSize.w, SCREEN_HEIGHT / charSize.h);

        FPS fps;

        AddDungeonHeart(m, Position(8, 8));

        for (int i = 0; i < 5; i++)
        {
            imps.push_back(Imp(m, Position(5, 5)));
        }

        auto last = high_resolution_clock::now();

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

            mapRenderer.Render(origin, viewPort);

            auto elapsed = duration_cast<milliseconds>(high_resolution_clock::now() - last);
            last = high_resolution_clock::now();

            for (auto& i : imps)
            {
                i.Update(elapsed);
                impRenderer.Render(i);
            }

            std::stringstream fpsText;
            fpsText << fps.Fps() << "FPS";

            textRenderer.PrintString(fpsText.str(), origin, Color(200, 255, 200));
            textRenderer.PrintString("Yet Another Rogue-like", Position(5,2), Color(200, 200, 200));

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

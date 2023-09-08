#include <sstream>
#include <chrono>

#define SCREEN_WIDTH (18*80)
#define SCREEN_HEIGHT (18*48)

#include "SDLWrapper.h"
#include "SDLException.h"
#include "FPS.h"
#include "PngLoader.h"

#include "Yarl.h"
#pragma warning(disable: 4100)
int main(int argc, char* argv[])
{
    try {
        SDLWrapper wrapper(SCREEN_WIDTH, SCREEN_HEIGHT);
        TextRenderer textRenderer("images/Teeto_K_18x18.PNG", wrapper.Renderer());
        Yarl yarl(textRenderer, Size(SCREEN_WIDTH, SCREEN_HEIGHT));
        auto quit = false;
        
        FPS fps;

        while(!quit) {
            fps.Tick();

            SDL_Event e;
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }

                if (!yarl.Handle(e))
                {
                    quit = true;
                }
            }

            wrapper.Renderer().Clear();

            yarl.Main();

            std::stringstream fpsText;
            fpsText << fps.Fps() << "FPS";

            textRenderer.PrintString(fpsText.str(), Position(70, 46), Color(200, 255, 200));
            textRenderer.PrintString("Yet Another Rogue-like", Position(5,46), Color(200, 200, 200));

            wrapper.Renderer().Present();
            
        }

    }
    catch (SDLException e)
    {
        std::cerr << e.Message() << std::endl;
        return -1;
    }
    return 0;
}

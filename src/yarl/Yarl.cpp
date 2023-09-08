#include <algorithm>
#include <sstream>

#include "SDLWrapper.h"

#include "utils/TextRenderer.h"
#include "utils/FPS.h"
#include "PngLoader.h"

#include "Yarl.h"

#include "Map.h"
#include "MapRenderer.h"

#include "Imp.h"
#include "ImpRenderer.h"

#include "Color.h"

using namespace std::chrono;

class YarlImpl {
    std::unique_ptr<SDLWrapper> m_sdlWrapper;
    Size m_screenSize;

public:
    YarlImpl(std::unique_ptr<SDLWrapper> sdlWrapper, Size screenSize) 
        : m_sdlWrapper(std::move(sdlWrapper))
        , m_screenSize(screenSize)
    {}
    
    void YarlMain()
    {
        Position origin(0, 0);
        Map m(Size(200, 200));
        std::vector<Imp> imps;

        auto &renderer = m_sdlWrapper->Renderer();
        auto textRenderer = TextRenderer("images/Teeto_K_18x18.PNG", renderer);
        auto charSize = textRenderer.CharSize();
        MapRenderer mapRenderer(textRenderer, m);
        ImpRenderer impRenderer(textRenderer);

        Size viewPort(m_screenSize.w / charSize.w, m_screenSize.h / charSize.h);

        FPS fps;

        AddDungeonHeart(m, Position(8, 8));

        for (int i = 0; i < 5; i++)
        {
            imps.push_back(Imp(m, Position(5, 5)));
        }

        auto last = high_resolution_clock::now();

        auto mapOrigin = origin;

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

                if (e.type == SDL_KEYDOWN)
                {
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_UP:
                        mapOrigin.y = std::max(CoordType(0), mapOrigin.y - 1); break;
                    case SDLK_DOWN:
                        mapOrigin.y = std::min(CoordType(200), mapOrigin.y + 1); break; // WRONG!
                    case SDLK_LEFT:
                        mapOrigin.x = std::max(CoordType(0), mapOrigin.x - 1); break;
                    case SDLK_RIGHT:
                        mapOrigin.x = std::min(CoordType(200), mapOrigin.x + 1); break; // WRONG!
                    }
                    if (e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        quit = true;
                    }

                }
            }

            renderer.Clear();

            mapRenderer.Render(mapOrigin, viewPort);

            auto elapsed = duration_cast<milliseconds>(high_resolution_clock::now() - last);
            last = high_resolution_clock::now();

            impRenderer.SetOrigin(mapOrigin);
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
};

Yarl::Yarl(std::unique_ptr<SDLWrapper> sdlWrapper, Size screenSize)
    : m_impl(std::make_unique<YarlImpl>(std::move(sdlWrapper), screenSize))
{
}

Yarl::~Yarl()
{
}

void Yarl::Main()
{
    m_impl->YarlMain();
}
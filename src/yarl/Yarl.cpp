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
    std::unique_ptr<SDLWrapper> _sdlWrapper;
    Size _screenSize;

    Position _origin;
    Map _map;
    std::vector<Imp> _imps;
    TextRenderer _textRenderer;
    FPS _fps;
    MapRenderer _mapRenderer;
    ImpRenderer _impRenderer;

public:
    YarlImpl(std::unique_ptr<SDLWrapper> sdlWrapper, Size screenSize) :
        _sdlWrapper(std::move(sdlWrapper)),
        _screenSize(screenSize),
        _origin(0,0),
        _map(Size(200,200)),
        _imps(),
        _fps(),
        _textRenderer("images/Teeto_K_18x18.PNG", _sdlWrapper->Renderer()),
        _mapRenderer(_textRenderer, _map),
        _impRenderer(_textRenderer)
    {
        AddDungeonHeart(_map, Position(8, 8));

        for (int i = 0; i < 5; i++)
        {
            _imps.push_back(Imp(_map, Position(5, 5)));
        }
    }
    
    void YarlMain()
    {
        auto charSize = _textRenderer.CharSize();
        Size viewPort(_screenSize.w / charSize.w, _screenSize.h / charSize.h);

        auto last = high_resolution_clock::now();

        auto mapOrigin = _origin;

        auto quit = false;
        while (!quit)
        {
            _fps.Tick();

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

            _sdlWrapper->Renderer().Clear();

            _mapRenderer.Render(mapOrigin, viewPort);

            auto elapsed = duration_cast<milliseconds>(high_resolution_clock::now() - last);
            last = high_resolution_clock::now();

            _impRenderer.SetOrigin(mapOrigin);
            for (auto& i : _imps)
            {
                i.Update(elapsed);
                _impRenderer.Render(i);
            }

            std::stringstream fpsText;
            fpsText << _fps.Fps() << "FPS";

            _textRenderer.PrintString(fpsText.str(), _origin, Color(200, 255, 200));
            _textRenderer.PrintString("Yet Another Rogue-like", Position(5,2), Color(200, 200, 200));

            _sdlWrapper->Renderer().Present();

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
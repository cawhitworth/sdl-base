#include <algorithm>

#include "SDLWrapper.h"

#include "utils/TextRenderer.h"

#include "Yarl.h"

#include "Map.h"
#include "MapRenderer.h"

#include "Imp.h"
#include "ImpRenderer.h"

#include "Color.h"

using namespace std::chrono;

class YarlImpl {
    Size _screenSize;
    Size _charSize;
    Position _origin;
    Position _mapOrigin;
    Map _map;
    std::vector<Imp> _imps;
    MapRenderer _mapRenderer;
    ImpRenderer _impRenderer;
    steady_clock::time_point _last;

public:
    YarlImpl(const TextRenderer& textRenderer, Size screenSize) :
        _screenSize(screenSize),
        _charSize(textRenderer.CharSize()),
        _origin(0,0),
        _mapOrigin(_origin),
        _map(Size(200,200)),
        _imps(),
        _mapRenderer(textRenderer, _map),
        _impRenderer(textRenderer),
        _last(high_resolution_clock::now())
    {
        AddDungeonHeart(_map, Position(8, 8));

        for (int i = 0; i < 5; i++)
        {
            _imps.push_back(Imp(_map, Position(5, 5)));
        }
    }
    
    bool Handle(const SDL_Event& e)
    {
        auto quit = false;
        if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                quit = true;
                break;
            case SDLK_UP:
                _mapOrigin.y = std::max(CoordType(0), _mapOrigin.y - 1); break;
            case SDLK_DOWN:
                _mapOrigin.y = std::min(CoordType(200), _mapOrigin.y + 1); break; // WRONG!
            case SDLK_LEFT:
                _mapOrigin.x = std::max(CoordType(0), _mapOrigin.x - 1); break;
            case SDLK_RIGHT:
                _mapOrigin.x = std::min(CoordType(200), _mapOrigin.x + 1); break; // WRONG!
            }
            if (e.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
        }

        return !quit;
    }

    void YarlMain()
    {
        Size viewPort(_screenSize.w / _charSize.w, _screenSize.h / _charSize.h);


        _mapRenderer.Render(_mapOrigin, viewPort);

        auto elapsed = duration_cast<milliseconds>(high_resolution_clock::now() - _last);
        _last = high_resolution_clock::now();

        _impRenderer.SetOrigin(_mapOrigin);
        for (auto& i : _imps)
        {
            i.Update(elapsed);
            _impRenderer.Render(i);
        }

    }
};

Yarl::Yarl(const TextRenderer& textRenderer, Size screenSize)
    : m_impl(std::make_unique<YarlImpl>(textRenderer, screenSize))
{
}

Yarl::~Yarl()
{
}

void Yarl::Main()
{
    m_impl->YarlMain();
}

bool Yarl::Handle(const SDL_Event& e)
{
    return m_impl->Handle(e);
}
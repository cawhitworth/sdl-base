#include "MapRenderer.h"
#include "Map.h"
#include <random>
#include "Color.h"
#include "TextRenderer.h"

MapRenderer::MapRenderer(const TextRenderer& textRenderer, const Map& map)
: m_textRenderer(textRenderer)
, m_map(map)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 4);

    for (CoordType i = 0; i < m_map.GetSize().w * m_map.GetSize().h; i++)
    {
        m_varianceMap.push_back(static_cast<unsigned char>(distribution(generator)));
    }
}

MapRenderer::~MapRenderer()
{
}

void MapRenderer::Render(Position p, Size s)
{
    Position rp;

    for (rp.x = p.x; rp.x < p.x + s.w; rp.x++)
    {
        for (rp.y = p.y; rp.y < p.y + s.h; rp.y++)
        {
            Color color(255,255,255);
            unsigned char ch = '?';
            
            switch (m_map[rp].type)
            {
                case Rock: 
                    ch = '*';
                    color = Color(150, 100, 0);
                    break;
                case StoneFloor:
                    ch = 249;
                    color = Color(192, 192, 192);
                    break;
                case DirtFloor:
                    ch = 249;
                    color = Color(150, 100, 0);
                    break;
                case Wall: 
                    ch = '#';
                    color = Color(150, 100, 0);
                    break;
                case Lava:
                    ch = '~';
                    color = Color(255, 100, 0);
                    break;
                case Heart:
                    ch = 3;
                    color = Color(255, 0, 0);
                    break;
                default: break;
            }

            auto offset = OffsetOf(rp, m_map.GetSize());
            auto vmap = m_varianceMap[offset];

            color.r = (color.r * vmap) / 4;
            color.g = (color.g * vmap) / 4;
            color.b = (color.b * vmap) / 4;

            m_textRenderer.PrintCharacter(ch, rp, color);
        }
    }
}
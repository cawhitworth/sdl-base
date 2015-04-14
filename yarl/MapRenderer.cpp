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

    for (int i = 0; i < m_map.Width() * m_map.Height(); i++)
    {
        m_varianceMap.push_back(static_cast<unsigned char>(distribution(generator)));
    }
}

MapRenderer::~MapRenderer()
{
}

void MapRenderer::Render(int x, int y, int w, int h)
{
    for (int rx = x; rx < x + w; rx++)
    {
        for (int ry = y; ry < y + h; ry++)
        {
            Color color(255,255,255);
            unsigned char ch = '?';
            
            switch (m_map[rx + ry * m_map.Width()].type)
            {
                case Rock: 
                    ch = '*';
                    color = Color(150, 100, 0);
                    break;
                case Floor:
                    ch = '.';
                    color = Color(150, 100, 0);
                    break;
                case Wall: 
                    ch = '#';
                    color = Color(150, 100, 0);
                    break;
                default: break;
            }

            auto vmap = m_varianceMap[rx + ry * m_map.Width()];
            color.r = (color.r * vmap) / 4;
            color.g = (color.g * vmap) / 4;
            color.b = (color.b * vmap) / 4;

            m_textRenderer.PrintCharacter(ch, rx, ry, color);
        }
    }
}
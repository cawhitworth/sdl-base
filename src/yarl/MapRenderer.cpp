#include <random>
#include <algorithm>
#include <map>

#include "MapRenderer.h"
#include "Map.h"
#include "Color.h"
#include "TextRenderer.h"

struct CellRenderInfo
{
    CellRenderInfo() 
        : minVariance(4), maxVariance(4), c('?'), col(Color(255, 255, 255)) {}
    CellRenderInfo(unsigned char c, Color col) 
        : minVariance(1), maxVariance(4), c(c), col(col) {}
    CellRenderInfo(unsigned char c, Color col, unsigned char minVariance, unsigned char maxVariance) 
        : minVariance(minVariance), maxVariance(maxVariance), c(c), col(col) {}

    unsigned char minVariance;
    unsigned char maxVariance;
    unsigned char c;
    Color col;
};

class MapRendererImpl
{

    const TextRenderer& m_textRenderer;
    const Map& m_map;
    std::vector<unsigned char> m_varianceMap;
    std::map<CellType, CellRenderInfo> m_appearance;

public:
    explicit MapRendererImpl(const TextRenderer& textRenderer, const Map& map)
        : m_textRenderer(textRenderer)
        , m_map(map)
    {
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(1, 4);

        for (CoordType i = 0; i < m_map.GetSize().w * m_map.GetSize().h; i++)
        {
            m_varianceMap.push_back(static_cast<unsigned char>(distribution(generator)));
        }

        m_appearance[Rock] = CellRenderInfo('*', Color(150, 80, 0));
        m_appearance[StoneFloor] = CellRenderInfo(249, Color(192, 192, 192));
        m_appearance[DirtFloor] = CellRenderInfo(249, Color(100, 75, 0));
        m_appearance[Wall] = CellRenderInfo('#', Color(192, 192, 192));
        m_appearance[Lava] = CellRenderInfo('~', Color(255, 175, 0), 3, 4);
        m_appearance[Heart] = CellRenderInfo(3, Color(255, 0, 0), 4, 4);

    }

    ~MapRendererImpl()
    {}

    MapRendererImpl& operator=(const MapRendererImpl&) = delete;

    void Render(Position p, Size s)
    {

        Position mapPos;
        Position screenPos;


        for (mapPos.x = p.x, screenPos.x = 0; mapPos.x < p.x + s.w; mapPos.x++, screenPos.x++)
        {
            for (mapPos.y = p.y, screenPos.y = 0; mapPos.y < p.y + s.h; mapPos.y++, screenPos.y++)
            {
                CellRenderInfo ri;

                auto appearance = m_appearance.find(m_map[mapPos].type);
                if (appearance != m_appearance.end())
                {
                    ri = appearance->second;
                }

                Color color(ri.col);

                auto offset = OffsetOf(mapPos, m_map.GetSize());
                auto vmap = m_varianceMap[offset];
                vmap = std::max(vmap, ri.minVariance);
                vmap = std::min(vmap, ri.maxVariance);

                color.r = (color.r * vmap) / 4;
                color.g = (color.g * vmap) / 4;
                color.b = (color.b * vmap) / 4;

                m_textRenderer.PrintCharacter(ri.c, screenPos, color);
            }
        }
    }
};


MapRenderer::MapRenderer(const TextRenderer& textRenderer, const Map& map)
{
    m_Impl = std::make_unique<MapRendererImpl>(textRenderer, map);
}

MapRenderer::~MapRenderer()
{
}

void MapRenderer::Render(Position p, Size s)
{
    m_Impl->Render(p, s);
}
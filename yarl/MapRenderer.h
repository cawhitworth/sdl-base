#pragma once
#include <vector>

class Map;
class TextRenderer;

class MapRenderer
{
    const TextRenderer& m_textRenderer;
    const Map& m_map;
    std::vector<unsigned char> m_varianceMap;
public:
    explicit MapRenderer(const TextRenderer&, const Map& map);
    ~MapRenderer();

    MapRenderer& operator=(const MapRenderer&) = delete;

    void Render(int x, int y, int w, int h);

};


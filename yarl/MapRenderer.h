#pragma once
#include <vector>
#include "BasicTypes.h"

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

    void Render(Position p, Size s);

};


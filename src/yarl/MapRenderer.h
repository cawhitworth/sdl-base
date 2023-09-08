#pragma once
#include "BasicTypes.h"
#include <memory>

class Map;
class TextRenderer;
class MapRendererImpl;

class MapRenderer
{
    std::unique_ptr<MapRendererImpl> m_Impl;
public:
    explicit MapRenderer(const TextRenderer&, const Map& map);
    ~MapRenderer();

    MapRenderer& operator=(const MapRenderer&) = delete;

    void Render(Position p, Size s);

};


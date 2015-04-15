#pragma once

#include <vector>
#include "BasicTypes.h"

typedef enum
{
    Rock = 0,
    Floor,
    Wall
} CellType;

struct MapCell
{
    CellType type;
};

class Map
{
    std::vector<MapCell> m_Cells;
    Size m_size;
public:
    Map(Size s);
    ~Map();

    // Oh no you don't
    Map(const Map&) = delete;
    Map& operator=(const Map&) = delete;

    const MapCell& operator[](Position p) const { return m_Cells[p.x + p.y*m_size.w]; }

    const Size& GetSize() const { return m_size; }
};

void AddDungeonHeart(Map& map, Position position);
#pragma once

#include <vector>
#include "BasicTypes.h"

typedef enum
{
    Rock = 0,
    Dirt,
    StoneFloor,
    DirtFloor,
    Wall,
    Lava,
    Heart
} CellType;

struct MapCell
{
    MapCell() : type(Rock) {}
    explicit MapCell(CellType type) : type(type) {}

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

    MapCell& operator[](Position p) { return m_Cells[OffsetOf(p, m_size)]; }
    const MapCell& operator[](Position p) const { return m_Cells[OffsetOf(p, m_size)]; }

    const Size& GetSize() const { return m_size; }

    bool CanMoveTo(Position position);
};

void AddDungeonHeart(Map& map, Position position);
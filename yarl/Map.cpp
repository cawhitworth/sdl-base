#include "Map.h"

Map::Map(Size s)
: m_size(s)
{
    MapCell c;
    c.type = Rock;

    m_Cells.resize(s.w * s.h, c);
}

Map::~Map()
{
}
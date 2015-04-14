#include "Map.h"

Map::Map(int height, int width)
: m_height(height)
, m_width(width)
{
    MapCell c;
    c.type = Rock;

    m_Cells.resize(height * width, c);
}

Map::~Map()
{
}
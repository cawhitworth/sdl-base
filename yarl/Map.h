#pragma once
#include <vector>

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
    int m_height;
    int m_width;

public:
    Map(int height, int width);
    ~Map();

    // Oh no you don't
    Map(const Map&) = delete;
    Map& operator=(const Map&) = delete;

    const MapCell& operator[](int offset) const { return m_Cells[offset]; }

    int Width() const { return m_width; }
    int Height() const { return m_height; }
};


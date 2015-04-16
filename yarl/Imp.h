#pragma once
#include "Entity.h"
#include "BasicTypes.h"

class Map;

class Imp :
    public Entity
{
    Position m_location;
    Map& m_map;

    std::chrono::milliseconds m_elapsed;
    std::chrono::milliseconds m_speed;


public:
    explicit Imp(Map& map, Position location) : m_location(location), m_map(map)
    {
        m_elapsed = std::chrono::milliseconds(0);
        m_speed = std::chrono::milliseconds(250);
    }

    virtual ~Imp() {}

    Imp(const Imp&) = delete;
    Imp& operator=(const Imp&) = delete;
    
    Imp(Imp&& imp) : m_location(imp.m_location), m_map(imp.m_map)
    {
        m_elapsed = std::chrono::milliseconds(0);
        m_speed = std::chrono::milliseconds(250);
    }

    void Update(std::chrono::milliseconds updateDuration);
    Position Location() const { return m_location; };
};


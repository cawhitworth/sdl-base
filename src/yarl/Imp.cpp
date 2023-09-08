#include "Imp.h"
#include <random>
#include "Map.h"

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(1, 4);

void Imp::Update(std::chrono::milliseconds updateDuration)
{
    m_elapsed += updateDuration;
    if (m_elapsed > m_speed)
    {
        m_elapsed -= m_speed;

        Position newLocation = m_location;
        switch (distribution(generator))
        {
        case 1: newLocation.x += 1; break;
        case 2: newLocation.y += 1; break;
        case 3: newLocation.x -= 1; break;
        case 4: newLocation.y -= 1; break;
        }

        if (m_map.CanMoveTo(newLocation))
        {
            m_location = newLocation;
        }
    }
}
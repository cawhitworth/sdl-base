#include <chrono>

class Entity
{
public:
    virtual ~Entity()
    {
    }

    virtual void Update(std::chrono::milliseconds duration) = 0;
};
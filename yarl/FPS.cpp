#include "FPS.h"
#include <chrono>

using namespace std::chrono;

class FPSImpl
{
    int m_frame;
    time_point<high_resolution_clock> m_start;
    seconds one_second = seconds(1);

public:

    void Reset()
    {
        m_frame = 0;
        m_start = high_resolution_clock::now();
        m_fps = 0;
    }

    void Tick()
    {
        m_frame++;
        if (high_resolution_clock::now() - m_start > one_second)
        {
            m_fps = m_frame;
            m_frame = 0;
            m_start = high_resolution_clock::now();
        }
    }

    int m_fps;
};

FPS::FPS() : m_impl(std::make_unique<FPSImpl>()) { }

FPS::~FPS() { m_impl.release(); }

void FPS::Reset()
{
    m_impl->Reset();
}

void FPS::Tick()
{
    m_impl->Tick();
}

int FPS::Fps()
{
    return m_impl->m_fps;
}

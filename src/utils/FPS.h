#pragma once

#include <memory>

class FPSImpl;
class FPS
{
    std::unique_ptr<FPSImpl> m_impl;
public:
    FPS();
    ~FPS();

    void Reset();
    void Tick();
    int Fps();
};


#pragma once

#include <memory>

class YarlImpl;
class Yarl
{
    std::unique_ptr<YarlImpl> m_impl;

public:
    Yarl(std::unique_ptr<SDLWrapper> sdlWrapper, Size screenSize);
    ~Yarl();

    void Main();
};

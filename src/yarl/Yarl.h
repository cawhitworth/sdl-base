#pragma once

#include <memory>

class YarlImpl;
class Yarl
{
    std::unique_ptr<YarlImpl> m_impl;

public:
    Yarl(const TextRenderer& textRenderer, Size screenSize);
    ~Yarl();

    void Main();
    bool Handle(const SDL_Event& e);
};

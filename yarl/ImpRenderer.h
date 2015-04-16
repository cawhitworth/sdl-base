#pragma once
#include "BasicTypes.h"
class Imp;
class TextRenderer;

class ImpRenderer
{
    Position m_mapOrigin;
    const TextRenderer& m_renderer;
public:
    explicit ImpRenderer(const TextRenderer& textRenderer)
        : m_renderer(textRenderer) {}
    ~ImpRenderer() {}

    ImpRenderer& operator=(const ImpRenderer&) = delete;

    void Render(const Imp& imp);
    void SetOrigin(Position mapOrigin) { m_mapOrigin = mapOrigin; }
};


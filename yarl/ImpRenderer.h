#pragma once
class Imp;
class TextRenderer;

class ImpRenderer
{
    const TextRenderer& m_renderer;
public:
    explicit ImpRenderer(const TextRenderer& textRenderer)
        : m_renderer(textRenderer) {}
    ~ImpRenderer() {}

    ImpRenderer& operator=(const ImpRenderer&) = delete;

    void Render(const Imp& imp);
};


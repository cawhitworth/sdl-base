#include <memory>
#include "TextRenderer.h"
#include "PngLoader.h"
#include "SDLRect.h"
#include "Color.h"
#include "SDLRenderer.h"

class TextRenderer::TextRendererImpl
{
    SDLTexture m_texture;
    const SDLRenderer& m_renderer;

public:
    Size m_characterSize;
    
    TextRendererImpl(const std::string& fontFile, const SDLRenderer& renderer) : m_renderer(renderer)
    {
        PNGLoader loader;
        auto surface = SDLSurface(loader.Load(fontFile));

        m_texture = surface.CreateAsTexture(renderer);

        // We assume it's a 16x16 grid of characters

        m_characterSize = Size(surface.GetSize().w / 16, surface.GetSize().h / 16);

    }
    ~TextRendererImpl() {}

    void PrintCharacter(unsigned char c, Position p, Color color) const
    {
        Position renderPos(p.x * m_characterSize.w, p.y * m_characterSize.h);
        RenderCharacter(c, renderPos, color);
    }

    void PrintString(std::string string, Position p, Color color) const
    {
        for (auto&& c : string)
        {
            PrintCharacter(c, p, color);
            p.x++;
        }
    }

    void RenderCharacter(unsigned char c, Position p, Color color) const
    {
        auto cx = c % 16;
        auto cy = c / 16;
        auto cp = Position(cx * m_characterSize.w, cy * m_characterSize.h);

        auto srcRect = SDLRect(cp, m_characterSize);
        auto destRect = SDLRect(p, m_characterSize);

        m_renderer.RenderCopyColor(m_texture, srcRect, destRect, color);
    }
};


TextRenderer::TextRenderer(const std::string& fontFile, const SDLRenderer& renderer)
: m_Impl(std::make_unique<TextRenderer::TextRendererImpl>(fontFile, renderer)) { }

TextRenderer::~TextRenderer() { m_Impl.release(); }

TextRenderer::TextRenderer(TextRenderer&& r)
    : m_Impl(std::move(r.m_Impl))
{}

void TextRenderer::PrintCharacter(unsigned char c, Position p, Color color) const
{
    m_Impl->PrintCharacter(c, p, color);
}

void TextRenderer::PrintString(std::string string, Position p, Color color) const
{
    m_Impl->PrintString(string, p, color);
}

const Size& TextRenderer::CharSize() const
{
    return m_Impl->m_characterSize;
}

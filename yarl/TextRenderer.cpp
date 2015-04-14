#include "TextRenderer.h"
#include "PngLoader.h"
#include "SDLRect.h"
#include "Color.h"
#include "SDLRenderer.h"

class TextRendererImpl
{
    SDLTexture m_texture;
    const SDLRenderer& m_renderer;

public:
    int m_characterHeight;
    int m_characterWidth;
    
    TextRendererImpl(const std::string& fontFile, const SDLRenderer& renderer) : m_renderer(renderer)
    {
        PNGLoader loader;
        auto surface = SDLSurface(loader.Load(fontFile));

        m_texture = surface.CreateAsTexture(renderer);

        // We assume it's a 16x16 grid of characters

        m_characterHeight = surface.Height() / 16;
        m_characterWidth = surface.Width() / 16;

    }
    ~TextRendererImpl() {}

    void PrintCharacter(unsigned char c, int x, int y, Color color) const
    {
        auto rx = x * m_characterHeight;
        auto ry = y * m_characterHeight;
        RenderCharacter(c, rx, ry, color);
    }

    void PrintString(std::string string, int x, int y, Color color) const
    {
        for (auto&& c : string)
        {
            PrintCharacter(c, x, y, color);
            x++;
        }
    }

    void RenderCharacter(unsigned char c, int x, int y, Color color) const
    {
        auto cx = c % 16;
        auto cy = c / 16;
        auto srcRect = SDLRect(cx * m_characterHeight, cy * m_characterWidth, m_characterHeight, m_characterWidth);
        auto destRect = SDLRect(x, y, m_characterHeight, m_characterWidth);

        m_renderer.RenderCopyColor(m_texture, srcRect, destRect, color);
    }
};


TextRenderer::TextRenderer(const std::string& fontFile, const SDLRenderer& renderer)
: m_Impl(std::make_unique<TextRendererImpl>(fontFile, renderer)) { }

TextRenderer::~TextRenderer() { m_Impl.release(); }

void TextRenderer::PrintCharacter(unsigned char c, int x, int y, Color color) const
{
    m_Impl->PrintCharacter(c, x, y, color);
}

void TextRenderer::PrintString(std::string string, int x, int y, Color color) const
{
    m_Impl->PrintString(string, x, y, color);
}

int TextRenderer::CharHeight() const
{
    return m_Impl->m_characterHeight;
}

int TextRenderer::CharWidth() const
{
    return m_Impl->m_characterWidth;
}
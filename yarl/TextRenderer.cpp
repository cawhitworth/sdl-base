#include "TextRenderer.h"
#include "PngLoader.h"
#include "SDLRect.h"
#include "Color.h"
#include "SDLRenderer.h"

TextRenderer::TextRenderer(const std::string& fontFile, const SDLRenderer& renderer) : m_renderer(renderer)
{
    PNGLoader loader;
    auto surface = SDLSurface(loader.Load(fontFile));

    m_texture = surface.CreateAsTexture(renderer);

    // We assume it's a 16x16 grid of characters

    m_characterHeight = surface.Height() / 16;
    m_characterWidth = surface.Width() / 16;
}

TextRenderer::~TextRenderer()
{
}

void TextRenderer::PrintCharacter(unsigned char c, int x, int y, Color color) const
{
    auto rx = x * m_characterHeight;
    auto ry = y * m_characterHeight;
    RenderCharacter(c, rx, ry, color);
}

void TextRenderer::PrintString(std::string string, int x, int y, Color color) const
{
    for (auto&& c : string)
    {
        PrintCharacter(c, x, y, color);
        x++;
    }
}

void TextRenderer::RenderCharacter(unsigned char c, int x, int y, Color color) const
{
    auto cx = c % 16;
    auto cy = c / 16;
    auto srcRect = SDLRect(cx * m_characterHeight, cy * m_characterWidth, m_characterHeight, m_characterWidth);
    auto destRect = SDLRect(x, y, m_characterHeight, m_characterWidth);

    m_renderer.RenderCopyColor(m_texture, srcRect, destRect, color);
}
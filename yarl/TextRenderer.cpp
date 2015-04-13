#include "TextRenderer.h"
#include "PngLoader.h"
#include "SDLRect.h"
#include "Color.h"

TextRenderer::TextRenderer(const std::string& fontFile)
{
    PNGLoader loader;
    m_surface = SDLSurface(loader.Load(fontFile));

    // We assume it's a 16x16 grid of characters

    m_characterHeight = m_surface.Height() / 16;
    m_characterWidth = m_surface.Width() / 16;
}

TextRenderer::~TextRenderer()
{
}

void TextRenderer::RenderCharacter(unsigned char c, int x, int y, const SDLSurface& target, Color color)
{
    auto cx = c % 16;
    auto cy = c / 16;
    auto srcRect = SDLRect(cx * m_characterHeight, cy * m_characterWidth, m_characterHeight, m_characterWidth);
    auto destRect = SDLRect(x, y, m_characterHeight, m_characterWidth);
    target.ColorBlit(m_surface, srcRect, destRect, color);
}
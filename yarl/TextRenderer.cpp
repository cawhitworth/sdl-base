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

void TextRenderer::RenderCharacter(unsigned char c, int x, int y, const SDLSurface& target, Color color)
{
    auto cx = c % 16;
    auto cy = c / 16;
    auto srcRect = SDLRect(cx * m_characterHeight, cy * m_characterWidth, m_characterHeight, m_characterWidth);
    auto destRect = SDLRect(x, y, m_characterHeight, m_characterWidth);

    m_renderer.RenderCopy(m_texture, srcRect, destRect);
}
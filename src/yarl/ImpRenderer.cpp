#include "ImpRenderer.h"
#include "TextRenderer.h"
#include "Color.h"
#include "Imp.h"

void ImpRenderer::Render(const Imp& imp)
{
    auto location = imp.Location();
    location.x -= m_mapOrigin.x;
    location.y -= m_mapOrigin.y;
    m_renderer.PrintCharacter('I', location, Color(0, 255, 0));
}
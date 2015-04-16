#include "ImpRenderer.h"
#include "TextRenderer.h"
#include "Color.h"
#include "Imp.h"

void ImpRenderer::Render(const Imp& imp)
{
    m_renderer.PrintCharacter('I', imp.Location(), Color(0, 255, 0));
}
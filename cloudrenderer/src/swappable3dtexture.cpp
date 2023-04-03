#include "swappable3dtexture.h"
Swappable3DTexture::Swappable3DTexture(void *data, eng::rndr::TextureInfo info, int width, int height, int depth) : m_a(data, info, width, height, depth), m_b(data, info, width, height, depth)
{
}

void Swappable3DTexture::swap()
{
    m_isAActive=!m_isAActive;
}

eng::rndr::Texture3d &Swappable3DTexture::getA()
{
    return m_a;
}

eng::rndr::Texture3d &Swappable3DTexture::getB()
{
    return m_b;
}

eng::rndr::Texture3d &Swappable3DTexture::getActive()
{
    return (m_isAActive) ? m_a : m_b;
}

eng::rndr::Texture3d &Swappable3DTexture::getNonActive()
{
    return (!m_isAActive) ? m_a : m_b;
}


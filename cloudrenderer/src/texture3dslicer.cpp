#include "texture3dslicer.h"

Texture3dSlicer::Texture3dSlicer(eng::rndr::Texture3d &texture) : m_texture(texture), m_slice(std::make_shared<eng::rndr::Texture2d>(nullptr, texture.info(), m_texture.width(), m_texture.height()))
{
    update(0);
}

void Texture3dSlicer::update(int slice)
{
    glBindTexture(GL_TEXTURE_2D, m_slice->id());
    glBindTexture(GL_TEXTURE_3D, m_texture.id());

    glCopyImageSubData(m_texture.id(), GL_TEXTURE_3D, 0, 0, 0, slice, m_slice->id(), GL_TEXTURE_2D, 0, 0, 0, 0, m_slice->width(), m_slice->height(), 1);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindTexture(GL_TEXTURE_3D, 0);
}

std::shared_ptr<eng::rndr::Texture2d> Texture3dSlicer::getSlice()
{
    return m_slice;
}

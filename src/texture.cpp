#include "texture.h"
namespace eng::rndr
{
Texture::Texture()
{

}

Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}

GLuint Texture::id() const
{
    return m_id;
}
void Texture::bind(GLenum unit)
{
    glActiveTexture(unit);
    glBindTexture(GL_TEXTURE_2D, m_id);
}
}
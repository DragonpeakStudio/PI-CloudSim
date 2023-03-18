#include "texture3d.h"
namespace eng::rndr
{

Texture3d::Texture3d(void *data, TextureInfo info, int width, int height, int depth) : m_width(width), m_height(height), m_depth(depth), m_info(info)
{
    GLint maxSize;
	glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &maxSize);
    if(maxSize < width || maxSize < height || maxSize < depth)
    {
        throw std::runtime_error("Texture3d::Texture3d - maxSize: " + std::to_string(maxSize) + " less than requested size: " + std::to_string(width) + "w " + std::to_string(height) + "h " + std::to_string(depth) + "d");
    }
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_3D, m_id);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, m_info.wrapS);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, m_info.wrapT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, m_info.filterMin);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, m_info.filterMag);
    glTexImage3D(GL_TEXTURE_3D, 0, m_info.internalFormat, m_width, m_height, m_depth, 0, m_info.format, m_info.type, data);
}

int Texture3d::height() const
{
    return m_height;
}

Texture3d::~Texture3d()
{

}

int Texture3d::depth() const
{
    return m_depth;
}

int Texture3d::width() const
{
    return m_width;
}

TextureInfo Texture3d::info() const
{
    return m_info;
}
void Texture3d::bind(GLenum unit)
{
    glActiveTexture(unit);
    glBindTexture(GL_TEXTURE_3D, m_id);
}

}
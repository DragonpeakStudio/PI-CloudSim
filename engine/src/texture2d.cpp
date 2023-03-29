#include "texture2d.h"
#include <OpenImageIO/imageio.h>
namespace eng::rndr
{
Texture2d::Texture2d(const std::string &path, TextureInfo info) : m_info(info)
{
    auto in = OIIO::ImageInput::open(path);
    if(!in)
    {
        throw std::runtime_error("Unable to load image: " + path);
    }
    const OIIO::ImageSpec &spec = in->spec();
    m_width = spec.width;
    m_height = spec.height;
    m_info.channels = spec.nchannels;//TODO allow auto convert to provided channels
    OIIO::TypeDesc type;
    int size = 0;
    switch (m_info.type)
    {
    case GL_UNSIGNED_BYTE:
        type = OIIO::TypeDesc::UINT8;
        size = sizeof(unsigned char);
        break;
    case GL_BYTE:
        type = OIIO::TypeDesc::INT8;
        size = sizeof(char);

        break;
    case GL_UNSIGNED_SHORT:
        type = OIIO::TypeDesc::USHORT;
        size = sizeof(unsigned short);

        break;
    case GL_SHORT:
        type = OIIO::TypeDesc::SHORT;
        size = sizeof(short);

        break;
    case GL_UNSIGNED_INT:
        type = OIIO::TypeDesc::UINT;
        size = sizeof(unsigned int);

        break;
    case GL_INT:
        type = OIIO::TypeDesc::INT;
        size = sizeof(int);
        break;
    case GL_FLOAT:
        type = OIIO::TypeDesc::FLOAT;
        size = sizeof(float);

        break;
    
    default:
        break;
    }
    std::vector<unsigned char> data(m_width*m_height*m_info.channels*size);
    in->read_image(type, data.data());
    in->close();
    fromData(data.data());
}

Texture2d::Texture2d(void *data, TextureInfo info, int width, int height) : m_width(width), m_height(height), m_info(info)
{
    fromData(data);
}

Texture2d::~Texture2d()
{
}

TextureInfo Texture2d::info() const
{
    return m_info;
}

int Texture2d::width() const
{
    return m_width;
}

int Texture2d::height() const
{
    return m_height;
}
void Texture2d::fromData(void *data)
{
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_info.wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_info.wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_info.filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_info.filterMag);
    glTexImage2D(GL_TEXTURE_2D, 0, m_info.internalFormat, m_width, m_height, 0, m_info.format, m_info.type, data);
}

}
#ifndef TEXTURE3D_H
#define TEXTURE3D_H

#pragma once

#include "texture.h"
#include <stdexcept>
namespace eng::rndr
{

class Texture3d : public Texture
{
    public:
        Texture3d(void *data, TextureInfo info, int width, int height, int depth);
        ~Texture3d();
    
    protected:
        int m_width, m_height, m_depth;
        TextureInfo m_info;

};
}
#endif
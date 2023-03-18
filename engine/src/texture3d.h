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

        int width() const;

        int height() const;

        int depth() const;

        TextureInfo info() const;
        virtual void bind(GLenum unit) override;
    
    protected:
        int m_width;
        int m_height;
        int m_depth;
        TextureInfo m_info;

};
}
#endif
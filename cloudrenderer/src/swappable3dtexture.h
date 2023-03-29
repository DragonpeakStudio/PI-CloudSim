#ifndef SWAPPABLE3DTEXTURE_H
#define SWAPPABLE3DTEXTURE_H

#pragma once
#include "texture3d.h"

class Swappable3DTexture
{
    public:
        Swappable3DTexture(void *data, eng::rndr::TextureInfo info, int width, int height, int depth);
        void swap();
        eng::rndr::Texture3d &getA();
        eng::rndr::Texture3d &getB();
        eng::rndr::Texture3d &getActive();
        eng::rndr::Texture3d &getNonActive();

    private:
        eng::rndr::Texture3d m_a;
        eng::rndr::Texture3d m_b;
        bool m_isAActive = true;


};

#endif
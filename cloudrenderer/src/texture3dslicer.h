#ifndef TEXTURE3DSLICER_H
#define TEXTURE3DSLICER_H

#pragma once
#include <memory>
#include "computeshaderprogram.h"
#include "texture3d.h"
#include "texture2d.h"

class Texture3dSlicer
{
    public:
        Texture3dSlicer(eng::rndr::Texture3d &texture);
        void update(int slice);
        std::shared_ptr<eng::rndr::Texture2d> getSlice(); 
    private:
        eng::rndr::Texture3d &m_texture;
        std::shared_ptr<eng::rndr::Texture2d> m_slice;

};

#endif
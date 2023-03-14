#ifndef CLOUDRENDERER_H
#define CLOUDRENDERER_H

#pragma once
#include "texture3d.h"
class CloudSystem;
class CloudRenderer
{
    public:
        CloudRenderer(CloudSystem &cloudSystem);
        ~CloudRenderer();
        virtual void draw(eng::rndr::Texture3d &densityField) = 0;
    
    protected:
        CloudSystem &m_cloudSystem;

};

#endif
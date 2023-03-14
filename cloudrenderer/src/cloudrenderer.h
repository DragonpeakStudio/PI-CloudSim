#ifndef CLOUDRENDERER_H
#define CLOUDRENDERER_H

#pragma once
#include "texture3d.h"
#include "renderer.h"
class CloudSystem;
class CloudRenderer
{
    public:
        CloudRenderer(CloudSystem &cloudSystem);
        ~CloudRenderer();
        virtual void draw(eng::rndr::Texture3d &densityField, eng::rndr::Renderer &renderer) = 0;
    
    protected:
        CloudSystem &m_cloudSystem;

};

#endif
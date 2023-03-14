#ifndef CLOUDRENDERER_H
#define CLOUDRENDERER_H

#pragma once
#include "texture3d.h"
#include "renderer.h"
class CloudSystem;
class CloudRenderer
{
    public:
        CloudRenderer(std::pair<glm::vec3, glm::vec3> bbox);
        virtual ~CloudRenderer(){}
        virtual void draw(eng::rndr::Texture3d &densityField, eng::rndr::Renderer &renderer) = 0;
    
    protected:
        std::pair<glm::vec3, glm::vec3> m_bbox;

};

#endif
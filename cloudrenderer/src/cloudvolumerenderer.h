#ifndef CLOUDVOLUMERENDERER_H
#define CLOUDVOLUMERENDERER_H

#pragma once
#include "cloudrenderer.h"
class CloudVolumeRenderer : public CloudRenderer
{
    public:
        CloudVolumeRenderer(std::pair<glm::vec3, glm::vec3> bbox);
    
        virtual void draw(eng::rndr::Texture3d &densityField, eng::rndr::Renderer &renderer) override;

    private:

};

#endif
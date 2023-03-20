#ifndef CLOUDVOLUMERENDERER_H
#define CLOUDVOLUMERENDERER_H

#pragma once
#include <vfshaderprogram.h>
#include "cloudrenderer.h"
#include "glutil.h"
#include "framebuffer.h"
class CloudVolumeRenderer : public CloudRenderer
{
    public:
        CloudVolumeRenderer(std::pair<glm::vec3, glm::vec3> bbox, std::weak_ptr<OutdoorLighting> lighting);
        ~CloudVolumeRenderer();
        virtual void draw(eng::rndr::Texture3d &densityField, eng::rndr::Renderer &renderer) override;
        virtual void drawUI() override;
    private:
        GLuint m_vbo = 0;
        GLuint m_vao = 0;
        eng::rndr::VFShaderProgram m_drawShader;
        float m_ambientBrightness = .05;
        float m_sunBrightness = .3;
        float m_stepSize = .1;
        float m_lightFar = 1.;
        float m_lightDensMult = .5; 
        float m_lightStepSize = .1;
};
#endif

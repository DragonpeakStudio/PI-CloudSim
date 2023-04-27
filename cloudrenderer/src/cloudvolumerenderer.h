#ifndef CLOUDVOLUMERENDERER_H
#define CLOUDVOLUMERENDERER_H

#pragma once
#include <vfshaderprogram.h>
#include "texture3d.h"
#include "cloudrenderer.h"
#include "glutil.h"
#include "framebuffer.h"
#include "texture3dslicer.h"
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
        float m_ambientBrightness = .15;
        float m_sunBrightness = 1.;
        float m_stepSize = 1;
        float m_lightFar = 25.;
        float m_lightDensMult = .4; 
        float m_densMult = 10.;
        float m_lightStepSize = 8.;
        float m_time = 1.;
        std::unique_ptr<eng::rndr::FrameBuffer> m_frameBuffer;
        float m_cloudResMult = 0.8;
        float m_lastFrameBlend = .5;
        glm::ivec4 m_origViewport;
        glm::ivec4 m_scaledViewport;
        std::unique_ptr<eng::rndr::Texture2d> m_lastFrame;


};
#endif

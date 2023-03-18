#ifndef CLOUDNOISESIMULATOR_H
#define CLOUDNOISESIMULATOR_H

#pragma once
#include <memory>
#include "imgui.h"
#include "computeshaderprogram.h"
#include "texture3d.h"
#include "texture3dslicer.h"
#include "cloudsimulator.h"
class CloudNoiseSimulator : public CloudSimulator
{
    public:
        CloudNoiseSimulator(std::pair<glm::vec3, glm::vec3> bbox, float voxelScale);
        virtual void update(double delta) override;
        virtual eng::rndr::Texture3d &getField(std::string_view identifier) override;
        virtual void drawUI() override;
    
    private:
        eng::rndr::Texture3d m_densField;
        eng::rndr::ComputeShaderProgram m_noiseProcess;
        Texture3dSlicer m_slicer;
        double m_time = 0.;
        int m_debugSlice = 0;

};

#endif
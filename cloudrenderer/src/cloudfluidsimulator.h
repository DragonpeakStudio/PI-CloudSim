#ifndef CLOUDFLUIDSIMULATOR_H
#define CLOUDFLUIDSIMULATOR_H

#pragma once
#include <memory>
#include "computeshaderprogram.h"
#include "cloudsimulator.h"
#include "swappable3dtexture.h"
class CloudFluidSimulator : public CloudSimulator
{
    public:
        CloudFluidSimulator(std::pair<glm::vec3, glm::vec3> bbox, float voxelScale);
        ~CloudFluidSimulator();
        virtual void update(double delta) override;
        virtual eng::rndr::Texture3d &getField(std::string_view identifier) override;
        virtual void drawUI() override;

        void setCollisionField(std::unique_ptr<eng::rndr::Texture3d> collisionField);
    
    private:
        Swappable3DTexture m_velocity;
        Swappable3DTexture m_qvAndTemp;//sperate these so qc can be used as density field in rendering easily
        Swappable3DTexture m_qc;
        Swappable3DTexture m_pressureAndDivergence;
        std::unique_ptr<eng::rndr::Texture3d> m_collisionField;
        eng::rndr::ComputeShaderProgram m_advect;
        eng::rndr::ComputeShaderProgram m_applyForces;
        eng::rndr::ComputeShaderProgram m_updateWaterAndTemp;
        eng::rndr::ComputeShaderProgram m_calcDivergence;
        eng::rndr::ComputeShaderProgram m_pressureItr;
        eng::rndr::ComputeShaderProgram m_applyPressureGrad;





};

#endif
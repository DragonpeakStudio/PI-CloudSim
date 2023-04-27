#ifndef CLOUDFLUIDSIMULATOR_H
#define CLOUDFLUIDSIMULATOR_H

#pragma once
#include <memory>
#include "imgui.h"

#include "computeshaderprogram.h"
#include "cloudsimulator.h"
#include "swappable3dtexture.h"
#include "texture3dslicer.h"
class CloudFluidSimulator : public CloudSimulator
{
    public:
        CloudFluidSimulator(std::pair<glm::vec3, glm::vec3> bbox, float voxelScale);
        ~CloudFluidSimulator();
        virtual void update(double delta) override;
        virtual eng::rndr::Texture3d &getField(std::string_view identifier) override;
        virtual void drawUI() override;
        virtual void init() override;
    
        void setCollisionField(std::unique_ptr<eng::rndr::Texture3d> collisionField);

    private:
        Swappable3DTexture m_velocity;
        Swappable3DTexture m_qvAndTemp;//sperate these so qc can be used as density field in rendering easily
        Swappable3DTexture m_qc;
        Swappable3DTexture m_pressureAndDivergence;
        eng::rndr::Texture3d m_curl;
        std::unique_ptr<eng::rndr::Texture3d> m_collisionField;
        eng::rndr::Texture3d m_debugOut;

        eng::rndr::ComputeShaderProgram m_advect;
        eng::rndr::ComputeShaderProgram m_applyForces;
        eng::rndr::ComputeShaderProgram m_updateWaterAndTemp;
        eng::rndr::ComputeShaderProgram m_calcDivergence;
        eng::rndr::ComputeShaderProgram m_pressureItr;
        eng::rndr::ComputeShaderProgram m_applyPressureGrad;
        eng::rndr::ComputeShaderProgram m_initProcess;
        eng::rndr::ComputeShaderProgram m_setBoundary;
        eng::rndr::ComputeShaderProgram m_calcCurl;


        Texture3dSlicer m_velSlicer;
        Texture3dSlicer m_qvAndTempSlicer;
        Texture3dSlicer m_qcSlicer;
        Texture3dSlicer m_pressureAndDivergenceSlicer;
        Texture3dSlicer m_debugOutSlicer;
        std::unique_ptr<Texture3dSlicer> m_collisionFieldSlicer;


        int m_debugSlice = 0;
        unsigned int m_pressureItrs = 15;
        void advectField(Swappable3DTexture &field, eng::rndr::Texture3d &velField, float delta);
        void initFields();
        bool m_stepByStep = true;
        bool m_update = false;
        float m_time = 0;
        float m_baseTemp = 280.;
        float m_bottomQV = .1;
        float m_bottomTempOffset = 100.;
        float m_windAngle = 0;
        float m_windStr = 0.01;
        float m_vortStr = 1024.*8.;

    
};


#endif
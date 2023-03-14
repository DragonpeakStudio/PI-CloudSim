#ifndef CLOUDNOISESIMULATOR_H
#define CLOUDNOISESIMULATOR_H

#pragma once
#include "texture3d.h"
#include "cloudsimulator.h"
class CloudNoiseSimulator : public CloudSimulator
{
    public:
        CloudNoiseSimulator(std::pair<glm::vec3, glm::vec3> bbox, float voxelScale);
        virtual void update(double delta) override;
        virtual eng::rndr::Texture3d &getField(std::string_view identifier) override;
    
    private:
        eng::rndr::Texture3d m_densField;

};

#endif
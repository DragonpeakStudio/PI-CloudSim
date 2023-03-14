#ifndef CLOUDSIMULATOR_H
#define CLOUDSIMULATOR_H

#pragma once
#include <string_view>
#include <glm/glm.hpp>
#include "texture3d.h"

class CloudSimulator
{
    public:
        CloudSimulator(std::pair<glm::vec3, glm::vec3> bbox, float voxelScale);
        virtual ~CloudSimulator(){}
        virtual void update(double delta) = 0;
        virtual eng::rndr::Texture3d &getField(std::string_view identifier) = 0;
    protected:
        std::pair<glm::vec3, glm::vec3> m_bbox;
        float m_voxelScale;

};

#endif
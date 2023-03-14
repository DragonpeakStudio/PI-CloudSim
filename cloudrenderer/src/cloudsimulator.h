#ifndef CLOUDSIMULATOR_H
#define CLOUDSIMULATOR_H

#pragma once
#include <string_view>
#include "texture3d.h"

class CloudSimulator
{
    public:
        CloudSimulator();
        ~CloudSimulator();
        virtual void update(double delta) = 0;
        virtual eng::rndr::Texture3d &getField(std::string_view identifier) = 0;
    private:

};

#endif
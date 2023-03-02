#ifndef CLOUDSYSTEM_H
#define CLOUDSYSTEM_H

#pragma once
#include <memory>
#include "object.h"
#include "cloudrenderer.h"
#include "cloudsimulator.h"

class CloudSystem : public eng::Object
{
    public:
        CloudSystem();
        ~CloudSystem();
    
    private:
        std::unique_ptr<CloudRenderer> m_renderer;
        std::unique_ptr<CloudSimulator> m_simulator;


};

#endif
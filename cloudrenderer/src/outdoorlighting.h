#ifndef OUTDOORLIGHTING_H
#define OUTDOORLIGHTING_H

#pragma once
#include "object.h"
#include "imgui.h"

class OutdoorLighting : public eng::Object
{
    public:
        OutdoorLighting();
        virtual ~OutdoorLighting();

        virtual void drawUI() override;

        glm::vec3 sunCol() const;

        glm::vec3 ambientCol() const;
        glm::vec3 sunDir() const;

        bool hasDirChanged() const;
    
    protected:
        glm::vec3 m_sunCol = glm::vec3(1,.9,.85);
        glm::vec3 m_ambientCol = glm::vec3(.2,.3,.6);
        glm::vec2 m_sunSpherical = glm::vec2(1.3, 0.);
        bool m_hasDirChanged = true;

};

#endif
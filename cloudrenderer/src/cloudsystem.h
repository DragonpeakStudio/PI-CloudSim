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
        template<typename Renderer, typename Simulator> 
        CloudSystem(std::pair<glm::vec3, glm::vec3> bbox) : m_bbox(bbox)
        {
            static_assert(std::is_base_of<CloudRenderer, Renderer>::value, "Renderer not derived from CloudRenderer");
            static_assert(std::is_base_of<CloudSimulator, Simulator>::value, "Simulator not derived from CloudSimulator");

            m_renderer = std::make_unique<Renderer>(*this);
            m_simulator = std::make_unique<Simulator>(*this);
        }
        virtual void draw(eng::rndr::Renderer *renderer) override;
        virtual void update(double delta) override;
        virtual void drawUI() override;
        std::pair<glm::vec3, glm::vec3> bbox() const;
    private:
        std::unique_ptr<CloudRenderer> m_renderer;
        std::unique_ptr<CloudSimulator> m_simulator;
        std::pair<glm::vec3, glm::vec3> m_bbox;


};

#endif
#ifndef CLOUDSYSTEM_H
#define CLOUDSYSTEM_H

#pragma once
#include <memory>
#include "object.h"
#include "cloudrenderer.h"
#include "cloudsimulator.h"
#include "outdoorlighting.h"
class CloudSystem : public eng::Object
{
    public:
        CloudSystem() = delete;
        virtual ~CloudSystem();
        template<typename Renderer, typename Simulator> 
        static std::shared_ptr<CloudSystem> create(std::pair<glm::vec3, glm::vec3> bbox, std::weak_ptr<OutdoorLighting> lighting, float voxelScale)
        {
            static_assert(std::is_base_of<CloudRenderer, Renderer>::value, "Renderer not derived from CloudRenderer");
            static_assert(std::is_base_of<CloudSimulator, Simulator>::value, "Simulator not derived from CloudSimulator");
            return std::shared_ptr<CloudSystem>(new CloudSystem(std::make_unique<Renderer>(bbox, lighting), std::make_unique<Simulator>(bbox, voxelScale), bbox));
        }
        virtual void draw(eng::rndr::Renderer &renderer) override;
        virtual void update(double delta) override;
        virtual void drawUI() override;
        virtual void onAdd(eng::Engine *engine) override;
        std::pair<glm::vec3, glm::vec3> bbox() const;
        CloudRenderer *renderer();
        CloudSimulator *simulator();
    private:
        CloudSystem(std::unique_ptr<CloudRenderer> renderer, std::unique_ptr<CloudSimulator> simulator, std::pair<glm::vec3, glm::vec3> bbox);

        std::unique_ptr<CloudRenderer> m_renderer;
        std::unique_ptr<CloudSimulator> m_simulator;
        std::pair<glm::vec3, glm::vec3> m_bbox;



};

#endif
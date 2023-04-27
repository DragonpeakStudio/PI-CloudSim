#include "engine.h"
#include "terrain.h"
#include "camera.h"
#include "outdoorlighting.h"
#include "cloudsystem.h"
#include "cloudnoisesimulator.h"
#include "cloudfluidsimulator.h"
#include "cloudvolumerenderer.h"
#include "heightmapvoxelizer.h"
int main(int, char**) 
{
    const int width = 1920;
    const int height = 1080;
    auto engine = eng::Engine(eng::EngineConfig{eng::rndr::RendererConfig{"Realtime Cloud Simulation and Rendering", width, height, 4, 5}});
    std::shared_ptr<OutdoorLighting> lighting = std::make_shared<OutdoorLighting>();
    auto heightMap = std::make_unique<eng::rndr::Texture2d>("../resources/terrain/export/height.tiff", eng::rndr::TextureInfo{GL_CLAMP, GL_CLAMP, GL_LINEAR, GL_LINEAR, GL_RED, 1, GL_R16F, GL_FLOAT});
    auto collision = voxelizeHeightMap(heightMap.get(), std::make_pair(glm::vec3(-512,-512,-64), glm::vec3(512,512,256)), 2.f);
    auto terrain = std::make_shared<Terrain>(lighting, std::move(heightMap),
    std::make_unique<eng::rndr::Texture2d>("../resources/terrain/export/_albedo.png", eng::rndr::TextureInfo{GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGBA, 1, GL_RGBA, GL_UNSIGNED_BYTE}), 
    1000, 1000, 1200, 1200);
    terrain->generate();
    engine.addObject(std::make_shared<eng::rndr::Camera>(80., (float)width/(float)height));
    engine.addObject(terrain);
    engine.addObject(lighting);
    auto cloudSystem = CloudSystem::create<CloudVolumeRenderer, CloudFluidSimulator>(std::make_pair(glm::vec3(-512,-512,-64), glm::vec3(512,512,256)), lighting, 4.f);
    ((CloudFluidSimulator*)cloudSystem->simulator())->setCollisionField(std::move(collision));
    engine.addObject(cloudSystem);
    engine.run();
    return 0;
}

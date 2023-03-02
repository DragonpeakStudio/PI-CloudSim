#include "engine.h"
#include "terrain.h"
#include "camera.h"
#include "outdoorlighting.h"
int main(int, char**) 
{
    const int width = 1280;
    const int height = 720;
    auto engine = eng::Engine(eng::EngineConfig{eng::rndr::RendererConfig{"Realtime Cloud Simulation and Rendering", width, height, 4, 5}});
    std::shared_ptr<OutdoorLighting> lighting = std::make_shared<OutdoorLighting>();
    auto terrain = std::make_shared<Terrain>(lighting, std::make_unique<eng::rndr::Texture2d>("../resources/terrain/export/height.tiff", eng::rndr::TextureInfo{GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RED, 1, GL_R16F, GL_FLOAT}),
    std::make_unique<eng::rndr::Texture2d>("../resources/terrain/export/_albedo.png", eng::rndr::TextureInfo{GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGBA, 1, GL_RGBA, GL_UNSIGNED_BYTE}), 
    1000, 1000, 800, 800);
    terrain->generate();
    engine.addObject(std::make_shared<eng::rndr::Camera>(80., (float)width/(float)height));
    engine.addObject(terrain);
    engine.addObject(lighting);
    engine.run();
    return 0;
}
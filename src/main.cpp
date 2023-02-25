#include "engine.h"
#include "terrain.h"
#include "camera.h"
int main(int, char**) 
{
    const int width = 1280;
    const int height = 720;
    auto engine = eng::Engine(eng::EngineConfig{eng::rndr::RendererConfig{"Realtime Cloud Simulation and Rendering", width, height, 4, 5}});
    auto terrain = std::make_shared<Terrain>(std::make_unique<eng::rndr::Texture2d>("resources/terrain/export/height.tiff", eng::rndr::Texture2dInfo{GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RED, 1, GL_R16F, GL_FLOAT}),
    std::make_unique<eng::rndr::Texture2d>("resources/terrain/export/_albedo.png", eng::rndr::Texture2dInfo{GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGBA, 1, GL_RGBA, GL_UNSIGNED_BYTE}), 
    1024, 1024);
    terrain->generate();
    engine.addObject(std::make_shared<eng::rndr::Camera>(80., (float)width/(float)height));
    engine.addObject(terrain);
    engine.run();
    return 0;
}
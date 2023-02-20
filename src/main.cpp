#include "engine.h"

int main(int, char**) 
{
    auto engine = eng::Engine(eng::EngineConfig{eng::rndr::RendererConfig{"Realtime Cloud Simulation and Rendering", 800, 600, 4, 5}});
    engine.run();
    return 0;
}

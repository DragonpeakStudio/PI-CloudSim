#include "engine.h"
namespace eng
{
Engine::Engine(EngineConfig &&config) :  m_inputManager(this), m_renderer(config.renderConfig, this)
{
	m_inputManager.addKeybindCallback(SDL_SCANCODE_ESCAPE, [this](){exit();});
}

Engine::~Engine()
{

}

void Engine::run()
{
	m_state = RUNNING;
	mainLoop();
}

InputManager &Engine::inputManager()
{
	return m_inputManager;
}

void Engine::exit()
{
	m_state = STOPPED;
}
void Engine::addObject(std::shared_ptr<Object> obj)
{
    m_objects.push_back(obj);
    m_renderer.addDrawable(obj);
    obj->onAdd(this);
}
void Engine::mainLoop()
{
    auto e = std::chrono::high_resolution_clock::now();
    while(m_state == EngineState::RUNNING)
    {
        std::chrono::duration<double> time = std::chrono::high_resolution_clock::now()-e;
		e = std::chrono::high_resolution_clock::now();
        double delta = time.count();
        std::cerr << "FPS: " << 1./delta << " | Delta: " << delta << std::endl;
        m_inputManager.processEvents();
        update(delta);
        m_renderer.dispatchFrame();
    }
}
void Engine::update(double delta)
{
    for(auto &i : m_objects)
    {
        i->update(delta, this);
    }
}
}